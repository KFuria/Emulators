#ifndef __I8080_HELPER_H__
#define __I8080_HELPER_H__

#include "i8080.h"

static const uint8_t OPCODES_CYCLES[256] = {
//  0  1   2   3   4   5   6   7   8  9   A   B   C   D   E  F
    4, 10, 7,  5,  5,  5,  7,  4,  4, 10, 7,  5,  5,  5,  7, 4,  // 0
    4, 10, 7,  5,  5,  5,  7,  4,  4, 10, 7,  5,  5,  5,  7, 4,  // 1
    4, 10, 16, 5,  5,  5,  7,  4,  4, 10, 16, 5,  5,  5,  7, 4,  // 2
    4, 10, 13, 5,  10, 10, 10, 4,  4, 10, 13, 5,  5,  5,  7, 4,  // 3
    5, 5,  5,  5,  5,  5,  7,  5,  5, 5,  5,  5,  5,  5,  7, 5,  // 4
    5, 5,  5,  5,  5,  5,  7,  5,  5, 5,  5,  5,  5,  5,  7, 5,  // 5
    5, 5,  5,  5,  5,  5,  7,  5,  5, 5,  5,  5,  5,  5,  7, 5,  // 6
    7, 7,  7,  7,  7,  7,  7,  7,  5, 5,  5,  5,  5,  5,  7, 5,  // 7
    4, 4,  4,  4,  4,  4,  7,  4,  4, 4,  4,  4,  4,  4,  7, 4,  // 8
    4, 4,  4,  4,  4,  4,  7,  4,  4, 4,  4,  4,  4,  4,  7, 4,  // 9
    4, 4,  4,  4,  4,  4,  7,  4,  4, 4,  4,  4,  4,  4,  7, 4,  // A
    4, 4,  4,  4,  4,  4,  7,  4,  4, 4,  4,  4,  4,  4,  7, 4,  // B
    5, 10, 10, 10, 11, 11, 7,  11, 5, 10, 10, 10, 11, 17, 7, 11, // C
    5, 10, 10, 10, 11, 11, 7,  11, 5, 10, 10, 10, 11, 17, 7, 11, // D
    5, 10, 10, 18, 11, 11, 7,  11, 5, 5,  10, 4,  11, 17, 7, 11, // E
    5, 10, 10, 4,  11, 11, 7,  11, 5, 5,  10, 4,  11, 17, 7, 11  // F
};

// reads a byte from memory
static inline uint8_t i8080_read_byte(i8080 * const cpu, uint16_t addr) {
    return cpu->read_byte(addr);
}

// writes a byte to memory
static inline void i8080_write_byte(i8080 * const cpu, uint16_t addr, uint8_t val) {
  cpu->write_byte(addr, val);
}

// reads a word from memory
static inline uint16_t i8080_read_word(i8080 * const cpu, uint16_t addr) {
  return (cpu->read_byte(addr+1) << 8) | cpu->read_byte(addr);
}

// writes a word to memory
static inline void i8080_write_word(i8080 * const cpu, uint16_t addr, uint16_t val) {
  cpu->write_byte(addr, val & 0xFF);
  cpu->write_byte(addr+1, val >> 8);
}

// returns the next byte in memory
static inline uint8_t i8080_next_byte(i8080 * const cpu) {
  return i8080_read_byte(cpu, cpu->pc++);
}

// returns the next word in memory
static inline uint16_t i8080_next_word(i8080 * const cpu) {
  uint16_t result = i8080_read_word(cpu, cpu->pc);
  cpu->pc += 2;
  return result;
}

// return the parity of byte: 0 for odd, 1 for even
static inline bool parity(uint8_t val){
    uint8_t num1 = 0;
    for(int i=0; i<8; i++){
        num1 += ((val>>i) & 1);
    }
    return (num1 & 1) == 0;
}


//sets zero, sign and parity flags based on val
static inline void set_szp(i8080 * const cpu, uint8_t val){
    cpu->zf = val == 0;
    cpu->sf = val >> 7;
    cpu->pf = parity(val); 
}

//---------------------- GET AND SET REGISTER PAIRS-----------------//

//set bc
static inline void i8080_set_bc(i8080 * const cpu, uint16_t val) {
  cpu->b = val >> 8;        //high
  cpu->c = val & 0xFF;      //low
}

//set de
static inline void i8080_set_de(i8080 * const cpu, uint16_t val) {
  cpu->d = val >> 8;        //high
  cpu->e = val & 0xFF;      //low
}

//set hl
static inline void i8080_set_hl(i8080 * const cpu, uint16_t val) {
  cpu->h = val >> 8;        //high
  cpu->l = val & 0xFF;      //low
}

//get bc
static inline uint16_t i8080_get_bc(i8080 * const cpu) {
  return (cpu->b << 8) | cpu->c;
}

//get de
static inline uint16_t i8080_get_de(i8080 * const cpu) {
  return (cpu->d << 8) | cpu->e;
}

//get hl
static inline uint16_t i8080_get_hl(i8080 * const cpu) {
  return (cpu->h << 8) | cpu->l;
}

//switch values of registers DE and HL
static inline void i8080_xchg(i8080 * const cpu){
  uint16_t temp_de = i8080_get_de(cpu);
  i8080_set_de(cpu, i8080_get_hl(cpu));
  i8080_set_hl(cpu, temp_de);
}

//switch values of SP and HL
static inline void i8080_xthl(i8080 * const cpu){
  uint16_t temp = i8080_read_word(cpu, cpu->sp);
  i8080_write_word(cpu, cpu->sp, i8080_get_hl(cpu));
  i8080_set_hl(cpu, temp);
}


//-------------------------STACK FUNCTIONS--------------------------//

// pushes a word into the stack and updates the stack pointer
static inline void i8080_push_word_stack(i8080 * const cpu, uint16_t val) {
  cpu->sp -= 2;
  i8080_write_word(cpu, cpu->sp, val);
}

// pops a word from the stack and updates the stack pointer
static inline uint16_t i8080_pop_word_stack(i8080 * const cpu) {
  uint16_t val = i8080_read_word(cpu, cpu->sp);
  cpu->sp += 2;
  return val;
}

//push flags and register A onto stack
static inline void i8080_push_psw(i8080 * const cpu){
  // sp <- sp - 2; (sp)<-flags; (sp+1)<-A; 
  //flags:  sf zf 0 hf 0 pf 1 cf
  uint16_t psw = 0;
  psw |= cpu->a << 8;
  psw |= cpu->sf << 7;
  psw |= cpu->zf << 6;
  psw |= cpu->hf << 4;
  psw |= cpu->pf << 2;
  psw |= 1 << 1;
  psw |= cpu->cf;
  i8080_push_word_stack(cpu, psw);
}

//pop flags and register A from stack
static inline void i8080_pop_psw(i8080 * const cpu){
  uint16_t psw = i8080_pop_word_stack(cpu);
  cpu->a =  (psw >> 8) & 0xFF;
  cpu->sf = (psw >> 7) & 0x1;
  cpu->zf = (psw >> 6) & 0x1;
  cpu->hf = (psw >> 4) & 0x1;
  cpu->pf = (psw >> 2) & 0x1;
  cpu->cf =  psw & 0x1;
}


//-------------------------ARITHMETIC LOGICAL INSTRUCTIONS-------------------------//

static bool carry(uint8_t pos, uint8_t a, uint8_t b, bool cy){
    uint16_t res = a + b + cy;
    uint16_t carry = res ^ a ^ b;
    return carry & (1 << pos);
}


// add  value to register A
static inline void i8080_add(i8080* const cpu, uint8_t val, bool cy) {
    uint8_t result = cpu->a + val + cy;
    cpu->cf = carry(8, cpu->a, val, cy);
    cpu->hf = carry(4, cpu->a, val, cy);
    set_szp(cpu, result);
    cpu->a = result;
}

//substract value from register A
static inline void i8080_sub(i8080 * const cpu, uint8_t val, bool cy){
    //use 2's complement
    i8080_add(cpu, ~val, !cy);
    cpu->cf = !cpu->cf;
}

//logical AND value with register A
static inline void i8080_ana(i8080 * const cpu, uint8_t val){
  uint8_t res = cpu->a & val;
  cpu->cf = 0;
  cpu->hf = ((cpu->a | val) &  0x08) != 0; //refer 8080 manual for explanation
  set_szp(cpu, res);
  cpu->a = res;
}

//logical OR value with register A
static inline void i8080_ora(i8080 * const cpu, uint8_t val){
  cpu->cf = 0;
  cpu->hf = 0;
  cpu->a |= val;
  set_szp(cpu, cpu->a);
}

//logical XOR value with register A
static inline void i8080_xra(i8080* const cpu, uint8_t val) {
  cpu->cf = 0;
  cpu->hf = 0;
  cpu->a ^= val;
  set_szp(cpu, cpu->a);
}

//logical compare value with register A
static inline void i8080_cmp(i8080 * const cpu, uint8_t val){
  uint16_t res = cpu->a - val;
  cpu->cf = res >> 8;
  cpu->hf = ~(cpu->a ^ res ^ val) & 0x10;
  set_szp(cpu, res & 0xFF);
}

//increment value by 1
static inline uint8_t i8080_inr(i8080 * const cpu, uint8_t val){
  uint8_t res = val + 1;
  cpu->hf = (res & 0xF)==0;
  set_szp(cpu, res);
  return res;
}

//decrement value by 1
static inline uint8_t i8080_dcr(i8080 * const cpu, uint8_t val){
  uint8_t res = val - 1;
  cpu->hf = !((res & 0xF)==0xF);
  set_szp(cpu, res);
  return res;
}

//add value to register pair HL
static inline void i8080_dad(i8080 * const cpu, uint16_t val){
  cpu->cf = ((i8080_get_hl(cpu) + val) >> 16) & 1;
  i8080_set_hl(cpu, i8080_get_hl(cpu) + val);
} 

//rotate register A left
static inline void i8080_rlc(i8080 * const cpu){
  cpu->cf = cpu->a >> 7;
  cpu->a = (cpu->a << 1) | cpu->cf;
}

//rotate register A right
static inline void i8080_rrc(i8080 * const cpu){
  cpu->cf = cpu->a & 0x1;
  cpu->a = (cpu->cf << 7) | (cpu->a >> 1);
}

//rotate left through carry
static inline void i8080_ral(i8080 * const cpu){
  bool cf = cpu->cf;
  cpu->cf = cpu->a >> 7;
  cpu->a = (cpu->a << 1) | cf;
}

//rotate right through carry
static inline void i8080_rar(i8080 * const cpu){
  bool cf = cpu->cf;
  cpu->cf = cpu->a & 0x1;
  cpu->a = (cpu->a >> 1) | (cf << 7);
}

//decimal adjust accumulator
static inline void i8080_daa(i8080 * const cpu){
  bool cy = cpu->cf;
  uint8_t val = 0;
  uint8_t lsb = cpu->a & 0xF;
  uint8_t msb = cpu->a >> 4;

  if (cpu->hf || lsb > 9){
    val += 0x06; //add 6 to lsb
  }
  if (cpu->cf || msb > 9 || (msb >= 9 && lsb > 9)){
    val += 0x60; //add 6 to msb
    cy = 1;
  }
  i8080_add(cpu, val, 0);
  cpu->cf = cy;
}


//----------------------------------JUMP, CALL & RET INSTRUCTIONS-----------------------------//

// jump to given address
static inline void i8080_jmp(i8080 * const cpu, uint16_t addr){
  cpu->pc = addr; 
}

//jump to address given in memory if condition met
static inline void i8080_jmp_cond(i8080 * const cpu, bool condition){
  uint16_t addr = i8080_next_word(cpu);
  if(condition){
    cpu->pc = addr;
  }
}

// save pc on stack and jump to given address
static inline void i8080_call(i8080 * const cpu, uint16_t addr){
  i8080_push_word_stack(cpu, cpu->pc);
  i8080_jmp(cpu, addr);
}

//save pc on stack and jump to address given in memory if condition met
static inline void i8080_call_cond(i8080 * const cpu, bool condition){
  uint16_t addr = i8080_next_word(cpu);
  if(condition){
    i8080_call(cpu, addr);
    cpu->cyc += 6; //additional cycles used to jump if condition met
  }
}

//return from a subroutine
static inline void i8080_ret(i8080 * const cpu){
  cpu->pc = i8080_pop_word_stack(cpu);
}

//return from a subroutine if condition met
static inline void i8080_ret_cond(i8080 * const cpu, bool condition){
  if(condition){
    i8080_ret(cpu);
    cpu->cyc += 6; //additional cycles used to jump if condition met
  }
}

#endif