#ifndef MEMORY_H
#define MEMORY_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct iMemory
{
    // Memory address
    void * mem;

    //ROM

    //RAM

    //VRAM


} iMemory;

uint8_t* imemory_init(uint8_t size, uint8_t num);
uint8_t imemory_read_byte(uint16_t addr);
void imemory_write_byte(uint16_t addr, uint8_t byte);
void imemory_free(void);

#endif