#ifndef IMEMORY_H
#define IMEMORY_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define MEM_SIZE 0x10000 //8080 uses 16-bit addresses (0xFFFF + 1)

typedef uint8_t * iMem;

iMem iMem_init();

int load_file_into_Mem(const char * filename, uint16_t addr);

uint8_t iMem_read_byte(uint16_t addr);

void iMem_write_byte(uint16_t addr, uint8_t byte);

void iMem_free(void);

#endif