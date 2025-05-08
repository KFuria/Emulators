#include <stdlib.h>

#define SDL_MAIN_HANDLED

#include "logger.h"
#include "chip8.h"
#include "displaysdl.h"
#include "keyboardSDL.h"
#include "soundSDL.h"

int main(){

    std::shared_ptr<TLogger> logger = TLogger::getInstance();
    logger->setLogLevel(ELogLevel::DEBUG);

    TDisplaySDL display;
    TKeyboardSDL keyboard;
    TSoundSDL sound;
    TChip8 emulator;

    emulator.setDisplay(&display);
    emulator.setKeyboard(&keyboard);
    emulator.setSound(&sound);
    emulator.init("roms/");
    emulator.load();
    emulator.run();
    emulator.deinit();

    return 0;
}