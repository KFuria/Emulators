#ifndef __KEYBOARDSDL_H__
#define __KEYBOARDSDL_H__

#include <cstdint>
#include <SDL2/SDL.h>

#include "keyboard.h"
#include "logger.h"


class TKeyboardSDL : public TKeyboard{
    std::shared_ptr<TLogger> logger;

public:
    TKeyboardSDL();
    ~TKeyboardSDL();
    virtual void init() override;
    virtual void deinit() override;
    virtual void update(uint8_t* keys, bool* running) override;
};

#endif