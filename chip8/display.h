#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <cstdint>
#include <vector>
#include <string>


class TDisplayInterface{

public:
    virtual void init(char const* title, uint16_t displayWidth, uint16_t displayHeight, uint8_t displayScale, std::vector<std::string>& file_map) = 0;
    virtual void deinit() = 0;
    virtual void update_screen(uint8_t buffer[][64]) = 0;
    virtual void update_menu(int activeIdx) = 0;
    virtual void setColor(uint8_t red, uint8_t green, uint8_t blue) = 0;    
};

#endif