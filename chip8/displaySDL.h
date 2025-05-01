#ifndef __DISPLAYSDL_H__
#define __DISPLAYSDL_H__

#include <cstdint>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "display.h"
#include "logger.h"

class TDisplaySDL : public TDisplayInterface{
    SDL_Window* window{};
    SDL_Renderer* renderer{};
    SDL_Texture* texture{};

    uint8_t red{};
    uint8_t green{};
    uint8_t blue{};
    uint32_t* textureBuffer;

    int height;
    int width;
    // Logging
    std::shared_ptr<TLogger> logger;

public:
    TDisplaySDL(uint8_t red, uint8_t green, uint8_t blue);
    ~TDisplaySDL();
    virtual void init(char const* title, uint16_t displayWidth, uint16_t displayHeight, uint8_t displayScale) override; 
    virtual void update(uint8_t buffer[][64]) override;
    virtual void deinit() override;
};

#endif