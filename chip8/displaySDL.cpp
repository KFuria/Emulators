#include <cstdint>
#include <SDL2/SDL.h>

#include "displaysdl.h"

TDisplaySDL::TDisplaySDL(){
    logger = TLogger::getInstance();
    logger->log("Display Constructed", ELogLevel::DEBUG);
}

TDisplaySDL::~TDisplaySDL(){
    logger->log("Display Destructed", ELogLevel::DEBUG);
}

void TDisplaySDL::init(char const* title, uint16_t displayWidth, uint16_t displayHeight, uint8_t displayScale){
    bufferHeight = displayHeight;
    bufferWidth = displayWidth;
    windowHeight = displayHeight * displayScale;
    windowWidth = displayWidth * displayScale;
    menu_offset_y = windowHeight / 2;
    menu_offset_x = windowWidth / 3;

    textureBuffer = new uint32_t [displayWidth*displayHeight]{};
    if(textureBuffer == nullptr){
        logger->log("Display Buffer Initialization Error", ELogLevel::ERROR);
        exit(1);
    }

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0){
        std::string errorSdl(SDL_GetError());
        logger->log("SDL Initialization Error: " + errorSdl, ELogLevel::ERROR);
        exit(1);
    }

    // Initialize TTF
    if (TTF_Init() != 0){
        std::string errorTTF(TTF_GetError());
        logger->log("TTF Initialization Error: " + errorTTF, ELogLevel::ERROR);
        exit(1);
    }
    

    // Create a window
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
    if(!window){
        std::string errorWindow(SDL_GetError());
        logger->log("Window creation Error: " + errorWindow, ELogLevel::ERROR);
        exit(1);
    }
    
    // Create renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(!renderer){
        std::string errorRenderer(SDL_GetError());
        logger->log("Window creation Error: " + errorRenderer, ELogLevel::ERROR);
        exit(1);
    }

    // Create texture for display screen
    texture_d = SDL_CreateTexture(renderer, 
        SDL_PIXELFORMAT_ARGB8888, 
        SDL_TEXTUREACCESS_STREAMING, 
        displayWidth, 
        displayHeight);

    logger->log("Display Initialized", ELogLevel::DEBUG);
}

void TDisplaySDL::createMenuList(std::vector<std::string>& menu_list){
    TTF_Font* menuFont = nullptr;
    setFont(&menuFont, "VCR_OSD_MONO.ttf", 20);
    TTF_Font* titleFont = nullptr; 
    TTF_Font* subtitleFont = nullptr;
    setFont(&titleFont, "VCR_OSD_MONO.ttf", 40);
    setFont(&subtitleFont, "VCR_OSD_MONO.ttf", 20);

    // Create textures for arrows
    SDL_Rect rectL, rectR;
    SDL_Surface* surfaceL = TTF_RenderText_Solid(menuFont, ">>", color);
    SDL_Surface* surfaceR = TTF_RenderText_Solid(menuFont, "<<", color);
    if(!surfaceL | !surfaceR){
        std::string errorSurface(TTF_GetError());
        logger->log("Surface creation Error: " + errorSurface, ELogLevel::ERROR);
        exit(1);
    }
    SDL_Texture* texture_arrow_L = SDL_CreateTextureFromSurface(renderer, surfaceL);
    SDL_Texture* texture_arrow_R = SDL_CreateTextureFromSurface(renderer, surfaceR);
    if(!texture_arrow_L | !texture_arrow_R){
        std::string errorTexture(SDL_GetError());
        logger->log("Texture creation Error: " + errorTexture, ELogLevel::ERROR);
        exit(1);
    }
    rectL.h = surfaceL->h;
    rectL.w = surfaceL->w;
    rectL.x = menu_offset_x + (2 * rectL.w);
    rectL.y = menu_offset_y;
    rectR.h = surfaceR->h;
    rectR.w = surfaceR->w;
    rectR.x = windowWidth - (2 * rectR.w);
    rectR.y = menu_offset_y;
    SDL_FreeSurface(surfaceL);
    SDL_FreeSurface(surfaceR);
    menuTextures.push_back({texture_arrow_L, rectL});
    menuTextures.push_back({texture_arrow_R, rectR});

    //create textures for title
    SDL_Rect rectTitle, rectSubtitle;
    SDL_Surface* surfaceTitle = TTF_RenderText_Solid(titleFont, "CHIP 8 EMULATOR", color);
    SDL_Surface* surfaceSubtitle = TTF_RenderText_Solid(subtitleFont, "2: down   8: up   5: select", color);
    if(!surfaceTitle | !surfaceSubtitle){
        std::string errorSurface(TTF_GetError());
        logger->log("Surface creation Error: " + errorSurface, ELogLevel::ERROR);
        exit(1);
    }
    SDL_Texture* texture_title = SDL_CreateTextureFromSurface(renderer, surfaceTitle);
    SDL_Texture* texture_subtitle = SDL_CreateTextureFromSurface(renderer, surfaceSubtitle);
    if(!texture_title | !texture_subtitle){
        std::string errorTexture(SDL_GetError());
        logger->log("Texture creation Error: " + errorTexture, ELogLevel::ERROR);
        exit(1);
    }
    rectTitle.h = surfaceTitle->h;
    rectTitle.w = surfaceTitle->w;
    rectTitle.x = menu_offset_x/2 - (rectTitle.w/2);
    rectTitle.y = menu_offset_y - 2 * rectTitle.h ;
    rectSubtitle.h = surfaceSubtitle->h;
    rectSubtitle.w = surfaceSubtitle->w;
    rectSubtitle.x = menu_offset_x/2 - (rectSubtitle.w/2);
    rectSubtitle.y = menu_offset_y + 2 * rectSubtitle.h;
    SDL_FreeSurface(surfaceTitle);
    SDL_FreeSurface(surfaceSubtitle);
    menuTextures.push_back({texture_title, rectTitle});
    menuTextures.push_back({texture_subtitle, rectSubtitle});

    // Create textures for program list
    int m = menu_list.size();
    
    for(auto i = 0; i < m; i++){
        SDL_Rect rect;
        SDL_Surface* surface = TTF_RenderText_Solid(menuFont, menu_list[i].c_str(), color);
        if(!surface){
            std::string errorSurface(TTF_GetError());
            logger->log("Surface creation Error: " + errorSurface, ELogLevel::ERROR);
            exit(1);
        }

        SDL_Texture* texture_m = SDL_CreateTextureFromSurface(renderer, surface);
        if(!texture_m){
            std::string errorTexture(SDL_GetError());
            logger->log("Texture creation Error: " + errorTexture, ELogLevel::ERROR);
            exit(1);
        }

        rect.h = surface->h;
        rect.w = surface->w;
        rect.x = menu_offset_x + (4 * rectL.w) ;
        rect.y = menu_offset_y + (rect.h * i); 
        menuTextures.push_back({texture_m, rect});
        SDL_FreeSurface(surface);
    }

}

void TDisplaySDL::deinit(){
    delete textureBuffer;
    for(auto m : menuTextures){
        SDL_DestroyTexture(m.texture);
    }
    SDL_DestroyTexture(texture_d);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
    logger->log("Display Deinitialized", ELogLevel::DEBUG);
}

void TDisplaySDL::update_screen(uint8_t buffer[][64]){
    for(auto r = 0; r < bufferHeight; r++){
        for(auto c = 0; c < bufferWidth; c++){
            if(buffer[r][c] == 1){
                textureBuffer[(r*bufferWidth)+c] = rgb_ON; 
            }
            else{
                textureBuffer[(r*bufferWidth)+c] = rgb_OFF;
            }
        }
    }
    
    SDL_UpdateTexture(texture_d, nullptr, textureBuffer, sizeof(textureBuffer[0]) * bufferWidth);
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture_d, nullptr, nullptr);
	SDL_RenderPresent(renderer);
}

void TDisplaySDL::update_menu(int activeIdx){
    SDL_RenderClear(renderer);
    for(int i = 4; i < (int)menuTextures.size(); i++){
        menuTextures[i].rect.y = menu_offset_y + (menuTextures[i].rect.h * (i - 4)) 
                                    - (activeIdx * menuTextures[i].rect.h);
    }
    for(const auto & t: menuTextures){
        SDL_RenderCopy(renderer, t.texture, NULL, &t.rect);
    }
    SDL_RenderPresent(renderer);
}

void TDisplaySDL::setColor(uint8_t red, uint8_t green, uint8_t blue){
    color.r = red;
    color.g = green;
    color.b = blue;
    rgb_ON = SDL_MapRGBA(0, red, green, blue, 255);
}

void TDisplaySDL::setFont(TTF_Font** gFont, char const* font, uint8_t fontSize){
    *gFont = TTF_OpenFont(font, fontSize);
    if(*gFont == NULL){
        std::string errorSdl(TTF_GetError());
        logger->log("Failed to load font! SDL_ttf Error: " + errorSdl, ELogLevel::ERROR);
        exit(1);
    }
}