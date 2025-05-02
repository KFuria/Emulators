#ifndef __CHIP8_H__
#define __CHIP8_H__

#include <cstdint>
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>

#include "logger.h"
#include "display.h"
#include "keyboard.h"


#define TOTAL_MEM 4096
#define STACK_SIZE 16
#define TIMER_MAX 255
#define NUM_KEYS 16

#define CHIP8_RAM_START_ADDR 0x000
#define CHIP8_RAM_END_ADDR 0x1FF
#define PRGRM_START_ADDR 0x200
#define PRGRM_END_ADDR 0xFFF

#define SCREEN_WIDTH 64
#define SCREEN_HEIGHT 32
#define DISPLAYSCALE 20

#define FONTSET_SIZE 80
const static uint8_t FONTSET[] = { 
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

class TCpu;

class TChip8{
    friend class TCpu;

    TCpu* cpu;
    TDisplayInterface* display;

    TKeyboard* keyboard;

    uint8_t memory[TOTAL_MEM];
    uint16_t stack[STACK_SIZE];

    uint8_t screen[SCREEN_HEIGHT][SCREEN_WIDTH];
    
    uint8_t keys[NUM_KEYS];
    bool key_pressed;
    
    uint8_t delay_timer;
    uint8_t sound_timer;

    bool emu_running;

    // Logging
    std::shared_ptr<TLogger> logger;

    void loadRom(std::string& file_path, uint8_t* mem);

public:
    TChip8();
    ~TChip8();
    void setDisplay(TDisplayInterface* display);
    void setKeyboard(TKeyboard* keyboardInterface);
    void init(std::string rom_path);
    void run();
    void deinit();
};


#endif