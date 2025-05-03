#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <cstdint>

class TDisplayInterface{

public:
    virtual void init(char const* title, uint16_t displayWidth, uint16_t displayHeight, uint8_t displayScale) = 0;
    virtual void deinit() = 0;
    virtual void update(uint8_t buffer[][64]) = 0;
};

#endif