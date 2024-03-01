#ifndef MEMORY_H
#define MEMORY_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef uint8_t * iMem;

iMem iMem_init(size_t size_in_bytes);

int load_file_into_Mem(const char * filename, uint16_t add);

uint8_t iMem_read_byte(uint16_t addr);

void iMem_write_byte(uint16_t addr, uint8_t byte);

void iMem_free(void);

#endif