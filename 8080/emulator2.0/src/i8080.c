#include "i8080.h"
#include "utils.h"


i8080 * i8080_init(void){
    i8080 * cpu = calloc(1, sizeof(i8080));
    
    cpu->cpu_pointer = cpu; // pointer to cpu struct in memory

    cpu->read_byte = NULL;
    cpu->write_byte = NULL;
    cpu->port_in = NULL;
    cpu->port_out = NULL;

    i8080_clear_registers_counters(cpu);

    return cpu;
}


void i8080_clear_registers_counters(i8080* const cpu){
    cpu->a = 0;
    cpu->b = 0;
    cpu->c = 0;
    cpu->d = 0;
    cpu->e = 0;
    cpu->h = 0;
    cpu->l = 0;

    cpu->pc = 0;
    cpu->sp = 0;

    cpu->sf = 0;
    cpu->zf = 0;
    cpu->hf = 0;
    cpu->pf = 0;
    cpu->cf = 0;

    cpu->iff = 0;
    cpu->interrupt_pending = 0;
    cpu->interrupt_vector = 0;
    cpu->interrupt_delay = 0;

    cpu->halted = 0;
    cpu->cyc = 0;
}


void i8080_step(i8080 * const cpu){
    if (cpu->interrupt_pending && cpu->iff && cpu->interrupt_delay == 0) {
        cpu->interrupt_pending = 0;
        cpu->iff = 0;
        cpu->halted = 0;
        i8080_execute(cpu, cpu->interrupt_vector);
    } else if (!cpu->halted) {
        i8080_execute(cpu, i8080_next_byte(cpu));
    }
}


void i8080_interrupt(i8080* const cpu, uint8_t opcode) {
  cpu->interrupt_pending = 1;
  cpu->interrupt_vector = opcode;
}


void i8080_execute(i8080 * const cpu, uint8_t opcode){
    
}

