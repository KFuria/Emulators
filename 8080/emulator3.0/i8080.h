#ifndef __I8080_H__
#define __I8080_H__

#include <cstddef>
#include <cstdint>
#include <array>
#include <iostream>
#include <fstream>
#include <string>
#include <format>

#include "logger.h"
#include "i8080_hal.h"

class T8080{
    std::shared_ptr<TLogger> logger;

    uint8_t A, B, C, D, E, H, L;    // registers
    uint16_t SP;                    // Stack pointer 
    uint16_t PC;                    // Program counter

    bool INTE;                       // interrupt bit
    
    T8080Hal * hal;

public:
    T8080();
    ~T8080();
    int disassembleOp(int pc);
    void setHal(T8080Hal * Hal);

};



#endif