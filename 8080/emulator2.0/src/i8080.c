#include "i8080.h"
#include "utils.c"


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
    cpu->cyc += OPCODES_CYCLES[opcode];

    if (cpu->interrupt_delay > 0) {
        cpu->interrupt_delay -= 1;
    }

    switch(opcode){
        //MOV INSTRUCTIONS
        case 0x06: cpu->b = i8080_next_byte(cpu); break; // MVI B,byte
        case 0x16: cpu->d = i8080_next_byte(cpu); break; // MVI D,byte
        case 0x26: cpu->h = i8080_next_byte(cpu); break; // MVI H,byte
        case 0x36: i8080_write_byte(cpu, i8080_get_hl(cpu), i8080_next_byte(cpu)); break; // MVI M,byte
        case 0x0E: cpu->c = i8080_next_byte(cpu); break; // MVI C,byte
        case 0x1E: cpu->e = i8080_next_byte(cpu); break; // MVI E,byte
        case 0x2E: cpu->l = i8080_next_byte(cpu); break; // MVI L,byte
        case 0x3E: cpu->a = i8080_next_byte(cpu); break; // MVI A,byte

        case 0x40: cpu->b = cpu->b; break;  //MOV B, B
        case 0x41: cpu->b = cpu->c; break;  //MOV B, C
        case 0x42: cpu->b = cpu->d; break;  //MOV B, D
        case 0x43: cpu->b = cpu->e; break;  //MOV B, E
        case 0x44: cpu->b = cpu->h; break;  //MOV B, H
        case 0x45: cpu->b = cpu->l; break;  //MOV B, L
        case 0x46: cpu->b = i8080_read_byte(cpu, i8080_get_hl(cpu)); break;  //MOV B, M
        case 0x47: cpu->b = cpu->a; break;  //MOV B, A
        
        case 0x48: cpu->c = cpu->b; break;  //MOV C, B
        case 0x49: cpu->c = cpu->c; break;  //MOV C, C
        case 0x4A: cpu->c = cpu->d; break;  //MOV C, D
        case 0x4B: cpu->c = cpu->e; break;  //MOV C, E
        case 0x4C: cpu->c = cpu->h; break;  //MOV C, H
        case 0x4D: cpu->c = cpu->l; break;  //MOV C, L
        case 0x4E: cpu->c = i8080_read_byte(cpu, i8080_get_hl(cpu)); break;  //MOV C, M
        case 0x4F: cpu->c = cpu->a; break;  //MOV C, A

        case 0x50: cpu->d = cpu->b; break;  //MOV D, B
        case 0x51: cpu->d = cpu->c; break;  //MOV D, C
        case 0x52: cpu->d = cpu->d; break;  //MOV D, D
        case 0x53: cpu->d = cpu->e; break;  //MOV D, E
        case 0x54: cpu->d = cpu->h; break;  //MOV D, H
        case 0x55: cpu->d = cpu->l; break;  //MOV D, L
        case 0x56: cpu->d = i8080_read_byte(cpu, i8080_get_hl(cpu)); break;  //MOV D, M
        case 0x57: cpu->d = cpu->a; break;  //MOV D, A

        case 0x58: cpu->e = cpu->b; break;  //MOV E, B
        case 0x59: cpu->e = cpu->c; break;  //MOV E, C
        case 0x5A: cpu->e = cpu->d; break;  //MOV E, D
        case 0x5B: cpu->e = cpu->e; break;  //MOV E, E
        case 0x5C: cpu->e = cpu->h; break;  //MOV E, H
        case 0x5D: cpu->e = cpu->l; break;  //MOV E, L
        case 0x5E: cpu->e = i8080_read_byte(cpu, i8080_get_hl(cpu)); break;  //MOV E, M
        case 0x5F: cpu->e = cpu->a; break;  //MOV E, A

        case 0x60: cpu->h = cpu->b; break;  //MOV H, B
        case 0x61: cpu->h = cpu->c; break;  //MOV H, C
        case 0x62: cpu->h = cpu->d; break;  //MOV H, D
        case 0x63: cpu->h = cpu->e; break;  //MOV H, E
        case 0x64: cpu->h = cpu->h; break;  //MOV H, H
        case 0x65: cpu->h = cpu->l; break;  //MOV H, L
        case 0x66: cpu->h = i8080_read_byte(cpu, i8080_get_hl(cpu)); break;  //MOV H, M
        case 0x67: cpu->h = cpu->a; break;  //MOV H, A

        case 0x68: cpu->l = cpu->b; break;  //MOV L, B
        case 0x69: cpu->l = cpu->c; break;  //MOV L, C
        case 0x6A: cpu->l = cpu->d; break;  //MOV L, D
        case 0x6B: cpu->l = cpu->e; break;  //MOV L, E
        case 0x6C: cpu->l = cpu->h; break;  //MOV L, H
        case 0x6D: cpu->l = cpu->l; break;  //MOV L, L
        case 0x6E: cpu->l = i8080_read_byte(cpu, i8080_get_hl(cpu)); break;  //MOV L, M
        case 0x6F: cpu->l = cpu->a; break;  //MOV L, A

        case 0x70: i8080_write_byte(cpu, i8080_get_hl(cpu), cpu->b); break;  //MOV M, B
        case 0x71: i8080_write_byte(cpu, i8080_get_hl(cpu), cpu->c); break;  //MOV M, C
        case 0x72: i8080_write_byte(cpu, i8080_get_hl(cpu), cpu->d); break;  //MOV M, D
        case 0x73: i8080_write_byte(cpu, i8080_get_hl(cpu), cpu->e); break;  //MOV M, E
        case 0x74: i8080_write_byte(cpu, i8080_get_hl(cpu), cpu->h); break;  //MOV M, H
        case 0x75: i8080_write_byte(cpu, i8080_get_hl(cpu), cpu->l); break;  //MOV M, L
        case 0x77: i8080_write_byte(cpu, i8080_get_hl(cpu), cpu->a); break;  //MOV M, A

        case 0x78: cpu->a = cpu->b; break;  //MOV A, B
        case 0x79: cpu->a = cpu->c; break;  //MOV A, C
        case 0x7A: cpu->a = cpu->d; break;  //MOV A, D 
        case 0x7B: cpu->a = cpu->e; break;  //MOV A, E
        case 0x7C: cpu->a = cpu->h; break;  //MOV A, H
        case 0x7D: cpu->a = cpu->l; break;  //MOV A, L
        case 0x7E: cpu->a = i8080_read_byte(cpu, i8080_get_hl(cpu)); break;  //MOV A, M
        case 0x7F: cpu->a = cpu->a; break;  //MOV A, A

        case 0xE3: i8080_xthl(cpu); break; // XTHL
        case 0xEB: i8080_xchg(cpu); break; // XCHG

        // LOAD & STORE INSTRUCTIONS
        case 0x01: i8080_set_bc(cpu, i8080_next_word(cpu)); break;   //LXI B, word
        case 0x11: i8080_set_de(cpu, i8080_next_word(cpu)); break; // LXI D,word
        case 0x21: i8080_set_hl(cpu, i8080_next_word(cpu)); break; // LXI H,word
        case 0x31: cpu->sp = i8080_next_word(cpu); break; // LXI SP,word

        case 0x0A: cpu->a = i8080_read_byte(cpu, i8080_get_bc(cpu)); break; //LDAX B
        case 0x1A: cpu->a = i8080_read_byte(cpu, i8080_get_de(cpu)); break; // LDAX D
        case 0x2A: i8080_set_hl(cpu, i8080_read_word(cpu, i8080_next_word(cpu))); break; //LHLD
        case 0x3A: cpu->a = i8080_read_byte(cpu, i8080_next_word(cpu)); break; //LDA 

        case 0x02: i8080_write_byte(cpu, i8080_get_bc(cpu), cpu->a); break; //STAX B
        case 0x12: i8080_write_byte(cpu, i8080_get_de(cpu), cpu->a); break; //STAX D
        case 0x22: i8080_write_word(cpu, i8080_next_word(cpu), i8080_get_hl(cpu)); break; //SHLD
        case 0x32: i8080_write_byte(cpu, i8080_next_word(cpu), cpu->a); break; //STA

        //STACK INSTRUCTIONS
        case 0xC1: i8080_set_bc(cpu, i8080_pop_word_stack(cpu)); break; //POP B
        case 0xD1: i8080_set_de(cpu, i8080_pop_word_stack(cpu)); break; //POP D
        case 0xE1: i8080_set_hl(cpu, i8080_pop_word_stack(cpu)); break; //POP H
        case 0xF1: i8080_pop_psw(cpu); break; //POP PSW

        case 0xC5: i8080_push_word_stack(cpu, i8080_get_bc(cpu)); break; //PUSH B
        case 0xD5: i8080_push_word_stack(cpu, i8080_get_de(cpu)); break; //PUSH D
        case 0xE5: i8080_push_word_stack(cpu, i8080_get_hl(cpu)); break; //PUSH H
        case 0xF5: i8080_push_psw(cpu); break; //PUSH PSW

        case 0xF9: cpu->sp = i8080_get_hl(cpu); break;  //SPHL
        case 0xE9: cpu->pc = i8080_get_hl(cpu); break;  //PCHL

        // JUMP, CALL & RET INSTRUCTIONS
        case 0xC3: i8080_jmp(cpu, i8080_next_word(cpu)); break; //JMP
        case 0xC2: i8080_jmp_cond(cpu, cpu->zf==0); break; //JNZ
        case 0xD2: i8080_jmp_cond(cpu, cpu->cf==0); break; //JNC
        case 0xE2: i8080_jmp_cond(cpu, cpu->pf==0); break; //JPO
        case 0xF2: i8080_jmp_cond(cpu, cpu->sf==0); break; //JP
        case 0xCA: i8080_jmp_cond(cpu, cpu->zf==1); break; //JZ
        case 0xDA: i8080_jmp_cond(cpu, cpu->cf==1); break; //JC
        case 0xEA: i8080_jmp_cond(cpu, cpu->pf==1); break; //JPE
        case 0xFA: i8080_jmp_cond(cpu, cpu->sf==1); break; //JM
        
        case 0xCD: i8080_call(cpu, i8080_next_word(cpu)); break; //CALL
        case 0xC4: i8080_call_cond(cpu, cpu->zf==0); break; //CNZ
        case 0xD4: i8080_call_cond(cpu, cpu->cf==0); break; //CNC
        case 0xE4: i8080_call_cond(cpu, cpu->pf==0); break; //CPO
        case 0xF4: i8080_call_cond(cpu, cpu->sf==0); break; //CP
        case 0xCC: i8080_call_cond(cpu, cpu->zf==1); break; //CZ
        case 0xDC: i8080_call_cond(cpu, cpu->cf==1); break; //CC
        case 0xEC: i8080_call_cond(cpu, cpu->pf==1); break; //CPE
        case 0xFC: i8080_call_cond(cpu, cpu->sf==1); break; //CM

        case 0xC9: i8080_ret(cpu); break; // RET
        case 0xC0: i8080_ret_cond(cpu, cpu->zf==0); break; //RNZ
        case 0xD0: i8080_ret_cond(cpu, cpu->cf==0); break; //RNC
        case 0xE0: i8080_ret_cond(cpu, cpu->pf==0); break; //RPO
        case 0xF0: i8080_ret_cond(cpu, cpu->sf==0); break; //RP
        case 0xC8: i8080_ret_cond(cpu, cpu->zf==1); break; //RZ
        case 0xD8: i8080_ret_cond(cpu, cpu->cf==1); break; //RC
        case 0xE8: i8080_ret_cond(cpu, cpu->pf==1); break; //RPE
        case 0xF8: i8080_ret_cond(cpu, cpu->sf==1); break; //RM

        

        // ARITHMETIC LOGICAL INSTRUCTIONS
        case 0x80: i8080_add(cpu, cpu->b, 0); break; // ADD B
        case 0x81: i8080_add(cpu, cpu->c, 0); break; // ADD C
        case 0x82: i8080_add(cpu, cpu->d, 0); break; // ADD D
        case 0x83: i8080_add(cpu, cpu->e, 0); break; // ADD E
        case 0x84: i8080_add(cpu, cpu->h, 0); break; // ADD H
        case 0x85: i8080_add(cpu, cpu->l, 0); break; // ADD L
        case 0x86: i8080_add(cpu, i8080_read_byte(cpu, i8080_get_hl(cpu)), 0); break; //ADD M
        case 0x87: i8080_add(cpu, cpu->a, 0); break; //ADD A

        case 0x88: i8080_add(cpu, cpu->b, cpu->cf); break; // ADC B
        case 0x89: i8080_add(cpu, cpu->c, cpu->cf); break; // ADC C
        case 0x8A: i8080_add(cpu, cpu->d, cpu->cf); break; // ADC D
        case 0x8B: i8080_add(cpu, cpu->e, cpu->cf); break; // ADC E
        case 0x8C: i8080_add(cpu, cpu->h, cpu->cf); break; // ADC H
        case 0x8D: i8080_add(cpu, cpu->l, cpu->cf); break; // ADC L
        case 0x8E: i8080_add(cpu, i8080_read_byte(cpu, i8080_get_hl(cpu)), cpu->cf); break; //ADC M
        case 0x8F: i8080_add(cpu, cpu->a, cpu->cf); break; //ADC A

        case 0xC6: i8080_add(cpu, i8080_next_byte(cpu), 0); break; //ADI
        case 0xCE: i8080_add(cpu, i8080_next_byte(cpu), cpu->cf); break; //ACI

        case 0x90: i8080_sub(cpu, cpu->b, 0); break; // SUB B
        case 0x91: i8080_sub(cpu, cpu->c, 0); break; // SUB C
        case 0x92: i8080_sub(cpu, cpu->d, 0); break; // SUB D
        case 0x93: i8080_sub(cpu, cpu->e, 0); break; // SUB E
        case 0x94: i8080_sub(cpu, cpu->h, 0); break; // SUB H
        case 0x95: i8080_sub(cpu, cpu->l, 0); break; // SUB L
        case 0x96: i8080_sub(cpu, i8080_read_byte(cpu, i8080_get_hl(cpu)), 0); break; // SUB M
        case 0x97: i8080_sub(cpu, cpu->a, 0); break; // SUB A

        case 0x98: i8080_sub(cpu, cpu->b, cpu->cf); break; // SBB B
        case 0x99: i8080_sub(cpu, cpu->c, cpu->cf); break; // SBB C
        case 0x9a: i8080_sub(cpu, cpu->d, cpu->cf); break; // SBB D
        case 0x9b: i8080_sub(cpu, cpu->e, cpu->cf); break; // SBB E
        case 0x9c: i8080_sub(cpu, cpu->h, cpu->cf); break; // SBB H
        case 0x9d: i8080_sub(cpu, cpu->l, cpu->cf); break; // SBB L
        case 0x9e: i8080_sub(cpu, i8080_read_byte(cpu, i8080_get_hl(cpu)), cpu->cf); break; //SBB M
        case 0x9F: i8080_sub(cpu, cpu->a, cpu->cf); break; //SBB A

        case 0xD6: i8080_sub(cpu, i8080_next_byte(cpu), 0); break; //SUI
        case 0xDE: i8080_sub(cpu, i8080_next_byte(cpu), cpu->cf); break; //SBI

        case 0xA0: i8080_ana(cpu, cpu->b); break; // ANA B
        case 0xA1: i8080_ana(cpu, cpu->c); break; // ANA C
        case 0xA2: i8080_ana(cpu, cpu->d); break; // ANA D
        case 0xA3: i8080_ana(cpu, cpu->e); break; // ANA E
        case 0xA4: i8080_ana(cpu, cpu->h); break; // ANA H
        case 0xA5: i8080_ana(cpu, cpu->l); break; // ANA L
        case 0xA6: i8080_ana(cpu, i8080_read_byte(cpu, i8080_get_hl(cpu))); break; // ANA M
        case 0xA7: i8080_ana(cpu, cpu->a); break; // ANA A
        case 0xE6: i8080_ana(cpu, i8080_next_byte(cpu)); break; //ANI

        case 0xA8: i8080_xra(cpu, cpu->b); break; // XRA B
        case 0xA9: i8080_xra(cpu, cpu->c); break; // XRA C
        case 0xAA: i8080_xra(cpu, cpu->d); break; // XRA D
        case 0xAB: i8080_xra(cpu, cpu->e); break; // XRA E
        case 0xAC: i8080_xra(cpu, cpu->h); break; // XRA H
        case 0xAD: i8080_xra(cpu, cpu->l); break; // XRA L
        case 0xAE: i8080_xra(cpu, i8080_read_byte(cpu, i8080_get_hl(cpu))); break; // XRA M
        case 0xAF: i8080_xra(cpu, cpu->a); break; // XRA A
        case 0xEE: i8080_xra(cpu, i8080_next_byte(cpu)); break; //XRI

        case 0xB0: i8080_ora(cpu, cpu->b); break; // ORA B
        case 0xB1: i8080_ora(cpu, cpu->c); break; // ORA C
        case 0xB2: i8080_ora(cpu, cpu->d); break; // ORA D
        case 0xB3: i8080_ora(cpu, cpu->e); break; // ORA E
        case 0xB4: i8080_ora(cpu, cpu->h); break; // ORA H
        case 0xB5: i8080_ora(cpu, cpu->l); break; // ORA L
        case 0xB6: i8080_ora(cpu, i8080_read_byte(cpu, i8080_get_hl(cpu))); break; // ORA M
        case 0xB7: i8080_ora(cpu, cpu->a); break; // ORA A
        case 0xF6: i8080_ora(cpu, i8080_next_byte(cpu)); break; //ORI

        case 0xB8: i8080_cmp(cpu, cpu->b); break; // CMP B
        case 0xB9: i8080_cmp(cpu, cpu->c); break; // CMP C
        case 0xBA: i8080_cmp(cpu, cpu->d); break; // CMP D
        case 0xBB: i8080_cmp(cpu, cpu->e); break; // CMP E
        case 0xBC: i8080_cmp(cpu, cpu->h); break; // CMP H
        case 0xBD: i8080_cmp(cpu, cpu->l); break; // CMP L
        case 0xBE: i8080_cmp(cpu, i8080_read_byte(cpu, i8080_get_hl(cpu))); break; // CMP M
        case 0xBF: i8080_cmp(cpu, cpu->a); break; // CMP A
        case 0xFE: i8080_cmp(cpu, i8080_next_byte(cpu)); break; //CPI

        case 0x03: i8080_set_bc(cpu, i8080_get_bc(cpu) + 1); break; //INX B
        case 0x13: i8080_set_de(cpu, i8080_get_de(cpu) + 1); break; //INX D
        case 0x23: i8080_set_hl(cpu, i8080_get_hl(cpu) + 1); break; //INX H
        case 0x33: cpu->sp = cpu->sp + 1; break; //INX SP

        case 0x0B: i8080_set_bc(cpu, i8080_get_bc(cpu) - 1); break; //DCX B
        case 0x1B: i8080_set_de(cpu, i8080_get_de(cpu) - 1); break; //DCX D
        case 0x2B: i8080_set_hl(cpu, i8080_get_hl(cpu) - 1); break; //DCX H
        case 0x3B: cpu->sp = cpu->sp - 1; break; //DCX SP

        case 0x09: i8080_dad(cpu, i8080_get_bc(cpu)); break; //DAD B
        case 0x19: i8080_dad(cpu, i8080_get_de(cpu)); break; //DAD D
        case 0x29: i8080_dad(cpu, i8080_get_hl(cpu)); break; //DAD H
        case 0x39: i8080_dad(cpu, cpu->sp); break; //DAD SP

        case 0x04: cpu->b = i8080_inr(cpu, cpu->b); break; //INR B
        case 0x14: cpu->d = i8080_inr(cpu, cpu->d); break; //INR D
        case 0x24: cpu->h = i8080_inr(cpu, cpu->h); break; //INR H
        case 0x34: i8080_write_byte(cpu, i8080_get_hl(cpu), i8080_inr(cpu, i8080_read_byte(cpu, i8080_get_hl(cpu)))); break; //INR M
        case 0x0C: cpu->c = i8080_inr(cpu, cpu->c); break; //INR C
        case 0x1C: cpu->e = i8080_inr(cpu, cpu->e); break; //INR E
        case 0x2C: cpu->l = i8080_inr(cpu, cpu->l); break; //INR L
        case 0x3C: cpu->a = i8080_inr(cpu, cpu->a); break; //INR A

        case 0x05: cpu->b = i8080_dcr(cpu, cpu->b); break; //DCR B
        case 0x15: cpu->d = i8080_dcr(cpu, cpu->d); break; //DCR D
        case 0x25: cpu->h = i8080_dcr(cpu, cpu->h); break; //DCR H
        case 0x35: i8080_write_byte(cpu, i8080_get_hl(cpu), i8080_dcr(cpu, i8080_read_byte(cpu, i8080_get_hl(cpu)))); break; //DCR M
        case 0x0D: cpu->c = i8080_dcr(cpu, cpu->c); break; //DCR C
        case 0x1D: cpu->e = i8080_dcr(cpu, cpu->e); break; //DCR E
        case 0x2D: cpu->l = i8080_dcr(cpu, cpu->l); break; //DCR L
        case 0x3D: cpu->a = i8080_dcr(cpu, cpu->a); break; //DCR A

        

        case 0x07: i8080_rlc(cpu); break; //RLC
        case 0x17: i8080_ral(cpu); break; //RAL
        case 0x27: i8080_daa(cpu); break; //DAA
        case 0x37: cpu->cf = 1; break;    //STC

        case 0x0F: i8080_rrc(cpu); break;       //RLC
        case 0x1F: i8080_rar(cpu); break;       //RAL
        case 0x2F: cpu->a = ~cpu->a; break;     //CMA
        case 0x3F: cpu->cf = !cpu->cf; break;   //CMC

        // RESET INSTRUCTIONS
        case 0xC7: i8080_call(cpu, 0x00); break; // RST 0
        case 0xCF: i8080_call(cpu, 0x08); break; // RST 1
        case 0xD7: i8080_call(cpu, 0x10); break; // RST 2
        case 0xDF: i8080_call(cpu, 0x18); break; // RST 3
        case 0xE7: i8080_call(cpu, 0x20); break; // RST 4
        case 0xEF: i8080_call(cpu, 0x28); break; // RST 5
        case 0xF7: i8080_call(cpu, 0x30); break; // RST 6
        case 0xFF: i8080_call(cpu, 0x38); break; // RST 7

        // CONTROL INSTRUCTIONS
        case 0x00: break;                   //NOP
        case 0x76: cpu->halted = 1; break; // HLT

        case 0xDB: cpu->a = cpu->port_in(cpu, i8080_next_byte(cpu)); break; // IN
        case 0xD3: cpu->port_out(cpu, i8080_next_byte(cpu), cpu->a); break; // OUT

        case 0xFB: cpu->iff = 1; cpu->interrupt_delay = 1; break;   //EI
        case 0xF3: cpu->iff = 0; break;                             //DI

        case 0x08:
        case 0x10:
        case 0x18:
        case 0x20:
        case 0x28:
        case 0x30:
        case 0x38: break; // undocumented NOPs

        case 0xD9: i8080_ret(cpu); break; // undocumented RET

        case 0xDD:
        case 0xED:
        case 0xFD: i8080_call(cpu, i8080_next_word(cpu)); break; // undocumented CALLs

        case 0xCB: i8080_jmp(cpu, i8080_next_word(cpu)); break; // undocumented JMP
    }
}

