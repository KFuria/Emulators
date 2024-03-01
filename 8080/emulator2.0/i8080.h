#ifndef I8080_H
#define I8080_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "memory.h"

typedef struct i8080
{
    uint8_t a, b, c, d, e, h, l; // registers
    uint16_t sp, pc;    //stack pointer, program counter

    bool sf : 1;    // sign
    bool zf : 1;    // zero
    bool hf : 1;    // half-carry
    bool pf : 1;    // parity 
    bool cf : 1;    // carry

    bool halted : 1; 
    
    

    // memory interface
    iMemory mem;




} i8080;


#endif