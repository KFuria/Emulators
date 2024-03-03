#ifndef I8080_EMU_H_
#define I8080_EMU_H_

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct i8080 {
    uint8_t a, b, c, d, e, h, l; // registers;

    uint16_t sp, pc; //stack pointer, program counter

    //flags: sign, zero, half-carry (a.k.a Auxiliary Carry Flag), parity, carry, interrupt flip-flop
    bool sf : 1, zf : 1, hf : 1, pf : 1, cf : 1, iff : 1;
    bool halted : 1;

    uint8_t (*read_byte)(uint16_t); 
    void (*write_byte)(uint16_t, uint8_t); 
    uint8_t (*port_in)(void *, uint8_t); 
    void (*port_out)(void *, uint8_t, uint8_t);
    void* cpu_pointer;

    unsigned long cyc; // cycle count

    bool interrupt_pending : 1;
    uint8_t interrupt_vector;
    uint8_t interrupt_delay;
    
} i8080;

i8080 *i8080_init(void);
void i8080_clr(i8080 * const cpu);
void i8080_step(i8080* const cpu);
void i8080_interrupt(i8080* const cpu, uint8_t opcode);

#endif