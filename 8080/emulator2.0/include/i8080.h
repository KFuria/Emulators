#ifndef I8080_H
#define I8080_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


typedef struct i8080
{
    uint8_t a, b, c, d, e, h, l; // registers
    uint16_t sp, pc;    //stack pointer, program counter

    bool sf : 1;    // sign
    bool zf : 1;    // zero
    bool hf : 1;    // half-carry
    bool pf : 1;    // parity 
    bool cf : 1;    // carry
   
    void * cpu_pointer;

    // memory interface
    uint8_t (* read_byte)(uint16_t);
    void (*write_byte)(uint16_t, uint8_t);

    // IO interface
    uint8_t (*port_in)(void *, uint8_t); 
    void (*port_out)(void *, uint8_t, uint8_t);

    bool iff : 1;
    bool interrupt_pending : 1;
    uint8_t interrupt_vector;
    uint8_t interrupt_delay;

    bool halted : 1; 
    unsigned long cyc; // cycle count

} i8080;

i8080 * i8080_init(void);
void i8080_clear_registers_counters(i8080* const cpu);
void i8080_step(i8080* const cpu);
void i8080_interrupt(i8080* const cpu, uint8_t opcode);
void i8080_execute(i8080 * const cpu, uint8_t opcode);

#endif