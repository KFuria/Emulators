#ifndef __I8080_HAL_H__
#define __I8080_HAL_H__

#include <array>
#include <cstdint>

#include "logger.h"

#define MAX_MEMORY 0x10000


class T8080Hal{

public: 
    virtual uint8_t read_byte(uint16_t addr) = 0;
    virtual void write_byte(uint16_t addr, uint8_t byte) = 0;
    virtual uint8_t io_input(uint8_t port) = 0;
    virtual void io_output(uint8_t port, uint8_t value) = 0;
};


#endif