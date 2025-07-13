#include <stdlib.h>
#include <string>
#include <format>

#include "logger.h"
#include "i8080.h"
#include "i8080_helpers.h"
#include "hal.h"


std::shared_ptr<TLogger> logger = TLogger::getInstance();

void run_test(T8080& i8080, THal& hal, std::string filename){
    // reset CPU
    i8080.reset();

    // read test ROM into memory
    hal.loadFile(filename, 0x100);

    i8080.setPC(0x100);
    hal.write_byte(0x0005, 0xD3);   // OUT
    hal.write_byte(0x0006, 0x01);   // 01
    hal.write_byte(0x0007, 0xC9);   // RET

    unsigned long num_instructions = 0;
    while(true){
        uint16_t pc = i8080.getPC();
        if(i8080.is_halted()){
            logger->log(std::format("8080 halted at 0x{:04X}", pc), ELogLevel::INFO);
            exit(1);
        }
        i8080.step();
        num_instructions += 1;

        if(i8080.getPC() == 0){
            std::cout << "\n";
            logger->log(std::format("Jump to 0000 from 0x{:04X}: 0x{:02X}", pc, hal.read_byte(pc)), ELogLevel::INFO);
            logger->log(std::format("Number of instructions executed: {}\n\n", num_instructions), ELogLevel::INFO);
            return;
        }
    }
}

int main(){
    T8080 i8080;
    THal hal;
    i8080.setHal(&hal);

    //Tests
    run_test(i8080, hal, "ROMs/8080PRE.COM");
    run_test(i8080, hal, "ROMs/TST8080.COM");
    run_test(i8080, hal, "ROMs/CPUTEST.COM");
    run_test(i8080, hal, "ROMs/8080EXM.COM");

    return 0;
}