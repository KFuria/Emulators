#ifndef __MEMORY_H__
#define __MEMORY_H__

#include <array>
#include <cstdint>

#include "logger.h"
#include "i8080_hal.h"

#define MAX_MEMORY 0x10000

class THal : public T8080Hal{
    std::shared_ptr<TLogger> logger;

    uint8_t m_data[MAX_MEMORY];

public:
    THal();
    ~THal();
    void loadFile(std::string filename);
    virtual uint8_t read_byte(uint16_t addr) override;
    virtual void write_byte(uint16_t addr, uint8_t byte) override;
    virtual uint8_t io_input(uint8_t port) override;
    virtual void io_output(uint8_t port, uint8_t value) override;
};


#endif