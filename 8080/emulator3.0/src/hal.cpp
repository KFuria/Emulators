#include "hal.h"

THal::THal(){
    m_data.fill(0x00);
    logger = TLogger::getInstance();
    logger->log("HAL Initialized", ELogLevel::INFO);
}

THal::~THal(){
    logger->log("HAL Deinitialized", ELogLevel::INFO);
}

void THal::loadFile(std::string file_path, uint16_t addr){
    logger->log("Loading ROM: " + file_path, ELogLevel::INFO);
    
    std::ifstream file(file_path, std::ios::binary);
    if(!file){
        logger->log("Couldn't open file: " + file_path, ELogLevel::ERROR);
        exit(1);
    }

    file.seekg(0, std::ios::end);
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    if(static_cast<uint32_t>(addr) + static_cast<uint32_t>(size) > m_data.size()){
        logger->log(std::format(
            "Error: ROM size ({} bytes) + start address (0x{:04X}) exceeds memory capacity ({} bytes).",
            size, addr, m_data.size()), ELogLevel::ERROR);
            exit(1);
    }

    if(file.read(reinterpret_cast<char *> (m_data.data() + addr), size)){
        logger->log(std::format(
            "File read successfully. Size: {} bytes loaded to 0x{:04X}", size, addr), ELogLevel::INFO);
    }
    else{
        logger->log("Error during file read", ELogLevel::ERROR);
        exit(1);
    }
    file.close();
}

uint8_t THal::read_byte(uint16_t addr){
    return m_data[addr];
}

void THal::write_byte(uint16_t addr, uint8_t byte){
    m_data[addr] = byte;
}

uint8_t THal::io_input(void * i8080, uint8_t port){
    (void) i8080;
    in_port_reads[port]++;
    if (!in_port_data[port].empty()) {
        uint8_t data = in_port_data[port].front();
        in_port_data[port].erase(in_port_data[port].begin());
        return data;
    }
    return 0xFF;
}

void THal::io_output(void * i8080_ptr, uint8_t port, uint8_t value){
    
    // // out_ports[port].push_back(value);
    
    (void) value;
    // Output logic for ROM test
    T8080 * const i8080 = (T8080 *) i8080_ptr;
    if(port == 1){
        if(i8080->getC() == 2){
            printf("%c", i8080->getE());
        }
        else if(i8080->getC() == 9){
            uint16_t addr = i8080->getDE();
            while(read_byte(addr) != '$'){
                printf("%c", read_byte(addr++));
            }
        }
    }
}

// Helper for tests to pre-load IN port data
void THal::set_in_port_data(uint8_t port, const std::vector<uint8_t>& data) {
    in_port_data[port] = data;
}

