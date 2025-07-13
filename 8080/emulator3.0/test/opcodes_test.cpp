#include "opcodes_test.h"


T8080 OpcodeTests::cpu;
THal OpcodeTests::hal;

//-----------------------------------------------------------------------------
// OpcodeTests Fixture Method Definitions
//-----------------------------------------------------------------------------
void OpcodeTests::SetUpTestSuite() {
    // Initialize CPU and HAL once for the entire test suite
    cpu.setHal(&hal);
}

void OpcodeTests::TearDownTestSuite() {
    // No teardown needed
}

void OpcodeTests::SetUp() {
    // Reset the CPU before each individual test
    cpu.reset();
    
    // Set common initial state for tests
    cpu.setPC(0x0100); // Common test program start address
    cpu.setSP(0xFF00); // Common stack address
}

void OpcodeTests::TearDown() {
    // No teardown needed
}


// Helper function to load an instruction into mock memory and run it
void OpcodeTests::loadAndRun(uint16_t start_addr, const std::vector<uint8_t>& program_bytes) {
    for (size_t i = 0; i < program_bytes.size(); ++i) {
        hal.write_byte(start_addr + i, program_bytes[i]);
    }
    cpu.setPC(start_addr);  // Set PC to program start
    cpu.step();             // Execute one instruction
}


