#include "i8080.h"
#include "i8080_helpers.h"


//------------------------------------------------------------
//	Desc: No operation occurs, execution proceeds with next
//  sequential instruction.
//	Condition bits affected: None
//------------------------------------------------------------
uint8_t T8080::nop(uint8_t op){
	return 4; // cycle
}

//------------------------------------------------------------
//	Desc: Loads 16-bit immediate value into a specified 
// 	register pair.
// 	Condition bits affected: None
//------------------------------------------------------------
uint8_t T8080::lxi(uint8_t op){
	switch((op >> 4) & 0x3){
		case 0x00: 
			set_bc(read_word()); 
			break;
		case 0x01: 
			set_de(read_word());  
			break;
		case 0x02: 
			set_hl(read_word()); 
			break;
		case 0x03: 
			SP = read_word();  
			break;
	}
	return 10;
}

//------------------------------------------------------------
//	Desc: The contents of the accumulator are stored in the 
// 	memory location addressed by registers B and C, or by 
//	registers D and E. 
//	Condition bits affected: None
//------------------------------------------------------------
uint8_t T8080::stax(uint8_t op){
	switch((op >> 4) & 0x1){
		case 0x0:
			write_byte(get_bc(), A);
			break;
		case 0x1:
			write_byte(get_de(), A);
			break;
	}
	return 7;
}


//------------------------------------------------------------
//	Desc: The 16 bit value held in the specified register pair
//	is incremented by 1. 
//	Condition bits affected: None
//------------------------------------------------------------
uint8_t T8080::inx(uint8_t op){
	switch((op >> 4) & 0x3){
		case 0x00:
			set_bc(get_bc()+1);
			break;
		case 0x01:
			set_de(get_de()+1);
			break;
		case 0x02:
			set_hl(get_hl()+1);
			break;
		case 0x03:
			SP += 1;
			break;
	}
	return 5;
}


//------------------------------------------------------------
//	Desc: The specified register or memory byte is
//	incremented by 1. 
//	Condition bits affected: Zero, Sign, Parity, Auxiliary
//	Carry
//------------------------------------------------------------
uint8_t T8080::inr(uint8_t op){
	uint8_t cycles;
	switch((op >> 3) & 0x7){
		case 0b000: 
			B += 1;
			set_flag(FLAG_AUX_CARRY, (B & 0xF) == 0);
			set_szp(B);
			cycles = 5;
			break;
		case 0b001: 
			C += 1; 
			set_flag(FLAG_AUX_CARRY, (C & 0xF) == 0);
			set_szp(C);
			cycles = 5;
			break;
		case 0b010: 
			D += 1; 
			set_flag(FLAG_AUX_CARRY, (D & 0xF) == 0);
			set_szp(D);
			cycles = 5;
			break;
		case 0b011: 
			E += 1; 
			set_flag(FLAG_AUX_CARRY, (E & 0xF) == 0);
			set_szp(E);
			cycles = 5;
			break;
		case 0b100: 
			H += 1; 
			set_flag(FLAG_AUX_CARRY, (H & 0xF) == 0);
			set_szp(H);
			cycles = 5;
			break;
		case 0b101: 
			L += 1; 
			set_flag(FLAG_AUX_CARRY, (L & 0xF) == 0);
			set_szp(L);
			cycles = 5;
			break;
		case 0b111: 
			A += 1; 
			set_flag(FLAG_AUX_CARRY, (A & 0xF) == 0);
			set_szp(A);
			cycles = 5;
			break;
		case 0b110:
			uint8_t res = peek_byte(get_hl()) + 1;
			write_byte(get_hl(), res);
			set_flag(FLAG_AUX_CARRY, (res & 0xF) == 0);
			set_szp(res);
			cycles = 10;
			break;
	}
	return cycles;
}

uint8_t T8080::dcr(uint8_t op){
	logger->log("0x05	DCR", ELogLevel::OP);
}

uint8_t T8080::mvi(uint8_t op){
	logger->log("0x06	MVI", ELogLevel::OP);
}

uint8_t T8080::dad(uint8_t op){
	logger->log("0x09	DAD", ELogLevel::OP);
}

uint8_t T8080::ldax(uint8_t op){
	logger->log("0x0A	LDAX", ELogLevel::OP);
}

uint8_t T8080::dcx(uint8_t op){
	logger->log("0x0B	DCX", ELogLevel::OP);
}

uint8_t T8080::rlc(uint8_t op){
	logger->log("0x07	RLC", ELogLevel::OP);
}

uint8_t T8080::rrc(uint8_t op){
	logger->log("0x0F	RRC", ELogLevel::OP);
}

uint8_t T8080::ral(uint8_t op){
	logger->log("0x01	RAL", ELogLevel::OP);
}

uint8_t T8080::rar(uint8_t op){
	logger->log("0x01	RAR", ELogLevel::OP);
}

uint8_t T8080::shld(uint8_t op){
	logger->log("0x01	SHLD", ELogLevel::OP);
}

uint8_t T8080::daa(uint8_t op){
	logger->log("0x01	DAA", ELogLevel::OP);
}

uint8_t T8080::lhld(uint8_t op){
	logger->log("0x01	LHLD", ELogLevel::OP);
}

uint8_t T8080::cma(uint8_t op){
	logger->log("0x01	CMA", ELogLevel::OP);
}

uint8_t T8080::sta(uint8_t op){
	logger->log("0x01	STA", ELogLevel::OP);
}

uint8_t T8080::stc(uint8_t op){
	logger->log("0x01	STC", ELogLevel::OP);
}

uint8_t T8080::lda(uint8_t op){
	logger->log("0x01	LDA", ELogLevel::OP);
}

uint8_t T8080::cmc(uint8_t op){
	logger->log("0x01	CMC", ELogLevel::OP);
}

uint8_t T8080::mov(uint8_t op){
	logger->log("0x01	MOV", ELogLevel::OP);
}

uint8_t T8080::hlt(uint8_t op){
	logger->log("0x01	HLT", ELogLevel::OP);
}

uint8_t T8080::add(uint8_t op){
	logger->log("0x01	ADD", ELogLevel::OP);
}

uint8_t T8080::sub(uint8_t op){
	logger->log("0x01	SUB", ELogLevel::OP);
}

uint8_t T8080::ana(uint8_t op){
	logger->log("0x01	ANA", ELogLevel::OP);
}

uint8_t T8080::xra(uint8_t op){
	logger->log("0x01	XRA", ELogLevel::OP);
}

uint8_t T8080::ora(uint8_t op){
	logger->log("0x01	ORA", ELogLevel::OP);
}

uint8_t T8080::cmp(uint8_t op){
	logger->log("0x01	CMP", ELogLevel::OP);
}

uint8_t T8080::rcc(uint8_t op){
	logger->log("0x01	RCC", ELogLevel::OP);
}

uint8_t T8080::pop(uint8_t op){
	logger->log("0x01	POP", ELogLevel::OP);
}

uint8_t T8080::jcc(uint8_t op){
	logger->log("0x01	JCC", ELogLevel::OP);
}

uint8_t T8080::jmp(uint8_t op){
	logger->log("0x01	JMP", ELogLevel::OP);
}

uint8_t T8080::ccc(uint8_t op){
	logger->log("0x01	CCC", ELogLevel::OP);
}

uint8_t T8080::push(uint8_t op){
	logger->log("0x01	PUSH", ELogLevel::OP);
}

uint8_t T8080::adi(uint8_t op){
	logger->log("0x01	ADI", ELogLevel::OP);
}

uint8_t T8080::aci(uint8_t op){
	logger->log("0x01	ACI", ELogLevel::OP);
}

uint8_t T8080::sui(uint8_t op){
	logger->log("0x01	SUI", ELogLevel::OP);
}

uint8_t T8080::sbi(uint8_t op){
	logger->log("0x01	SBI", ELogLevel::OP);
}

uint8_t T8080::ani(uint8_t op){
	logger->log("0x01	ANI", ELogLevel::OP);
}

uint8_t T8080::xri(uint8_t op){
	logger->log("0x01	XRI", ELogLevel::OP);
}

uint8_t T8080::ori(uint8_t op){
	logger->log("0x01	ORI", ELogLevel::OP);
}

uint8_t T8080::cpi(uint8_t op){
	logger->log("0x01	CPI", ELogLevel::OP);
}

uint8_t T8080::rst(uint8_t op){
	logger->log("0x01	RST", ELogLevel::OP);
}

uint8_t T8080::ret(uint8_t op){
	logger->log("0x01	RET", ELogLevel::OP);
}

uint8_t T8080::call(uint8_t op){
	logger->log("0x01	CALL", ELogLevel::OP);
}

uint8_t T8080::out(uint8_t op){
	logger->log("0x01	OUT", ELogLevel::OP);
}

uint8_t T8080::in(uint8_t op){
	logger->log("0x01	IN", ELogLevel::OP);
}

uint8_t T8080::xthl(uint8_t op){
	logger->log("0x01	XTHL", ELogLevel::OP);
}

uint8_t T8080::pchl(uint8_t op){
	logger->log("0x01	PCHL", ELogLevel::OP);
}

uint8_t T8080::xchg(uint8_t op){
	logger->log("0x01	XCHG", ELogLevel::OP);
}

uint8_t T8080::di(uint8_t op){
	logger->log("0x01	DI", ELogLevel::OP);
}

uint8_t T8080::sphl(uint8_t op){
	logger->log("0x01	SPHL", ELogLevel::OP);
}

uint8_t T8080::ei(uint8_t op){
	logger->log("0x01	EI", ELogLevel::OP);
}