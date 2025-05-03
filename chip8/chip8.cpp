#include "chip8.h"
#include "cpu.h"

TChip8::TChip8(){
    logger = TLogger::getInstance();
    cpu = new TCpu(this);
    display = nullptr;
    keyboard = nullptr;
    sound = nullptr;
    emu_running = true;
}

TChip8::~TChip8(){

}

void TChip8::loadRom(std::string& file_path, uint8_t* mem){
    logger->log("Loading ROM: " + file_path, ELogLevel::INFO);
    
    std::ifstream file(file_path, std::ios::binary);
    if(!file){
        logger->log("Couldn't open file: " + file_path, ELogLevel::ERROR);
        exit(1);
    }

    file.seekg(0, std::ios::end);
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    if(file.read(reinterpret_cast<char*> (mem), size)){
        logger->log("File read successfully. Size: " + std::to_string(size) + " bytes.", ELogLevel::INFO);
    }
    else{
        logger->log("Error during file read", ELogLevel::ERROR);
        exit(1);
    }
    file.close();
}

void TChip8::init(std::string rom_path){
    // Clear screen frame buffer
    for(auto i = 0; i < SCREEN_HEIGHT; i++){
        for(auto j = 0; j < SCREEN_WIDTH; j++){
            screen[i][j] = 0;
        }
    }

    // Clear stack
    for(auto i = 0; i < STACK_SIZE; i++)
        stack[i] = 0;

    // Clear RAM
    for(auto i = 0; i < TOTAL_MEM; i++)
        memory[i] = 0;

    // Load font set into memory
    for(auto i = 0; i < FONTSET_SIZE; i++)
        memory[i] = FONTSET[i];

    // Reset timers
    delay_timer = 0;
    sound_timer = 0;

    // Set all keys state to unpressed
    for (auto i = 0; i < NUM_KEYS; i++)
        keys[i] = 0;

    key_pressed = false;

    // Initialize components
    cpu->init();
    display->init("CHIP-8 EMU", SCREEN_WIDTH, SCREEN_HEIGHT, DISPLAYSCALE);
    keyboard->init();
    sound->init();

     // Load ROM in memory
     TChip8::loadRom(rom_path, memory + PRGRM_START_ADDR);
}

void TChip8::deinit(){
    cpu->deinit();
    display->deinit();
    keyboard->deinit();
    sound->deinit();
}

void TChip8::run(){
    using clock = std::chrono::high_resolution_clock;
    clock::time_point start, end;
    const std::chrono::microseconds desired_cycle_time(1000); // 1000 instructions per second
    int display_update_delay_time = 0;

    while(emu_running){
        start = clock::now();

        // Execute a CPU cycle
    	cpu->cycle();
        
        if(display_update_delay_time >= 20){
            display->update(screen);
            display_update_delay_time = 0;
            
            // Update timers ~60Hz
        	if(delay_timer > 0)
                delay_timer--;

            if(sound_timer > 0){
                sound_timer--;
                sound->playSound();
            }
            else{
                sound->pauseSound();
            }
        }

        keyboard->update(keys, &emu_running);
        
        end = clock::now();
        std::chrono::duration<double, std::micro> loop_time = end - start;
        auto sleep_time = desired_cycle_time - loop_time;
        auto later = end + sleep_time;
        std::this_thread::sleep_until(later);
        display_update_delay_time++;
    }

}

void TChip8::setDisplay(TDisplayInterface* displayInterface){
    display = displayInterface;
}

void TChip8::setKeyboard(TKeyboard* keyboardInterface){
    keyboard = keyboardInterface;
}

void TChip8::setSound(TSound* soundInterface){
    sound = soundInterface;
}