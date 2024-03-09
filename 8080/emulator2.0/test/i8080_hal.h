#ifndef I8080_HAL_h
#define I8080_HAL_h

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "i8080.h"

#define MEM_SIZE 0x10000 //8080 uses 16-bit addresses (0xFFFF + 1)

typedef uint8_t * iMem;

iMem iMem_init();
int load_file_into_Mem(const char * filename, uint16_t addr);
iMem iMem_free(void);

// Memory interfaces for i8080
uint8_t iMem_read_byte(uint16_t addr);
void iMem_write_byte(uint16_t addr, uint8_t byte);

// IO interfaces for i8080
uint8_t i8080_hal_io_input(void * cpu_pointer, uint8_t port);
void i8080_hal_io_output(void * cpu_pointer, uint8_t port, uint8_t value);


#endif