#ifndef __I8080_HELPER_H__
#define __I8080_HELPER_H__

#include "i8080.h"

//-----------------------------------------------------------------------------
// Inline Implementations of Helper Methods
// Placing these in the header for performance with small, frequently
// called functions.
//-----------------------------------------------------------------------------


// Writes a word to specified address in memory
inline void T8080::write_word(uint16_t addr, uint16_t val){
	hal->write_byte(addr, val & 0xFF);
	hal->write_byte(addr + 1, val >> 8);
}

// Writes a byte to specified address in memory
inline void T8080::write_byte(uint16_t addr, uint8_t val){
    hal->write_byte(addr, val);
}

// Peeks the word at specified address in memory 
inline uint8_t T8080::peek_byte(uint16_t addr){
	return hal->read_byte(addr);
}

// Peeks the word at specified address in memory 
inline uint16_t T8080::peek_word(uint16_t addr){
	return (static_cast<uint16_t>(hal->read_byte(addr+1)) << 8) | hal->read_byte(addr);
}

// Advance PC by 1 after reading byte from memory
inline uint8_t T8080::read_byte(){
	return hal->read_byte(PC++);
}

// Advance PC by 2 after reading word from memory
inline uint16_t T8080::read_word(){
	uint16_t result = peek_word(PC);
	PC += 2;
	return result;
}

// Private getter for BC register
inline uint16_t T8080::get_bc() const {
    return (static_cast<uint16_t>(B) << 8) | C;
}

// Private setter for BC register
inline void T8080::set_bc(uint16_t val) {
    B = (val >> 8) & 0xFF;
    C = val & 0xFF;
}

// Private getter for DE register
inline uint16_t T8080::get_de() const {
    return (static_cast<uint16_t>(D) << 8) | E;
}

// Private setter for DE register
inline void T8080::set_de(uint16_t val) {
    D = (val >> 8) & 0xFF;
    E = val & 0xFF;
}

// Private getter for HL register
inline uint16_t T8080::get_hl() const {
    return (static_cast<uint16_t>(H) << 8) | L;
}

// Private setter for HL register
inline void T8080::set_hl(uint16_t val) {
    H = (val >> 8) & 0xFF;
    L = val & 0xFF;
}

// Private getter for PSW register
inline uint16_t T8080::get_psw() const {
    return (static_cast<uint16_t>(A) << 8) | F;
}

// Private setter for PSW register
inline void T8080::set_psw(uint16_t val) {
    A = (val >> 8) & 0xFF;
    F = (val & 0xD7) | 0x02; // (S, Z, 0, AC, 0, P, 1, C)
}

// Private setter for flag resgister
inline void T8080::set_flag(uint8_t flag_mask, bool state) {
    if (state) {
        F |= flag_mask;
    } else {
        F &= ~flag_mask;
    }
}

// Private getter for flag register
inline bool T8080::get_flag(uint8_t flag_mask) const {
    return (F & flag_mask) != 0;
}

// Public setter for PC
inline void T8080::setPC(uint16_t addr){
    PC = addr;
}

// Public setter for SP
inline void T8080::setSP(uint16_t addr){
    SP = addr;
}

// Sets zero, sign and parity flags based on val
inline void T8080::set_szp(uint8_t const val){
    // Sign Flag (S): Set if bit 7 of the result is 1
    set_flag(FLAG_SIGN, (val & FLAG_SIGN) != 0);
    
    // Zero Flag (Z): Set if the result is 0
    set_flag(FLAG_ZERO, val == 0);

    // Parity Flag (P): Set if the number of set bits in the result is even
    uint8_t set_bits = 0;
    for (int i = 0; i < 8; ++i) {
        set_bits += ((val >> i) & 0x01);
    }
    set_flag(FLAG_PARITY, (set_bits & 0x1) == 0); 
}

// Pop 16-bit word from the stack
inline uint16_t T8080::pop_word(){
    uint16_t res = peek_word(SP);
    SP += 2;
    return res;
}

// Push 16-bit word to the stack
inline void T8080::push_word(uint16_t val){
    SP -= 2;
    write_word(SP, val);
}

#endif