#include "hal.h"

THal::THal() : 
    m_data{} {
    logger = TLogger::getInstance();
    logger->log("HAL Initialized", ELogLevel::INFO);
}

THal::~THal(){
    logger->log("HAL Deinitialized", ELogLevel::INFO);
}

void THal::loadFile(std::string file_path){
    logger->log("Loading ROM: " + file_path, ELogLevel::INFO);
    
    std::ifstream file(file_path, std::ios::binary);
    if(!file){
        logger->log("Couldn't open file: " + file_path, ELogLevel::ERROR);
        exit(1);
    }

    file.seekg(0, std::ios::end);
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    if(file.read(reinterpret_cast<char *> (m_data), size)){
        logger->log("File read successfully. Size: " + std::to_string(size) + " bytes.", ELogLevel::INFO);
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

uint8_t THal::io_input(uint8_t port){

}

void THal::io_output(uint8_t port, uint8_t value){

}