#include "i8080.h"
#include "i8080_helpers.h"


//------------------------------------------------------------
//	Desc: No operation occurs, execution proceeds with next
//  sequential instruction.
//	Condition bits affected: None
//------------------------------------------------------------
uint8_t T8080::nop(uint8_t op){
	(void) op;
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

//------------------------------------------------------------
//	Desc: The specified register or memory byte is
//	decremented by 1. 
//	Condition bits affected: Zero, Sign, Parity, Auxiliary
//	Carry
//------------------------------------------------------------
uint8_t T8080::dcr(uint8_t op){
	uint8_t cycles;
	switch((op >> 3) & 0x7){
		case 0b000: 
			B -= 1;
			set_flag(FLAG_AUX_CARRY, (B & 0xF) == 0xF);
			set_szp(B);
			cycles = 5;
			break;
		case 0b001: 
			C -= 1; 
			set_flag(FLAG_AUX_CARRY, (C & 0xF) == 0xF);
			set_szp(C);
			cycles = 5;
			break;
		case 0b010: 
			D -= 1; 
			set_flag(FLAG_AUX_CARRY, (D & 0xF) == 0xF);
			set_szp(D);
			cycles = 5;
			break;
		case 0b011: 
			E -= 1; 
			set_flag(FLAG_AUX_CARRY, (E & 0xF) == 0xF);
			set_szp(E);
			cycles = 5;
			break;
		case 0b100: 
			H -= 1; 
			set_flag(FLAG_AUX_CARRY, (H & 0xF) == 0xF);
			set_szp(H);
			cycles = 5;
			break;
		case 0b101: 
			L -= 1; 
			set_flag(FLAG_AUX_CARRY, (L & 0xF) == 0xF);
			set_szp(L);
			cycles = 5;
			break;
		case 0b111: 
			A -= 1; 
			set_flag(FLAG_AUX_CARRY, (A & 0xF) == 0xF);
			set_szp(A);
			cycles = 5;
			break;
		case 0b110:
			uint8_t res = peek_byte(get_hl()) - 1;
			write_byte(get_hl(), res);
			set_flag(FLAG_AUX_CARRY, (res & 0xF) == 0xF);
			set_szp(res);
			cycles = 10;
			break;
	}
	return cycles;
}

//------------------------------------------------------------
//	Desc: The byte of immediate data is stored in
//	the specified register or memory byte. 
//	Condition bits affected: None
//------------------------------------------------------------
uint8_t T8080::mvi(uint8_t op){
	uint8_t cycles; 
	switch((op >> 3) & 0x7){
		case 0b000: 
			B = read_byte();
			cycles = 7;
			break;
		case 0b001: 
			C = read_byte(); 
			cycles = 7;
			break;
		case 0b010: 
			D = read_byte(); 
			cycles = 7;
			break;
		case 0b011: 
			E = read_byte(); 
			cycles = 7;
			break;
		case 0b100: 
			H = read_byte(); 
			cycles = 7;
			break;
		case 0b101: 
			L = read_byte(); 
			cycles = 7;
			break;
		case 0b111: 
			A = read_byte(); 
			cycles = 7;
			break;
		case 0b110:
			write_byte(get_hl(), read_byte());
			cycles = 10;
			break;
	}
	return cycles;
}

//------------------------------------------------------------
//	Desc: The 16-bit number in the specified register pair is 
//	added to the 16-bit number held in the H and L registers 
//	using two's complement arithmetic. The result replaces the
//	contents of the H and L registers. 
//	Condition bits affected: Carry
//------------------------------------------------------------
uint8_t T8080::dad(uint8_t op){
	uint8_t cycles;
	uint32_t res; 
	switch((op >> 4) & 0x3){
		case 0b00:
			res = get_hl() + get_bc();
			set_hl(res);
			set_flag(FLAG_CARRY, res >> 16);
			cycles = 10;
			break;
		case 0b01: 
			res = get_hl() + get_de();
			set_hl(res);
			set_flag(FLAG_CARRY, res >> 16);
			cycles = 10;
			break;
		case 0b10: 
			res = get_hl() << 1;
			set_hl(res);
			set_flag(FLAG_CARRY, res >> 16);
			cycles = 10;
			break;
		case 0b11: 
			res = get_hl() + getSP();
			set_hl(res);
			set_flag(FLAG_CARRY, res >> 16);
			cycles = 10;
			break;
	}
	return cycles;
}

//------------------------------------------------------------
//	Desc: The contents of the memory location addressed by 
//	registers B and C, or by registers D and E, replace
//	the contents of the accumulator. 
//	Condition bits affected: None
//------------------------------------------------------------
uint8_t T8080::ldax(uint8_t op){
	switch((op >> 4) & 0x1){
		case 0x0:
			A = peek_byte(get_bc());
			break;
		case 0x1:
			A = peek_byte(get_de());
			break;
	}
	return 7;
}

//------------------------------------------------------------
//	Desc: The 16-bit number held in the specified register 
//	pair is decremented by one. 
//	Condition bits affected: None
//------------------------------------------------------------
uint8_t T8080::dcx(uint8_t op){
	switch((op >> 4) & 0x3){
		case 0x00:
			set_bc(get_bc()-1);
			break;
		case 0x01:
			set_de(get_de()-1);
			break;
		case 0x02:
			set_hl(get_hl()-1);
			break;
		case 0x03:
			SP -= 1;
			break;
	}
	return 5;
}

//------------------------------------------------------------
//	Desc: The Carry bit is set equal to the high-order bit of 
//	the accumulator. The contents of the accumulator are 
//	rotated one bit position to the left, with the high-order
//	bit being transferred to the low-order bit position of
//	the accumulator. 
//	Condition bits affected: Carry
//------------------------------------------------------------
uint8_t T8080::rlc(uint8_t op){
	A = (A << 1) | (A >> 7);
	set_flag(FLAG_CARRY, A & 0x1);
	return 4;
}

//------------------------------------------------------------
//	Desc: The carry bit is set equal to the low-order bit of 
//	the accumulator. The contents of the accumulator are
//	rotated one bit position to the right, with the low-order 
//	bit	being transferred to the high-order bit position of 
//	the	accumulator. 
//	Condition bits affected: Carry
//------------------------------------------------------------
uint8_t T8080::rrc(uint8_t op){
	A = (A >> 1) | (A << 7);
	set_flag(FLAG_CARRY, A & 0x80);
	return 4;
}

//------------------------------------------------------------
//	Desc: The contents of the accumulator are rotated one bit
//	position to the left. The high-order bit of the 
//	accumulator replaces the Carry bit, while the Carry bit 
//	replaces the low-order bit of the accumulator. 
//	Condition bits affected: Carry
//------------------------------------------------------------
uint8_t T8080::ral(uint8_t op){
	bool cf = get_flag(FLAG_CARRY);
	set_flag(FLAG_CARRY, A & 0x80);
	A = (A << 1) | cf;
	return 4;
}

//------------------------------------------------------------
//	Desc: The contents of the accumulator are rotated one bit
//	position to the right. The low-order bit of the 
//	accumulator replaces the Carry bit, while the Carry bit 
//	replaces the high-order bit of the accumulator. 
//	Condition bits affected: Carry
//------------------------------------------------------------
uint8_t T8080::rar(uint8_t op){
	bool cf = get_flag(FLAG_CARRY);
	set_flag(FLAG_CARRY, A & 0x01);
	A = (A >> 1) | (cf << 7);
	return 4;
}

//------------------------------------------------------------
//	Desc: The contents of the L register are stored at the 
//	memory address formed by concatenating HI ADDR with 
//	LOW ADDR. The contents of the H register are stored at
//	the next higher memory address.
//	Condition bits affected: None
//------------------------------------------------------------
uint8_t T8080::shld(uint8_t op){
	write_word(read_word(), get_hl());
	return 16;
}

//------------------------------------------------------------
//	Desc: The eight-bit hexadecimal number in the accumulator
//	is adjusted to form two four-bit binary coded decimal
//	digits.
//	Condition bits affected: Zero, Sign, Parity, Carry,
//	Auxiliary Carry
//------------------------------------------------------------
uint8_t T8080::daa(uint8_t op){
	if(((A & 0x0F) > 9) || get_flag(FLAG_AUX_CARRY)){
		A += 0x06;
		set_flag(FLAG_AUX_CARRY, 1);
	}
	if(((A >> 4) > 9) || get_flag(FLAG_CARRY)){
		A += 0x60;
		set_flag(FLAG_CARRY, 1);
	}
	set_szp(A);
	return 4;
}

//------------------------------------------------------------
//	Desc: The byte at the memory address formed by 
//	concatenating HI ADD with LOW ADD replaces the contents
//	of the L register. The byte at the next higher memory
//	address replaces the contents of the H register.
//	Condition bits affected: None
//------------------------------------------------------------
uint8_t T8080::lhld(uint8_t op){
	set_hl(peek_word(read_word()));
	return 16;
}

//------------------------------------------------------------
//	Desc: Each bit of the contents of the accumulator
//	is complemented (producing the one's complement).
//	Condition bits affected: None
//------------------------------------------------------------
uint8_t T8080::cma(uint8_t op){
	A = ~A;
	return 4;
}

//------------------------------------------------------------
//	Desc: The contents of the accumulator replace the byte at 
//	the memory address formed by HI ADD and LOW ADD.
//	Condition bits affected: None
//------------------------------------------------------------
uint8_t T8080::sta(uint8_t op){
	write_byte(read_word(), A);
	return 13;
}

//------------------------------------------------------------
//	Desc: The Carry bit is set to one.
//	Condition bits affected: Carry
//------------------------------------------------------------
uint8_t T8080::stc(uint8_t op){
	set_flag(FLAG_CARRY, 1);
	return 4;
}

//------------------------------------------------------------
//	Desc: The byte at the memory address formed by HI ADD and 
//	LOW ADD replaces the contents of the accumulator.
//	Condition bits affected: None
//------------------------------------------------------------
uint8_t T8080::lda(uint8_t op){
	A = peek_byte(read_word());
	return 13;
}

//------------------------------------------------------------
//	Desc: If the Carry bit = 0, it is set to 1. 
//	If the Carry bit = 1, it is reset to O.
//	Condition bits affected: Carry
//------------------------------------------------------------
uint8_t T8080::cmc(uint8_t op){
	set_flag(FLAG_CARRY, !get_flag(FLAG_CARRY));
	return 4;
}

//------------------------------------------------------------
//	Desc: One byte of data is moved from the register 
//	specified by src (the source register) to the register
//	specified by dst (the destination register). The data 
//	replaces the contents of the destination register; 
//	the source remains unchanged.
//	Condition bits affected: None
//------------------------------------------------------------
uint8_t T8080::mov(uint8_t op){
	uint8_t dst = (op >> 3) & 0x7; 	//  Destination register
	uint8_t src = op & 0x7;         //  Source register
	uint8_t cycles = 5;

	if(dst == 0b000){ // B
		switch(src){
			case 0b000: break; 		  // MOV B, B
			case 0b001: B = C; break; // MOV B, C
			case 0b010: B = D; break; // MOV B, D
			case 0b011: B = E; break; // MOV B, E
			case 0b100: B = H; break; // MOV B, H
			case 0b101: B = L; break; // MOV B, L
			case 0b111: B = A; break; // MOV B, A
			case 0b110: B = peek_byte(get_hl()); cycles = 7; break; // MOV B, M
		}
	} else if(dst == 0b001){ // C
		switch(src){
			case 0b000: C = B; break; // MOV C, B
			case 0b001: break; 		  // MOV C, C
			case 0b010: C = D; break; // MOV C, D
			case 0b011: C = E; break; // MOV C, E
			case 0b100: C = H; break; // MOV C, H
			case 0b101: C = L; break; // MOV C, L
			case 0b111: C = A; break; // MOV C, A
			case 0b110: C = peek_byte(get_hl()); cycles = 7; break; // MOV C, M
		}
	} else if(dst == 0b010){ // D
		switch(src){
			case 0b000: D = B; break; // MOV D, B
			case 0b001: D = C; break; // MOV D, C
			case 0b010: break; 		  // MOV D, D
			case 0b011: D = E; break; // MOV D, E
			case 0b100: D = H; break; // MOV D, H
			case 0b101: D = L; break; // MOV D, L
			case 0b111: D = A; break; // MOV D, A
			case 0b110: D = peek_byte(get_hl()); cycles = 7; break;// MOV D, M
		}
	} else if(dst == 0b011){ // E
		switch(src){
			case 0b000: E = B; break; // MOV E, B
			case 0b001: E = C; break; // MOV E, C
			case 0b010: E = D; break; // MOV E, D
			case 0b011: break; 		  // MOV E, E
			case 0b100: E = H; break; // MOV E, H
			case 0b101: E = L; break; // MOV E, L
			case 0b111: E = A; break; // MOV E, A
			case 0b110: E = peek_byte(get_hl()); cycles = 7; break; // MOV E, M
		}
	} else if(dst == 0b100){ // H
		switch(src){
			case 0b000: H = B; break; // MOV H, B
			case 0b001: H = C; break; // MOV H, C
			case 0b010: H = D; break; // MOV H, D
			case 0b011: H = E; break; // MOV H, E
			case 0b100: break; 	 	  // MOV H, H
			case 0b101: H = L; break; // MOV H, L
			case 0b111: H = A; break; // MOV H, A
			case 0b110: H = peek_byte(get_hl()); cycles = 7; break; // MOV H, M
		}
	} else if(dst == 0b101){ // L
		switch(src){
			case 0b000: L = B; break; // MOV L, B
			case 0b001: L = C; break; // MOV L, C
			case 0b010: L = D; break; // MOV L, D
			case 0b011: L = E; break; // MOV L, E
			case 0b100: L = H; break; // MOV L, H
			case 0b101: break; 		  // MOV L, L
			case 0b111: L = A; break; // MOV L, A
			case 0b110: L = peek_byte(get_hl()); cycles = 7; break; // MOV L, M
		}
	} else if(dst == 0b111){ // A
		switch(src){
			case 0b000: A = B; break; // MOV A, B
			case 0b001: A = C; break; // MOV A, C
			case 0b010: A = D; break; // MOV A, D
			case 0b011: A = E; break; // MOV A, E
			case 0b100: A = H; break; // MOV A, H
			case 0b101: A = L; break; // MOV A, L
			case 0b111: break; 		  // MOV A, A
			case 0b110: A = peek_byte(get_hl()); cycles = 7; break; // MOV A, M
		}
	} else if(dst == 0b110){ // M
		cycles = 7;
		switch(src){
			case 0b000: write_byte(get_hl(), B); break; // MOV M, B
			case 0b001: write_byte(get_hl(), C); break; // MOV M, C
			case 0b010: write_byte(get_hl(), D); break; // MOV M, D
			case 0b011: write_byte(get_hl(), E); break; // MOV M, E
			case 0b100: write_byte(get_hl(), H); break; // MOV M, H
			case 0b101: write_byte(get_hl(), L); break; // MOV M, L
			case 0b111: write_byte(get_hl(), A); break; // MOV M, A
			case 0b110: break; // MOV M, M
		}
	}

	return cycles; // cycle count
}

//------------------------------------------------------------
//	Desc: The program counter is incremented to the address of
//	the next sequential instruction. The CPU then enters the 
//	STOPPED state and no further activity takes place until an
//	interrupt occurs.
//	Condition bits affected: None
//------------------------------------------------------------
uint8_t T8080::hlt(uint8_t op){
	halted = true;
	return 7;
}

//------------------------------------------------------------
//	Desc: The specified byte is added to the contents of the 
//	accumulator using two's complement arithmetic.
//	Condition bits affected: Carry, Sign, Zero, Parity,
//	Auxiliary Carry
//------------------------------------------------------------
uint8_t T8080::add(uint8_t op){
	uint8_t cycles;
	uint8_t value;
	switch(op & 0x7){
		case 0b000: value = B; cycles = 4; break;
		case 0b001: value = C; cycles = 4; break;
		case 0b010: value = D; cycles = 4; break;
		case 0b011: value = E; cycles = 4; break;
		case 0b100: value = H; cycles = 4; break;
		case 0b101: value = L; cycles = 4; break;
		case 0b110: value = peek_byte(get_hl()); cycles = 7; break;
		case 0b111: value = A; cycles = 4; break;
	}

	A += value;
	set_flag(FLAG_AUX_CARRY, (A & 0x0F) < (value & 0x0F));
	set_flag(FLAG_CARRY, A < value);
	set_szp(A);

	return cycles;
}

//------------------------------------------------------------
//	Desc: The specified byte is subtracted from the
//	accumulator using two's complement arithmetic.
//  If there is no carry out of the high-order bit position,
//	indicating that a borrow occurred, the Carry bit is set;
//	otherwise it is reset. (Note that this differs from an add
//	operation, which resets the carry if no overflow occurs).
//	Condition bits affected: Carry, Sign, Zero, Parity,
//	Auxiliary Carry
//------------------------------------------------------------
uint8_t T8080::sub(uint8_t op){
	uint8_t cycles;
	uint8_t value;
	switch(op & 0x7){
		case 0b000: value = B; cycles = 4; break;
		case 0b001: value = C; cycles = 4; break;
		case 0b010: value = D; cycles = 4; break;
		case 0b011: value = E; cycles = 4; break;
		case 0b100: value = H; cycles = 4; break;
		case 0b101: value = L; cycles = 4; break;
		case 0b110: value = peek_byte(get_hl()); cycles = 7; break;
		case 0b111: value = A; cycles = 4; break;
	}
	uint8_t old_A = A;
	A = old_A - value;
	set_flag(FLAG_AUX_CARRY, (old_A & 0x0F) < (value & 0x0F));
	set_flag(FLAG_CARRY, old_A < value);
	set_szp(A);

	return cycles;
}

//------------------------------------------------------------
//	Desc: The specified byte is logically ANDed bit by bit 
//	with the contents of the accumulator. The Carry bit is 
//	reset to zero.
//	Condition bits affected: Carry, Zero, Sign, Parity,
//	Auxiliary Carry
//------------------------------------------------------------
uint8_t T8080::ana(uint8_t op){
	uint8_t cycles;
	uint8_t value;
	switch(op & 0x7){
		case 0b000: value = B; cycles = 4; break;
		case 0b001: value = C; cycles = 4; break;
		case 0b010: value = D; cycles = 4; break;
		case 0b011: value = E; cycles = 4; break;
		case 0b100: value = H; cycles = 4; break;
		case 0b101: value = L; cycles = 4; break;
		case 0b110: value = peek_byte(get_hl()); cycles = 7; break;
		case 0b111: value = A; cycles = 4; break;
	}
	
	set_flag(FLAG_AUX_CARRY, (A & 0x08) && (value & 0x08)); // Bit 3
	
	A &= value;
	set_flag(FLAG_CARRY, 0);	// Carry always reset
	set_szp(A);
	return cycles;
}

//------------------------------------------------------------
//	Desc: The specified byte is EXCLUSIVE-ORed bit by bit with
// 	the contents of the accumulator. The Carry bit is reset to
//	zero.
//	Condition bits affected: Carry, Zero, Sign, Parity,
//	Auxiliary Carry
//------------------------------------------------------------
uint8_t T8080::xra(uint8_t op){
	uint8_t cycles;
	uint8_t value;
	switch(op & 0x7){
		case 0b000: value = B; cycles = 4; break;
		case 0b001: value = C; cycles = 4; break;
		case 0b010: value = D; cycles = 4; break;
		case 0b011: value = E; cycles = 4; break;
		case 0b100: value = H; cycles = 4; break;
		case 0b101: value = L; cycles = 4; break;
		case 0b110: value = peek_byte(get_hl()); cycles = 7; break;
		case 0b111: value = A; cycles = 4; break;
	}
	A ^= value;
	set_flag(FLAG_CARRY, 0);	// Carry always reset
	set_flag(FLAG_AUX_CARRY, 0);
	set_szp(A);
	return cycles;
}

//------------------------------------------------------------
//	Desc: The specified byte is logically ORed bit by bit with
//	the contents of the accumulator. The carry bit is reset to 
//	zero.
//	Condition bits affected: Carry, Zero, Sign, Parity,
//	Auxiliary Carry
//------------------------------------------------------------
uint8_t T8080::ora(uint8_t op){
	uint8_t cycles;
	uint8_t value;
	switch(op & 0x7){
		case 0b000: value = B; cycles = 4; break;
		case 0b001: value = C; cycles = 4; break;
		case 0b010: value = D; cycles = 4; break;
		case 0b011: value = E; cycles = 4; break;
		case 0b100: value = H; cycles = 4; break;
		case 0b101: value = L; cycles = 4; break;
		case 0b110: value = peek_byte(get_hl()); cycles = 7; break;
		case 0b111: value = A; cycles = 4; break;
	}
	A |= value;
	set_flag(FLAG_CARRY, 0);	// Carry always reset
	set_flag(FLAG_AUX_CARRY, 0);
	set_szp(A);
	return cycles;
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