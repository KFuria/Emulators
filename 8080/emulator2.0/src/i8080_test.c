#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "utils.h"
#include "i8080dis.h"
#include "i8080.h"
#include "i8080_hal.h"

#define DEBUG 0

static void run_test(i8080 * const cpu, const char * filename){
    // clear registers and counters
    i8080_clear_registers_counters(cpu);

    // initialize memory for test
    iMem mem = iMem_init();

    // read test ROM into memory
    if(load_file_into_Mem(filename, 0x100) != 0){
        return;
    }
    printf("TEST: %s\n", filename);
    printf("***************************************************\n");

    //set the pc to starting of program
    cpu->pc = 0x100;

    // set intruction "out 1,a" at 0x0005 (signal to output some characters)
    mem[0x0005] = 0xD3;
    mem[0x0006] = 0x01;
    mem[0x0007] = 0xC9;

    unsigned long num_instructions = 0;
    while (1) {
        int const pc = cpu->pc;
        // if HLT exit test
        if (cpu->halted == 1) {
            printf("HLT at %04X\n", pc);
            exit(1);
        }
        // use with gdb to debug
        if(DEBUG){
            printf("SP:0x%04X, 0x%04X: 0x%02X  ",cpu->sp, cpu->pc, mem[cpu->pc]);
            Disassemble8080Op(mem, cpu->pc);
        }

        i8080_step(cpu);
        num_instructions += 1;
        
        // End of test
        if(cpu->pc == 0){
            printf("\nJump to 0000 from %04X: %02X\n", pc, mem[pc]);
            printf("Number of Instructions executed: %ld\n", num_instructions);
            printf("***************************************************\n\n\n");
            return;
        }
    }
    // free memory
    mem = iMem_free();

}


int main(){
    //i8080 cpu
    i8080 * cpu = i8080_init();

    //set IO and memory interfaces for test
    cpu->read_byte = iMem_read_byte;
    cpu->write_byte = iMem_write_byte;
    cpu->port_in = i8080_hal_io_input;
    cpu->port_out = i8080_hal_io_output;

    // Run ROM Tests
    run_test(cpu, "src/ROMs/8080PRE.COM");
    run_test(cpu, "src/ROMs/TST8080.COM");
    run_test(cpu, "src/ROMs/CPUTEST.COM");
    run_test(cpu, "src/ROMs/8080EXM.COM");
}