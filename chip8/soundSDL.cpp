#include <SDL2/SDL.h>
#include "soundSDL.h"

// Constants
const int SAMPLE_RATE = 44100; 
const int AMPLITUDE = 28000;
const double FREQUENCY = 440.0; // sine wave (A4)

TSoundSDL::TSoundSDL(){
    logger = TLogger::getInstance();
    logger->log("Sound Constructed", ELogLevel::DEBUG);
}

TSoundSDL::~TSoundSDL(){
    logger->log("Sound Destructed", ELogLevel::DEBUG);
}

void audioCallback(void* userdata, Uint8* stream, int len) {
    static double phase = 0.0;
    (void)userdata;
    double increment = (2.0 * std::numbers::pi * FREQUENCY) / SAMPLE_RATE;

    for (int i = 0; i < len; i += 2){
        short sample = static_cast<short>(AMPLITUDE * sin(phase));
        phase += increment;

        if (phase > 2.0 * std::numbers::pi){
            phase -= 2.0 * std::numbers::pi;
        }

        stream[i] = sample & 0xFF;       // Low byte
        stream[i + 1] = (sample >> 8) & 0xFF; // High byte
    }
}

void TSoundSDL::init(){
    if (SDL_Init(SDL_INIT_AUDIO) < 0){
        std::string errorSdl(SDL_GetError());
        logger->log("SDL Sound Initialization Error: " + errorSdl, ELogLevel::ERROR);
        exit(1);
    }
    audioSpec.freq = SAMPLE_RATE;
    audioSpec.format = AUDIO_S16SYS;
    audioSpec.channels = 1;
    audioSpec.samples = 4096;
    audioSpec.callback = audioCallback;
    audioSpec.userdata = nullptr;

    logger->log("Connecting to audio device", ELogLevel::INFO);
    if (SDL_OpenAudio(&audioSpec, nullptr) < 0){
        std::string errorSdl(SDL_GetError());
        logger->log("Failed to open audio device: " + errorSdl, ELogLevel::ERROR);
    }
    logger->log("Sound Initialized", ELogLevel::DEBUG);
}

void TSoundSDL::deinit(){
    SDL_CloseAudio();
    SDL_Quit();
    logger->log("Sound Deinitialized", ELogLevel::DEBUG);
}

void TSoundSDL::playSound(){
    SDL_PauseAudio(0);
}

void TSoundSDL::pauseSound(){
    SDL_PauseAudio(1);
}

