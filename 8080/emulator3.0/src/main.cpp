#include <stdlib.h>

#include "i8080.h"
#include "logger.h"
#include "hal.h"

int main(){

    std::shared_ptr<TLogger> logger = TLogger::getInstance();

    THal hal;
    T8080 i8080;
    i8080.setHal(&hal);

    //Tests
    hal.write_byte(0x0000, 0x01);
    hal.write_byte(0x0001, 0xAA);
    hal.write_byte(0x0002, 0xBB);
    i8080.step();
    
    hal.write_byte(0x0003, 0x11);
    hal.write_byte(0x0004, 0xAA);
    hal.write_byte(0x0005, 0xBB);
    i8080.step();
    return 0;
}