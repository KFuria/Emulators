#include "i8080dis.h"

int Disassemble8080Op(unsigned char * buffer, int pc){
    unsigned char * code = &buffer[pc];
    int opbytes = 1;
    //printf("%04x ", pc);
    switch(*code){
        case 0x00: printf("%02x 			NOP", code[0]); break;
		case 0x01: printf("%02x %02x %02x 	LXI    B,#$%02x%02x", code[0], code[1], code[2], code[2], code[1]); opbytes=3; break;
		case 0x02: printf("%02x 			STAX   B", code[0]); break;
		case 0x03: printf("%02x 			INX    B", code[0]); break;
		case 0x04: printf("%02x 			INR    B", code[0]); break;
		case 0x05: printf("%02x 			DCR    B", code[0]); break;
		case 0x06: printf("%02x %02x 		MVI    B,#$%02x", code[0], code[1], code[1]); opbytes=2; break;
		case 0x07: printf("%02x 			RLC", code[0]); break;
		case 0x08: printf("%02x 			NOP", code[0]); break;
		case 0x09: printf("%02x 			DAD    B", code[0]); break;
		case 0x0a: printf("%02x 			LDAX   B", code[0]); break;
		case 0x0b: printf("%02x 			DCX    B", code[0]); break;
		case 0x0c: printf("%02x 			INR    C", code[0]); break;
		case 0x0d: printf("%02x 			DCR    C", code[0]); break;
		case 0x0e: printf("%02x %02x 		MVI    C,#$%02x", code[0], code[1], code[1]); opbytes = 2;	break;
		case 0x0f: printf("%02x 			RRC", code[0]); break;
			
		case 0x10: printf("%02x 			NOP", code[0]); break;
		case 0x11: printf("%02x %02x %02x 	LXI    D,#$%02x%02x", code[0], code[1], code[2], code[2], code[1]); opbytes=3; break;
		case 0x12: printf("%02x 			STAX   D", code[0]); break;
		case 0x13: printf("%02x 			INX    D", code[0]); break;
		case 0x14: printf("%02x 			INR    D", code[0]); break;
		case 0x15: printf("%02x 			DCR    D", code[0]); break;
		case 0x16: printf("%02x %02x 		MVI    D,#$%02x", code[0], code[1], code[1]); opbytes=2; break;
		case 0x17: printf("%02x 			RAL", code[0]); break;
		case 0x18: printf("%02x 			NOP", code[0]); break;
		case 0x19: printf("%02x 			DAD    D", code[0]); break;
		case 0x1a: printf("%02x 			LDAX   D", code[0]); break;
		case 0x1b: printf("%02x 			DCX    D", code[0]); break;
		case 0x1c: printf("%02x 			INR    E", code[0]); break;
		case 0x1d: printf("%02x 			DCR    E", code[0]); break;
		case 0x1e: printf("%02x %02x 		MVI    E,#$%02x", code[0], code[1], code[1]); opbytes = 2; break;
		case 0x1f: printf("%02x 			RAR", code[0]); break;
			
		case 0x20: printf("%02x 			NOP", code[0]); break;
		case 0x21: printf("%02x %02x %02x 	LXI    H,#$%02x%02x", code[0], code[1], code[2], code[2], code[1]); opbytes=3; break;
		case 0x22: printf("%02x %02x %02x 	SHLD   $%02x%02x", code[0], code[1], code[2], code[2], code[1]); opbytes=3; break;
		case 0x23: printf("%02x 			INX    H", code[0]); break;
		case 0x24: printf("%02x 			INR    H", code[0]); break;
		case 0x25: printf("%02x 			DCR    H", code[0]); break;
		case 0x26: printf("%02x %02x 		MVI    H,#$%02x", code[0], code[1], code[1]); opbytes=2; break;
		case 0x27: printf("%02x 			DAA", code[0]); break;
		case 0x28: printf("%02x 			NOP", code[0]); break;
		case 0x29: printf("%02x 			DAD    H", code[0]); break;
		case 0x2a: printf("%02x %02x %02x 	LHLD   $%02x%02x", code[0], code[1], code[2], code[2], code[1]); opbytes=3; break;
		case 0x2b: printf("%02x 			DCX    H", code[0]); break;
		case 0x2c: printf("%02x 			INR    L", code[0]); break;
		case 0x2d: printf("%02x 			DCR    L", code[0]); break;
		case 0x2e: printf("%02x %02x 		MVI    L,#$%02x", code[0], code[1], code[1]); opbytes = 2; break;
		case 0x2f: printf("%02x 			CMA", code[0]); break;
			
		case 0x30: printf("%02x 			NOP", code[0]); break;
		case 0x31: printf("%02x %02x %02x 	LXI    SP,#$%02x%02x", code[0], code[1], code[2], code[2], code[1]); opbytes=3; break;
		case 0x32: printf("%02x %02x %02x 	STA    $%02x%02x", code[0], code[1], code[2], code[2], code[1]); opbytes=3; break;
		case 0x33: printf("%02x 			INX    SP", code[0]); break;
		case 0x34: printf("%02x 			INR    M", code[0]); break;
		case 0x35: printf("%02x 			DCR    M", code[0]); break;
		case 0x36: printf("%02x %02x 		MVI    M,#$%02x", code[0], code[1], code[1]); opbytes=2; break;
		case 0x37: printf("%02x 			STC", code[0]); break;
		case 0x38: printf("%02x 			NOP", code[0]); break;
		case 0x39: printf("%02x 			DAD    SP", code[0]); break;
		case 0x3a: printf("%02x %02x %02x 	LDA    $%02x%02x", code[0], code[1], code[2], code[2], code[1]); opbytes=3; break;
		case 0x3b: printf("%02x 			DCX    SP", code[0]); break;
		case 0x3c: printf("%02x 			INR    A", code[0]); break;
		case 0x3d: printf("%02x 			DCR    A", code[0]); break;
		case 0x3e: printf("%02x %02x 		MVI    A,#$%02x", code[0], code[1], code[1]); opbytes = 2; break;
		case 0x3f: printf("%02x 			CMC", code[0]); break;
			
		case 0x40: printf("%02x 			MOV    B,B", code[0]); break;
		case 0x41: printf("%02x 			MOV    B,C", code[0]); break;
		case 0x42: printf("%02x 			MOV    B,D", code[0]); break;
		case 0x43: printf("%02x 			MOV    B,E", code[0]); break;
		case 0x44: printf("%02x 			MOV    B,H", code[0]); break;
		case 0x45: printf("%02x 			MOV    B,L", code[0]); break;
		case 0x46: printf("%02x 			MOV    B,M", code[0]); break;
		case 0x47: printf("%02x 			MOV    B,A", code[0]); break;
		case 0x48: printf("%02x 			MOV    C,B", code[0]); break;
		case 0x49: printf("%02x 			MOV    C,C", code[0]); break;
		case 0x4a: printf("%02x 			MOV    C,D", code[0]); break;
		case 0x4b: printf("%02x 			MOV    C,E", code[0]); break;
		case 0x4c: printf("%02x 			MOV    C,H", code[0]); break;
		case 0x4d: printf("%02x 			MOV    C,L", code[0]); break;
		case 0x4e: printf("%02x 			MOV    C,M", code[0]); break;
		case 0x4f: printf("%02x 			MOV    C,A", code[0]); break;
			
		case 0x50: printf("%02x 			MOV    D,B", code[0]); break;
		case 0x51: printf("%02x 			MOV    D,C", code[0]); break;
		case 0x52: printf("%02x 			MOV    D,D", code[0]); break;
		case 0x53: printf("%02x 			MOV    D.E", code[0]); break;
		case 0x54: printf("%02x 			MOV    D,H", code[0]); break;
		case 0x55: printf("%02x 			MOV    D,L", code[0]); break;
		case 0x56: printf("%02x 			MOV    D,M", code[0]); break;
		case 0x57: printf("%02x 			MOV    D,A", code[0]); break;
		case 0x58: printf("%02x 			MOV    E,B", code[0]); break;
		case 0x59: printf("%02x 			MOV    E,C", code[0]); break;
		case 0x5a: printf("%02x 			MOV    E,D", code[0]); break;
		case 0x5b: printf("%02x 			MOV    E,E", code[0]); break;
		case 0x5c: printf("%02x 			MOV    E,H", code[0]); break;
		case 0x5d: printf("%02x 			MOV    E,L", code[0]); break;
		case 0x5e: printf("%02x 			MOV    E,M", code[0]); break;
		case 0x5f: printf("%02x 			MOV    E,A", code[0]); break;

		case 0x60: printf("%02x 			MOV    H,B", code[0]); break;
		case 0x61: printf("%02x 			MOV    H,C", code[0]); break;
		case 0x62: printf("%02x 			MOV    H,D", code[0]); break;
		case 0x63: printf("%02x 			MOV    H.E", code[0]); break;
		case 0x64: printf("%02x 			MOV    H,H", code[0]); break;
		case 0x65: printf("%02x 			MOV    H,L", code[0]); break;
		case 0x66: printf("%02x 			MOV    H,M", code[0]); break;
		case 0x67: printf("%02x 			MOV    H,A", code[0]); break;
		case 0x68: printf("%02x 			MOV    L,B", code[0]); break;
		case 0x69: printf("%02x 			MOV    L,C", code[0]); break;
		case 0x6a: printf("%02x 			MOV    L,D", code[0]); break;
		case 0x6b: printf("%02x 			MOV    L,E", code[0]); break;
		case 0x6c: printf("%02x 			MOV    L,H", code[0]); break;
		case 0x6d: printf("%02x 			MOV    L,L", code[0]); break;
		case 0x6e: printf("%02x 			MOV    L,M", code[0]); break;
		case 0x6f: printf("%02x 			MOV    L,A", code[0]); break;

		case 0x70: printf("%02x 			MOV    M,B", code[0]); break;
		case 0x71: printf("%02x 			MOV    M,C", code[0]); break;
		case 0x72: printf("%02x 			MOV    M,D", code[0]); break;
		case 0x73: printf("%02x 			MOV    M.E", code[0]); break;
		case 0x74: printf("%02x 			MOV    M,H", code[0]); break;
		case 0x75: printf("%02x 			MOV    M,L", code[0]); break;
		case 0x76: printf("%02x 			HLT", code[0]);        break;
		case 0x77: printf("%02x 			MOV    M,A", code[0]); break;
		case 0x78: printf("%02x 			MOV    A,B", code[0]); break;
		case 0x79: printf("%02x 			MOV    A,C", code[0]); break;
		case 0x7a: printf("%02x 			MOV    A,D", code[0]); break;
		case 0x7b: printf("%02x 			MOV    A,E", code[0]); break;
		case 0x7c: printf("%02x 			MOV    A,H", code[0]); break;
		case 0x7d: printf("%02x 			MOV    A,L", code[0]); break;
		case 0x7e: printf("%02x 			MOV    A,M", code[0]); break;
		case 0x7f: printf("%02x 			MOV    A,A", code[0]); break;

		case 0x80: printf("%02x 			ADD    B", code[0]); break;
		case 0x81: printf("%02x 			ADD    C", code[0]); break;
		case 0x82: printf("%02x 			ADD    D", code[0]); break;
		case 0x83: printf("%02x 			ADD    E", code[0]); break;
		case 0x84: printf("%02x 			ADD    H", code[0]); break;
		case 0x85: printf("%02x 			ADD    L", code[0]); break;
		case 0x86: printf("%02x 			ADD    M", code[0]); break;
		case 0x87: printf("%02x 			ADD    A", code[0]); break;
		case 0x88: printf("%02x 			ADC    B", code[0]); break;
		case 0x89: printf("%02x 			ADC    C", code[0]); break;
		case 0x8a: printf("%02x 			ADC    D", code[0]); break;
		case 0x8b: printf("%02x 			ADC    E", code[0]); break;
		case 0x8c: printf("%02x 			ADC    H", code[0]); break;
		case 0x8d: printf("%02x 			ADC    L", code[0]); break;
		case 0x8e: printf("%02x 			ADC    M", code[0]); break;
		case 0x8f: printf("%02x 			ADC    A", code[0]); break;

		case 0x90: printf("%02x 			SUB    B", code[0]); break;
		case 0x91: printf("%02x 			SUB    C", code[0]); break;
		case 0x92: printf("%02x 			SUB    D", code[0]); break;
		case 0x93: printf("%02x 			SUB    E", code[0]); break;
		case 0x94: printf("%02x 			SUB    H", code[0]); break;
		case 0x95: printf("%02x 			SUB    L", code[0]); break;
		case 0x96: printf("%02x 			SUB    M", code[0]); break;
		case 0x97: printf("%02x 			SUB    A", code[0]); break;
		case 0x98: printf("%02x 			SBB    B", code[0]); break;
		case 0x99: printf("%02x 			SBB    C", code[0]); break;
		case 0x9a: printf("%02x 			SBB    D", code[0]); break;
		case 0x9b: printf("%02x 			SBB    E", code[0]); break;
		case 0x9c: printf("%02x 			SBB    H", code[0]); break;
		case 0x9d: printf("%02x 			SBB    L", code[0]); break;
		case 0x9e: printf("%02x 			SBB    M", code[0]); break;
		case 0x9f: printf("%02x 			SBB    A", code[0]); break;

		case 0xa0: printf("%02x 			ANA    B", code[0]); break;
		case 0xa1: printf("%02x 			ANA    C", code[0]); break;
		case 0xa2: printf("%02x 			ANA    D", code[0]); break;
		case 0xa3: printf("%02x 			ANA    E", code[0]); break;
		case 0xa4: printf("%02x 			ANA    H", code[0]); break;
		case 0xa5: printf("%02x 			ANA    L", code[0]); break;
		case 0xa6: printf("%02x 			ANA    M", code[0]); break;
		case 0xa7: printf("%02x 			ANA    A", code[0]); break;
		case 0xa8: printf("%02x 			XRA    B", code[0]); break;
		case 0xa9: printf("%02x 			XRA    C", code[0]); break;
		case 0xaa: printf("%02x 			XRA    D", code[0]); break;
		case 0xab: printf("%02x 			XRA    E", code[0]); break;
		case 0xac: printf("%02x 			XRA    H", code[0]); break;
		case 0xad: printf("%02x 			XRA    L", code[0]); break;
		case 0xae: printf("%02x 			XRA    M", code[0]); break;
		case 0xaf: printf("%02x 			XRA    A", code[0]); break;

		case 0xb0: printf("%02x 			ORA    B", code[0]); break;
		case 0xb1: printf("%02x 			ORA    C", code[0]); break;
		case 0xb2: printf("%02x 			ORA    D", code[0]); break;
		case 0xb3: printf("%02x 			ORA    E", code[0]); break;
		case 0xb4: printf("%02x 			ORA    H", code[0]); break;
		case 0xb5: printf("%02x 			ORA    L", code[0]); break;
		case 0xb6: printf("%02x 			ORA    M", code[0]); break;
		case 0xb7: printf("%02x 			ORA    A", code[0]); break;
		case 0xb8: printf("%02x 			CMP    B", code[0]); break;
		case 0xb9: printf("%02x 			CMP    C", code[0]); break;
		case 0xba: printf("%02x 			CMP    D", code[0]); break;
		case 0xbb: printf("%02x 			CMP    E", code[0]); break;
		case 0xbc: printf("%02x 			CMP    H", code[0]); break;
		case 0xbd: printf("%02x 			CMP    L", code[0]); break;
		case 0xbe: printf("%02x 			CMP    M", code[0]); break;
		case 0xbf: printf("%02x 			CMP    A", code[0]); break;

		case 0xc0: printf("%02x 			RNZ", code[0]); break;
		case 0xc1: printf("%02x 			POP    B", code[0]); break;
		case 0xc2: printf("%02x %02x %02x 	JNZ    $%02x%02x", code[0], code[1], code[2], code[2], code[1]); opbytes = 3; break;
		case 0xc3: printf("%02x %02x %02x 	JMP    $%02x%02x", code[0], code[1], code[2], code[2], code[1]); opbytes = 3; break;
		case 0xc4: printf("%02x %02x %02x 	CNZ    $%02x%02x", code[0], code[1], code[2], code[2], code[1]); opbytes = 3; break;
		case 0xc5: printf("%02x 			PUSH   B", code[0]); break;
		case 0xc6: printf("%02x %02x 		ADI    #$%02x", code[0], code[1], code[1]); opbytes = 2; break;
		case 0xc7: printf("%02x 			RST    0", code[0]); break;
		case 0xc8: printf("%02x 			RZ", code[0]); break;
		case 0xc9: printf("%02x 			RET", code[0]); break;
		case 0xca: printf("%02x %02x %02x 	JZ     $%02x%02x", code[0], code[1], code[2], code[2], code[1]); opbytes = 3; break;
		case 0xcb: printf("%02x %02x %02x 	JMP    $%02x%02x", code[0], code[1], code[2], code[2], code[1]); opbytes = 3; break;
		case 0xcc: printf("%02x %02x %02x 	CZ     $%02x%02x", code[0], code[1], code[2], code[2], code[1]); opbytes = 3; break;
		case 0xcd: printf("%02x %02x %02x 	CALL   $%02x%02x", code[0], code[1], code[2], code[2], code[1]); opbytes = 3; break;
		case 0xce: printf("%02x %02x 		ACI    #$%02x", code[0], code[1], code[1]); opbytes = 2; break;
		case 0xcf: printf("%02x 			RST    1", code[0]); break;

		case 0xd0: printf("%02x 			RNC", code[0]); break;
		case 0xd1: printf("%02x 			POP    D", code[0]); break;
		case 0xd2: printf("%02x %02x %02x 	JNC    $%02x%02x", code[0], code[1], code[2], code[2], code[1]); opbytes = 3; break;
		case 0xd3: printf("%02x %02x 		OUT    #$%02x", code[0], code[1], code[1]); opbytes = 2; break;
		case 0xd4: printf("%02x %02x %02x 	CNC    $%02x%02x",code[0], code[1], code[2], code[2], code[1]); opbytes = 3; break;
		case 0xd5: printf("%02x 			PUSH   D", code[0]); break;
		case 0xd6: printf("%02x %02x 		SUI    #$%02x",code[0], code[1], code[1]); opbytes = 2; break;
		case 0xd7: printf("%02x 			RST    2", code[0]); break;
		case 0xd8: printf("%02x 			RC", code[0]);  break;
		case 0xd9: printf("%02x 			RET", code[0]); break;
		case 0xda: printf("%02x %02x %02x 	JC     $%02x%02x", code[0], code[1], code[2], code[2], code[1]); opbytes = 3; break;
		case 0xdb: printf("%02x %02x 		IN     #$%02x", code[0], code[1], code[1]); opbytes = 2; break;
		case 0xdc: printf("%02x %02x %02x 	CC     $%02x%02x", code[0], code[1], code[2], code[2], code[1]); opbytes = 3; break;
		case 0xdd: printf("%02x %02x %02x 	CALL   $%02x%02x", code[0], code[1], code[2], code[2], code[1]); opbytes = 3; break;
		case 0xde: printf("%02x %02x 		SBI    #$%02x", code[0], code[1], code[1]); opbytes = 2; break;
		case 0xdf: printf("%02x 			RST    3", code[0]); break;

		case 0xe0: printf("%02x				RPO", code[0]); break;
		case 0xe1: printf("%02x				POP    H", code[0]); break;
		case 0xe2: printf("%02x %02x %02x	JPO    $%02x%02x", code[0], code[1], code[2], code[2],code[1]); opbytes = 3; break;
		case 0xe3: printf("%02x 			XTHL", code[0]);break;
		case 0xe4: printf("%02x %02x %02x 	CPO    $%02x%02x", code[0], code[1], code[2], code[2],code[1]); opbytes = 3; break;
		case 0xe5: printf("%02x 			PUSH   H", code[0]); break;
		case 0xe6: printf("%02x %02x 		ANI    #$%02x", code[0], code[1], code[1]); opbytes = 2; break;
		case 0xe7: printf("%02x 			RST    4", code[0]); break;
		case 0xe8: printf("%02x 			RPE", code[0]); break;
		case 0xe9: printf("%02x 			PCHL", code[0]);break;
		case 0xea: printf("%02x %02x %02x 	JPE    $%02x%02x", code[0], code[1], code[2], code[2],code[1]); opbytes = 3; break;
		case 0xeb: printf("%02x 			XCHG", code[0]); break;
		case 0xec: printf("%02x %02x %02x 	CPE     $%02x%02x", code[0], code[1], code[2], code[2],code[1]); opbytes = 3; break;
		case 0xed: printf("%02x %02x %02x 	CALL    $%02x%02x", code[0], code[1], code[2], code[2],code[1]); opbytes = 3; break;
		case 0xee: printf("%02x %02x 		XRI    #$%02x", code[0], code[1], code[1]); opbytes = 2; break;
		case 0xef: printf("%02x 			RST    5", code[0]); break;

		case 0xf0: printf("%02x 			RP", code[0]);  break;
		case 0xf1: printf("%02x 			POP    PSW", code[0]); break;
		case 0xf2: printf("%02x %02x %02x 	JP     $%02x%02x", code[0], code[1], code[2], code[2],code[1]); opbytes = 3; break;
		case 0xf3: printf("%02x 			DI", code[0]);  break;
		case 0xf4: printf("%02x %02x %02x 	CP     $%02x%02x", code[0], code[1], code[2], code[2],code[1]); opbytes = 3; break;
		case 0xf5: printf("%02x 			PUSH   PSW", code[0]); break;
		case 0xf6: printf("%02x %02x 		ORI    #$%02x", code[0], code[1], code[1]); opbytes = 2; break;
		case 0xf7: printf("%02x 			RST    6", code[0]); break;
		case 0xf8: printf("%02x 			RM", code[0]);  break;
		case 0xf9: printf("%02x 			SPHL", code[0]);break;
		case 0xfa: printf("%02x %02x %02x 	JM     $%02x%02x", code[0], code[1], code[2], code[2],code[1]); opbytes = 3; break;
		case 0xfb: printf("%02x 			EI", code[0]);  break;
		case 0xfc: printf("%02x %02x %02x 	CM     $%02x%02x", code[0], code[1], code[2], code[2], code[1]); opbytes = 3; break;
		case 0xfd: printf("%02x %02x %02x 	CALL   $%02x%02x", code[0], code[1], code[2], code[2], code[1]); opbytes = 3; break;
		case 0xfe: printf("%02x %02x 		CPI    #$%02x", code[0], code[1], code[1]); opbytes = 2; break;
		case 0xff: printf("%02x 			RST    7", code[0]); break;
    }
    
    printf("\n");
    return opbytes;
}

// int main(int argc, char**argv){
//     FILE *f = fopen(argv[1], "rb");
//     if (f==NULL){
//         printf("error: Couldn't open %sn", argv[1]);
//         exit(1);
//     }

//     //get file size and read it into memory buffer
//     fseek(f, 0L, SEEK_END); // jump to the end of file
//     int fsize = ftell(f);   // return the current position of f
//     fseek(f, 0L, SEEK_SET); // jump back to the start of the file

//     unsigned char * buffer = malloc(fsize);
//     fread(buffer, fsize, 1, f);
//     fclose(f);

//     int pc = 0;
//     while (pc<fsize){
//         pc += Disassemble8080Op(buffer, pc);
//     }
//     return 0;
// }