#include "i8080.h"
#include "i8080_helpers.h"

T8080::T8080(){
    logger = TLogger::getInstance();
	logger->setLogLevel(ELogLevel::OP);

	reset();
	logger->log("8080 Initialized", ELogLevel::INFO);
}

T8080::~T8080(){
	logger->log("8080 Deinitialized", ELogLevel::INFO);
}

void T8080::setHal(T8080Hal * Hal){
	hal = Hal;
}

void T8080::reset(){
	PC = 0;
	SP = 0;
	set_bc(0x00);
	set_de(0x00);
	set_hl(0x00);
	set_psw(0x0002);

	iff = 0;
	interrupt_delay = 0;
	interrupt_pending = 0;
	interrupt_vector = 0;

	halted = 0;
	cyc = 0;
}

void T8080::step(){
	if(interrupt_pending && iff && interrupt_delay == 0){
		interrupt_pending = 0;
		iff = 0;
		halted = 0;
		execute(interrupt_vector);
	}else if(!halted){
		execute(read_byte());
	}
}

void T8080::execute(uint8_t op){
	InstructionFunc v = instruction_set[op];
	cyc += (this->*v)(op);
}

