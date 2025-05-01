#include <stdlib.h>

#define SDL_MAIN_HANDLED


#include "chip8.h"
#include "displaysdl.h"
#include "logger.h"

int main(){

    // SDL_Init(SDL_INIT_EVERYTHING);
    // SDL_Window* window = SDL_CreateWindow("Title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, SDL_WINDOW_SHOWN);
    // SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    // SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

    // SDL_RenderClear(renderer);

    // SDL_RenderPresent(renderer);

    // SDL_Delay(5000);

    std::shared_ptr<TLogger> logger = TLogger::getInstance();
    logger->setLogLevel(ELogLevel::DEBUG);

    TDisplaySDL display(0xFF, 0xFF, 0xFF);
    TChip8 emulator;

    emulator.setDisplay(&display);
    emulator.init("roms/demos/Maze.ch8");
    emulator.run();
    emulator.deinit();

    return 0;
}