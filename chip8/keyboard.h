#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#include <cstdint>

class TKeyboard{
public:
    virtual void update(uint8_t* keys, bool* running) = 0;
};

#endif