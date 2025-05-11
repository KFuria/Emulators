#ifndef __SOUNDSDL_H__
#define __SOUNDSDL_H__

#include <SDL2/SDL.h>
#include "logger.h"
#include "sound.h"

class TSoundSDL : public TSound{
    std::shared_ptr<TLogger> logger;
    SDL_AudioSpec audioSpec;

public: 
    TSoundSDL();
    ~TSoundSDL();
    virtual void init() override;
    virtual void deinit() override;
    virtual void playSound() override;
    virtual void pauseSound() override;

};

#endif