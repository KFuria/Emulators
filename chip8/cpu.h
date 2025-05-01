#ifndef __CPU_H__
#define __CPU_H__

#include <cstdint>
#include <sstream>
#include <iomanip>

#include "chip8.h"
#include "logger.h"

#define NUM_REGISTERS 16
#define PC_START 0x200

class TCpu{
    //registers
    uint8_t reg[NUM_REGISTERS];
    uint16_t I;
    uint16_t pc;
    uint16_t sp;

    uint16_t opcode;
    uint16_t instruction;

    TChip8* chip8;

    // Logging
    std::shared_ptr<TLogger> logger;

    //instructions
    void OP_0();
    void OP_8();
    void OP_E();
    void OP_F();
    void OP_00E0();
    void OP_00EE();
    void OP_1NNN();
    void OP_2NNN();
    void OP_3XNN();
    void OP_4XNN();
    void OP_5XY0();
    void OP_6XNN();
    void OP_7XNN();
    void OP_8XY0();
    void OP_8XY1();
    void OP_8XY2();
    void OP_8XY3();
    void OP_8XY4();
    void OP_8XY5();
    void OP_8XY6();
    void OP_8XY7();
    void OP_8XYE();
    void OP_9XY0();
    void OP_ANNN();
    void OP_BNNN();
    void OP_CXNN();
    void OP_DXYN();
    void OP_EX9E();
    void OP_EXA1();
    void OP_FX07();
    void OP_FX0A();
    void OP_FX15();
    void OP_FX18();
    void OP_FX1E();
    void OP_FX29();
    void OP_FX33();
    void OP_FX55();
    void OP_FX65();
    
public:
    TCpu(TChip8* machine);
    ~TCpu();
    void init();
    void fetch();
    void execute();
    void deinit();
};

#endif