#ifndef __MEMORY_H__
#define __MEMORY_H__

#include <array>
#include <cstdint>
#include <vector>
#include <format>

#include "logger.h"
#include "i8080_hal.h"
#include "i8080.h"
#include "i8080_helpers.h"

class THal : public T8080Hal{
public:
    virtual uint8_t read_byte(uint16_t addr) override;
    virtual void write_byte(uint16_t addr, uint8_t byte) override;
    virtual uint8_t io_input(void * i8080, uint8_t port) override;
    virtual void io_output(void * i8080, uint8_t port, uint8_t value) override;
    

    THal();
    ~THal();
    void loadFile(std::string filename, uint16_t addr);
    void set_in_port_data(uint8_t port, const std::vector<uint8_t>& data);

private:
    std::shared_ptr<TLogger> logger;
    std::array<uint8_t, MAX_MEMORY> m_data;
    std::vector<uint8_t> out_ports[256]; // To track data written to OUT ports
    std::vector<uint8_t> in_port_data[256]; // Data to be returned by IN ports
    int in_port_reads[256] = {0}; // Counter for IN port reads
};


#endif