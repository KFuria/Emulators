#include <cstdint>
#include <SDL2/SDL.h>

#include "displaysdl.h"

TDisplaySDL::TDisplaySDL(uint8_t red, uint8_t green, uint8_t blue){
    logger = TLogger::getInstance();
    red = red;
    green = green;
    blue = blue;
}

TDisplaySDL::~TDisplaySDL(){

}

void TDisplaySDL::init(char const* title, uint16_t displayWidth, uint16_t displayHeight, uint8_t displayScale)
{
    height = displayHeight;
    width = displayWidth;
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

    // Create a window
    window = SDL_CreateWindow(title,
        SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, 
        displayWidth * displayScale, 
        displayHeight * displayScale, 
        SDL_WINDOW_SHOWN);

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

    // Create texture
    texture = SDL_CreateTexture(renderer, 
        SDL_PIXELFORMAT_ARGB8888, 
        SDL_TEXTUREACCESS_STREAMING, 
        displayWidth, 
        displayHeight);
        
    
}

void TDisplaySDL::update(uint8_t buffer[][64]){
    for(auto r = 0; r < height; r++){
        for(auto c = 0; c < width; c++){
            if(buffer[r][c] == 1){
                textureBuffer[(r*width)+c] = 0xFF | (red << 16) | (green << 8) | blue; 
            }
        }
    }
    
    SDL_UpdateTexture(texture, nullptr, textureBuffer, sizeof(textureBuffer[0]) * width);
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture, nullptr, nullptr);
	SDL_RenderPresent(renderer);
}


void TDisplaySDL::deinit(){
    SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}