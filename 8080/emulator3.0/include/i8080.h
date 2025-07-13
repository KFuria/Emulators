#ifndef __I8080_H__
#define __I8080_H__

#include <cstddef>
#include <cstdint>
#include <array>
#include <iostream>
#include <fstream>
#include <string>

#include "logger.h"
#include "i8080_hal.h"

#define FLAG_CARRY      0x01 // C
#define FLAG_PARITY     0X04 // P
#define FLAG_AUX_CARRY  0x10 // AC
#define FLAG_ZERO       0x40 // Z
#define FLAG_SIGN       0x80 // S  

#define TEST_BUILD 1

class T8080{
public: 
    T8080();
    ~T8080();
    int disassembleOp(int pc);
    void setHal(T8080Hal * Hal);
    void reset();
    void step();
    void execute(uint8_t op);

    // Public getters and setters for PC and SP
    void setPC(uint16_t addr);
    void setSP(uint16_t addr);
    uint16_t getPC() const { return PC; }
    uint16_t getSP() const { return SP; }

    // Basic 8-bit register getters
    uint8_t getA() const { return A; }
    uint8_t getFlags() const { return F; }
    uint8_t getB() const { return B; }
    uint8_t getC() const { return C; }
    uint8_t getD() const { return D; }
    uint8_t getE() const { return E; }
    uint8_t getH() const { return H; }
    uint8_t getL() const { return L; }
    
    // 16-bit register pair getters
    uint16_t getBC() const { return get_bc(); }
    uint16_t getDE() const { return get_de(); }
    uint16_t getHL() const { return get_hl(); }
    uint16_t getPSW() const { return get_psw(); }

    bool is_halted() const{ return halted;} 

    // cycle count
    unsigned long getCyc() const { return cyc; }


#ifdef TEST_BUILD // Include only when testing and debugging
    // Setters for individual 8-bit registers (Only for test setup)
    void setA(uint8_t val) { A = val; }
    void setFlags(uint8_t val) { F = val; }
    void setB(uint8_t val) { B = val; }
    void setC(uint8_t val) { C = val; }
    void setD(uint8_t val) { D = val; }
    void setE(uint8_t val) { E = val; }
    void setH(uint8_t val) { H = val; }
    void setL(uint8_t val) { L = val; }
    
    // Setters for 16-bit register pairs and status word (Only for test setup)
    void setBC(uint16_t val) { set_bc(val); }
    void setDE(uint16_t val) { set_de(val); }
    void setHL(uint16_t val) { set_hl(val); }
    void setPSW(uint16_t val) { set_psw(val); }
#endif // TEST_BUILD


private:
    std::shared_ptr<TLogger> logger;

    // Registers
    uint16_t SP;
    uint16_t PC;
    uint8_t A, B, C, D, E, H, L;
    uint8_t F; // (S, Z, 0, AC, 0, P, 1, C)

    // Interrupts
    bool INTE : 1;
    bool interrupt_pending : 1;
    uint8_t interrupt_vector;
    uint8_t interrupt_delay;
    void set_interrupt(uint8_t opcode);

    bool halted : 1;
    unsigned long cyc;

    T8080Hal * hal;

    // Helper Methods (Memory/IO Access)
    void write_word(uint16_t addr, uint16_t val);
    void write_byte(uint16_t addr, uint8_t val);
    uint16_t read_word();
    uint8_t read_byte();
    uint16_t peek_word(uint16_t addr);
    uint8_t peek_byte(uint16_t addr);

    // Getters for 16-bit register pairs
    uint16_t get_bc() const;
    uint16_t get_de() const;
    uint16_t get_hl() const;
    uint16_t get_psw() const; // Processor Status Word (A and F combined)

    // Setters for 16-bit register pairs
    void set_bc(uint16_t val);
    void set_de(uint16_t val);
    void set_hl(uint16_t val);
    void set_psw(uint16_t val); // Sets A and F registers

    // Helper for flag manipulation
    void set_flag(uint8_t flag_mask, bool state);
    bool get_flag(uint8_t flag_mask) const;
    void set_szp(uint8_t val);

    // Push and Pop helper methods
    void push_word(uint16_t val);
    uint16_t pop_word();

    // Opcode Instructions
    uint8_t nop(uint8_t);
    uint8_t lxi(uint8_t);
    uint8_t stax(uint8_t);
    uint8_t inx(uint8_t);
    uint8_t inr(uint8_t);
    uint8_t dcr(uint8_t);
    uint8_t mvi(uint8_t);
    uint8_t dad(uint8_t);
    uint8_t ldax(uint8_t);
    uint8_t dcx(uint8_t);
    uint8_t rlc(uint8_t);
    uint8_t rrc(uint8_t);
    uint8_t ral(uint8_t);
    uint8_t rar(uint8_t);
    uint8_t shld(uint8_t);
    uint8_t daa(uint8_t);
    uint8_t lhld(uint8_t);
    uint8_t cma(uint8_t);
    uint8_t sta(uint8_t);
    uint8_t stc(uint8_t);
    uint8_t lda(uint8_t);
    uint8_t cmc(uint8_t);
    uint8_t mov(uint8_t);
    uint8_t hlt(uint8_t);
    uint8_t add(uint8_t);
    uint8_t adc(uint8_t);
    uint8_t sub(uint8_t);
    uint8_t sbb(uint8_t);
    uint8_t ana(uint8_t);
    uint8_t xra(uint8_t);
    uint8_t ora(uint8_t);
    uint8_t cmp(uint8_t);
    uint8_t rcc(uint8_t);
    uint8_t pop(uint8_t);
    uint8_t jcc(uint8_t);
    uint8_t jmp(uint8_t);
    uint8_t ccc(uint8_t);
    uint8_t push(uint8_t);
    uint8_t adi(uint8_t);
    uint8_t aci(uint8_t);
    uint8_t sui(uint8_t);
    uint8_t sbi(uint8_t);
    uint8_t ani(uint8_t);
    uint8_t xri(uint8_t);
    uint8_t ori(uint8_t);
    uint8_t cpi(uint8_t);
    uint8_t rst(uint8_t);
    uint8_t ret(uint8_t);
    uint8_t call(uint8_t);
    uint8_t out(uint8_t);
    uint8_t in(uint8_t);
    uint8_t xthl(uint8_t);
    uint8_t pchl(uint8_t);
    uint8_t xchg(uint8_t);
    uint8_t di(uint8_t);
    uint8_t sphl(uint8_t);
    uint8_t ei(uint8_t);

    // function pointer array
    using InstructionFunc = uint8_t (T8080::*)(uint8_t op);
    static constexpr InstructionFunc instruction_set[256] = {
    //      0           1           2           3               4           5               6           7           8               9           A           B               C           D           E               F    
    &T8080::nop, &T8080::lxi, &T8080::stax, &T8080::inx,  &T8080::inr, &T8080::dcr,  &T8080::mvi, &T8080::rlc, &T8080::nop, &T8080::dad, &T8080::ldax, &T8080::dcx,  &T8080::inr, &T8080::dcr, &T8080::mvi, &T8080::rrc,
    &T8080::nop, &T8080::lxi, &T8080::stax, &T8080::inx,  &T8080::inr, &T8080::dcr,  &T8080::mvi, &T8080::ral, &T8080::nop, &T8080::dad, &T8080::ldax, &T8080::dcx,  &T8080::inr, &T8080::dcr, &T8080::mvi, &T8080::rar,
    &T8080::nop, &T8080::lxi, &T8080::shld, &T8080::inx,  &T8080::inr, &T8080::dcr,  &T8080::mvi, &T8080::daa, &T8080::nop, &T8080::dad, &T8080::lhld, &T8080::dcx,  &T8080::inr, &T8080::dcr, &T8080::mvi, &T8080::cma,
    &T8080::nop, &T8080::lxi, &T8080::sta , &T8080::inx,  &T8080::inr, &T8080::dcr,  &T8080::mvi, &T8080::stc, &T8080::nop, &T8080::dad, &T8080::lda , &T8080::dcx,  &T8080::inr, &T8080::dcr, &T8080::mvi, &T8080::cmc,
   
    &T8080::mov, &T8080::mov, &T8080::mov,  &T8080::mov,  &T8080::mov, &T8080::mov,  &T8080::mov, &T8080::mov, &T8080::mov, &T8080::mov, &T8080::mov,  &T8080::mov,  &T8080::mov, &T8080::mov, &T8080::mov, &T8080::mov,
    &T8080::mov, &T8080::mov, &T8080::mov,  &T8080::mov,  &T8080::mov, &T8080::mov,  &T8080::mov, &T8080::mov, &T8080::mov, &T8080::mov, &T8080::mov,  &T8080::mov,  &T8080::mov, &T8080::mov, &T8080::mov, &T8080::mov,
    &T8080::mov, &T8080::mov, &T8080::mov,  &T8080::mov,  &T8080::mov, &T8080::mov,  &T8080::mov, &T8080::mov, &T8080::mov, &T8080::mov, &T8080::mov,  &T8080::mov,  &T8080::mov, &T8080::mov, &T8080::mov, &T8080::mov,
    &T8080::mov, &T8080::mov, &T8080::mov,  &T8080::mov,  &T8080::mov, &T8080::mov,  &T8080::hlt, &T8080::mov, &T8080::mov, &T8080::mov, &T8080::mov,  &T8080::mov,  &T8080::mov, &T8080::mov, &T8080::mov, &T8080::mov,
    
    &T8080::add, &T8080::add, &T8080::add,  &T8080::add,  &T8080::add, &T8080::add,  &T8080::add, &T8080::add, &T8080::adc, &T8080::adc, &T8080::adc,  &T8080::adc,  &T8080::adc, &T8080::adc, &T8080::adc, &T8080::adc,
    &T8080::sub, &T8080::sub, &T8080::sub,  &T8080::sub,  &T8080::sub, &T8080::sub,  &T8080::sub, &T8080::sub, &T8080::sbb, &T8080::sbb, &T8080::sbb,  &T8080::sbb,  &T8080::sbb, &T8080::sbb, &T8080::sbb, &T8080::sbb,
    &T8080::ana, &T8080::ana, &T8080::ana,  &T8080::ana,  &T8080::ana, &T8080::ana,  &T8080::ana, &T8080::ana, &T8080::xra, &T8080::xra, &T8080::xra,  &T8080::xra,  &T8080::xra, &T8080::xra, &T8080::xra, &T8080::xra,
    &T8080::ora, &T8080::ora, &T8080::ora,  &T8080::ora,  &T8080::ora, &T8080::ora,  &T8080::ora, &T8080::ora, &T8080::cmp, &T8080::cmp, &T8080::cmp,  &T8080::cmp,  &T8080::cmp, &T8080::cmp, &T8080::cmp, &T8080::cmp,

    &T8080::rcc, &T8080::pop, &T8080::jcc,  &T8080::jmp,  &T8080::ccc, &T8080::push, &T8080::adi, &T8080::rst, &T8080::rcc, &T8080::ret,  &T8080::jcc, &T8080::jmp,  &T8080::ccc, &T8080::call, &T8080::aci, &T8080::rst,
    &T8080::rcc, &T8080::pop, &T8080::jcc,  &T8080::out,  &T8080::ccc, &T8080::push, &T8080::sui, &T8080::rst, &T8080::rcc, &T8080::ret,  &T8080::jcc, &T8080::in,   &T8080::ccc, &T8080::call, &T8080::sbi, &T8080::rst,
    &T8080::rcc, &T8080::pop, &T8080::jcc,  &T8080::xthl, &T8080::ccc, &T8080::push, &T8080::ani, &T8080::rst, &T8080::rcc, &T8080::pchl, &T8080::jcc, &T8080::xchg, &T8080::ccc, &T8080::call, &T8080::xri, &T8080::rst,
    &T8080::rcc, &T8080::pop, &T8080::jcc,  &T8080::di,   &T8080::ccc, &T8080::push, &T8080::ori, &T8080::rst, &T8080::rcc, &T8080::sphl, &T8080::jcc, &T8080::ei,   &T8080::ccc, &T8080::call, &T8080::cpi, &T8080::rst, 

    };

};



#endif