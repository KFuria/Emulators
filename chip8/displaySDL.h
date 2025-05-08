#ifndef __DISPLAYSDL_H__
#define __DISPLAYSDL_H__

#include <cstdint>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "display.h"
#include "logger.h"

struct TmenuTextures{
    SDL_Texture* texture;
    SDL_Rect rect;
};

class TDisplaySDL : public TDisplayInterface{
    SDL_Window* window{};
    SDL_Renderer* renderer{};
    SDL_Texture* texture_d{};

    SDL_Color color = {255, 255, 255, 255};
    uint32_t rgb_ON = 0xFFFFFFFF;
    uint32_t rgb_OFF = 0xFF000000;
    
    
    uint32_t* textureBuffer;

    std::vector<TmenuTextures> menuTextures;

    int menu_offset_y;
    int menu_offset_x;

    int windowHeight;
    int windowWidth;
    int bufferHeight;
    int bufferWidth;

    // Logging
    std::shared_ptr<TLogger> logger;

    void createMenuTextures(std::vector<std::string>& file_map);
    void setFont(TTF_Font** gFont, char const* font, uint8_t fontSize);

public:
    TDisplaySDL();
    ~TDisplaySDL();
    virtual void init(char const* title, uint16_t displayWidth, uint16_t displayHeight, uint8_t displayScale, std::vector<std::string>& file_map) override; 
    virtual void deinit() override;
    virtual void update_screen(uint8_t buffer[][64]) override;
    virtual void update_menu(int activeIdx) override;
    virtual void setColor(uint8_t red, uint8_t green, uint8_t blue) override;
};

#endif