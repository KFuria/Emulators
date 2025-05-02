#include <SDL2/SDL.h>
#include "keyboardSDL.h"

TKeyboardSDL::TKeyboardSDL(){
    logger = TLogger::getInstance();
}

TKeyboardSDL::~TKeyboardSDL(){

}

void TKeyboardSDL::update(uint8_t* keys, bool* running){
    SDL_Event e;
    if (SDL_PollEvent(&e) != 0){
        if (e.type == SDL_KEYDOWN){
            switch (e.key.keysym.sym){
                case SDLK_1: keys[0x1] = 1; break;
                case SDLK_2: keys[0x2] = 1; break;
                case SDLK_3: keys[0x3] = 1; break;
                case SDLK_4: keys[0xC] = 1; break;
                case SDLK_q: keys[0x4] = 1; break;
                case SDLK_w: keys[0x5] = 1; break;
                case SDLK_e: keys[0x6] = 1; break;
                case SDLK_r: keys[0xD] = 1; break;
                case SDLK_a: keys[0x7] = 1; break;
                case SDLK_s: keys[0x8] = 1; break;
                case SDLK_d: keys[0x9] = 1; break;
                case SDLK_f: keys[0xE] = 1; break;
                case SDLK_z: keys[0xA] = 1; break;
                case SDLK_x: keys[0x0] = 1; break;
                case SDLK_c: keys[0xB] = 1; break;
                case SDLK_v: keys[0xF] = 1; break;
                case SDLK_ESCAPE: *running = false; break;
            }
        }
        else if(e.type == SDL_KEYUP){
            switch (e.key.keysym.sym){
                case SDLK_1: keys[0x1] = 0; break;
                case SDLK_2: keys[0x2] = 0; break;
                case SDLK_3: keys[0x3] = 0; break;
                case SDLK_4: keys[0xC] = 0; break;
                case SDLK_q: keys[0x4] = 0; break;
                case SDLK_w: keys[0x5] = 0; break;
                case SDLK_e: keys[0x6] = 0; break;
                case SDLK_r: keys[0xD] = 0; break;
                case SDLK_a: keys[0x7] = 0; break;
                case SDLK_s: keys[0x8] = 0; break;
                case SDLK_d: keys[0x9] = 0; break;
                case SDLK_f: keys[0xE] = 0; break;
                case SDLK_z: keys[0xA] = 0; break;
                case SDLK_x: keys[0x0] = 0; break;
                case SDLK_c: keys[0xB] = 0; break;
                case SDLK_v: keys[0xF] = 0; break;
            }
        }
        else if (e.type == SDL_QUIT) 
            *running = false;       
    }
}

