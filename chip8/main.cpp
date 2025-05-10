#include <stdlib.h>

#define SDL_MAIN_HANDLED

#include "logger.h"
#include "chip8.h"
#include "displaysdl.h"
#include "keyboardSDL.h"
#include "soundSDL.h"
#include "loader.h"

int main(){
    std::shared_ptr<TLogger> logger = TLogger::getInstance();

    TDisplaySDL display;
    TKeyboardSDL keyboard;
    TSoundSDL sound;
    TLoader loader;
    TChip8 emulator;

    loader.setDisplay(&display);
    loader.setKeyboard(&keyboard);
    loader.init("roms/");
    display.init("CHIP-8 EMU", SCREEN_WIDTH, SCREEN_HEIGHT, DISPLAYSCALE);
    display.createMenuList(loader.getMenuList());
    loader.run();
    emulator.setDisplay(&display);
    emulator.setKeyboard(&keyboard);
    emulator.setSound(&sound);
    emulator.init(loader.getRomPath());
    emulator.run();
    emulator.deinit();
    loader.deinit();

    return 0;
}