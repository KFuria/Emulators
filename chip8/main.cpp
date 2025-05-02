#include <stdlib.h>

#define SDL_MAIN_HANDLED


#include "chip8.h"
#include "displaysdl.h"
#include "logger.h"
#include "keyboardSDL.h"

int main(){

    std::shared_ptr<TLogger> logger = TLogger::getInstance();
    logger->setLogLevel(ELogLevel::DEBUG);

    TDisplaySDL display(0xFF, 0xFF, 0xFF);
    TKeyboardSDL keyboard;
    TChip8 emulator;

    emulator.setDisplay(&display);
    emulator.setKeyboard(&keyboard);
    emulator.init("roms/games/Astro Dodge [Revival Studios, 2008].ch8");
    emulator.run();
    emulator.deinit();

    return 0;
}