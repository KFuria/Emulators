#include "opcodes_test.h"


//-----------------------------------------------------------------------------
// Individual Opcode Test Cases
//-----------------------------------------------------------------------------

// Test NOP (0x00)
TEST_F(OpcodeTests, NOP) {
    uint16_t initial_pc = cpu.getPC();
    loadAndRun(initial_pc, {0x00}); // Place NOP at PC

    // NOP takes 1 byte, so PC should advance by 1
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getCyc(), 4);

}

