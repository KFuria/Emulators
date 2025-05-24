#include <stdlib.h>

#define SDL_MAIN_HANDLED

#include "i8080.h"
#include "logger.h"
#include "hal.h"

int main(){

    std::shared_ptr<TLogger> logger = TLogger::getInstance();
    

    THal hal;
    hal.write_byte(0x0000, 0x00);

    T8080 i8080;
    i8080.setHal(&hal);
    i8080.disassembleOp(0x0000);

    return 0;
}