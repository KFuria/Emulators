#include <stdio.h>
#include <stdlib.h>
#include "i8080_hal.h"
#include "i8080emu.h"

#define MEMORY_SIZE 0x10000 //16K


static uint8_t * memory = NULL;

uint8_t i8080_hal_memory_read_byte(uint16_t addr) {
    return memory[addr];
}

void i8080_hal_memory_write_byte(uint16_t addr, uint8_t byte) {
    memory[addr] = byte;
}

uint8_t i8080_hal_io_input(void * cpu_pointer, uint8_t port) {
    return 0;
}

void i8080_hal_io_output(void * cpu_pointer, uint8_t port, uint8_t value) {
    i8080 * const cpu = (i8080*) cpu_pointer;
    if (port == 1) {
        if (cpu->c == 2) { // print a character stored in register E
            printf("%c", cpu->e);
        } else if (cpu->c == 9) {
            // print from memory at DE until '$' char 
            uint16_t addr = (cpu->d << 8) | cpu->e;
            do {
                printf("%c", i8080_hal_memory_read_byte(addr++));
            } while (i8080_hal_memory_read_byte(addr) != '$');
        }
    }
}

uint8_t* i8080_hal_memory_init(void){
    memory = malloc(MEMORY_SIZE);
    memset(memory, 0, MEMORY_SIZE);
    if(memory == NULL){
        fprintf(stderr, "Memory not created\n");
    }
    return memory;
}

void i8080_hal_memory_free(void){
    free(memory);
}

int load_file_into_memory(const char * name, uint16_t addr){
    FILE* f = fopen(name, "r+b");
    if (f==NULL){
        fprintf(stderr, "error: can't open file '%s'.\n", name);
        return 1;
    }

    //get file size
    fseek(f, 0, SEEK_END); // jump to the end of file
    size_t fsize = ftell(f);   // return the current position of f
    rewind(f); // jump back to the start of the file
    printf("File Size: %ld\n", fsize);

    if (fsize + addr >= MEMORY_SIZE){
        fprintf(stderr, "error: file %s can't fit in memory.\n", name);
        return 1;
    }

    //read  file into memory
    uint8_t * load_to = memory + addr;
    printf("File located at: 0x%p\n", load_to);
    size_t result = fread(&memory[addr], sizeof(uint8_t), fsize, f);
    if (result != fsize){
        fprintf(stderr, "error: while reading file '%s'\n", name);
        return 1;
    }

    fclose(f);
    return 0;
}