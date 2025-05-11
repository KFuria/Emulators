#ifndef __LOADER_H__
#define __LOADER_H__

#include <cstdint>
#include <filesystem>
#include <chrono>
#include <thread>

#include "logger.h"
#include "display.h"
#include "keyboard.h"

#define NUM_KEYS 16

class TLoader{
    std::shared_ptr<TLogger> logger;
    
    TDisplayInterface* display;
    TKeyboard* keyboard;

    std::vector<std::string> menu_list;
    int activeIdx = 0;
    uint8_t numFiles;

    uint8_t keys[NUM_KEYS];

    bool menu_running;

    std::string root_path;
    std::string rom_path;

public: 
    TLoader();
    ~TLoader();
    void init(std::string root_path);
    void deinit();
    void update();
    void run();
    void setDisplay(TDisplayInterface* display);
    void setKeyboard(TKeyboard* keyboardInterface);
    std::vector<std::string>& getMenuList();
    std::string getRomPath();
};



#endif