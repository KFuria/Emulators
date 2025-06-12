#include "test_fixture.h"


//-----------------------------------------------------------------------------
// Individual Opcode Test Cases
//-----------------------------------------------------------------------------

// Test LXI (0x01)
TEST_F(OpcodeTests, LXI_B){
    
    // Test LXI B, D16 (0x01)
    uint16_t initial_pc = cpu.getPC();
    loadAndRun(initial_pc, {0x01, 0xAA, 0xBB});
    
    EXPECT_EQ(cpu.getPC(), initial_pc + 3);
    EXPECT_EQ(cpu.getBC(), 0xBBAA);
    EXPECT_EQ(cpu.getDE(), 0x0000);
    EXPECT_EQ(cpu.getHL(), 0x0000);
    EXPECT_EQ(cpu.getA(), 0x00);
    EXPECT_EQ(cpu.getFlags(), 0x02);
    EXPECT_EQ(cpu.getCyc(), 10);

}

TEST_F(OpcodeTests, LXI_D){

    // Test LXI D, D16 (0x11)
    uint16_t initial_pc = cpu.getPC();
    loadAndRun(initial_pc, {0x11, 0xAA, 0xBB});
    EXPECT_EQ(cpu.getPC(), initial_pc + 3);
    EXPECT_EQ(cpu.getBC(), 0x0000);
    EXPECT_EQ(cpu.getDE(), 0xBBAA);
    EXPECT_EQ(cpu.getHL(), 0x0000);
    EXPECT_EQ(cpu.getA(), 0x00);
    EXPECT_EQ(cpu.getFlags(), 0x02);
    EXPECT_EQ(cpu.getCyc(), 10);

}

TEST_F(OpcodeTests, LXI_H){

    // Test LXI H, D16 (0x21)
    uint16_t initial_pc = cpu.getPC();
    loadAndRun(initial_pc, {0x21, 0xAA, 0xBB});
    EXPECT_EQ(cpu.getPC(), initial_pc + 3);
    EXPECT_EQ(cpu.getBC(), 0x0000);
    EXPECT_EQ(cpu.getDE(), 0x0000);
    EXPECT_EQ(cpu.getHL(), 0xBBAA);
    EXPECT_EQ(cpu.getA(), 0x00);
    EXPECT_EQ(cpu.getFlags(), 0x02);
    EXPECT_EQ(cpu.getCyc(), 10);

}

TEST_F(OpcodeTests, LXI_SP){

    // Test LXI SP, D16 (0x31)
    uint16_t initial_pc = cpu.getPC();
    loadAndRun(initial_pc, {0x31, 0xAA, 0xBB});
    EXPECT_EQ(cpu.getPC(), initial_pc + 3);
    EXPECT_EQ(cpu.getBC(), 0x0000);
    EXPECT_EQ(cpu.getDE(), 0x0000);
    EXPECT_EQ(cpu.getHL(), 0x0000);
    EXPECT_EQ(cpu.getSP(), 0xBBAA);
    EXPECT_EQ(cpu.getA(), 0x00);
    EXPECT_EQ(cpu.getFlags(), 0x02);
    EXPECT_EQ(cpu.getCyc(), 10);

}

TEST_F(OpcodeTests, STAX_BC){

    // Test SPAX rp (0x02)
    uint16_t initial_pc = cpu.getPC();
    
    // ensure memory is set to 0x00
    hal.write_byte(0x0000, 0x00);
    hal.write_byte(0x0001, 0x00);

    cpu.setA(0x42);     // Set A
    cpu.setBC(0x0000);  // Set BC to memory location
    cpu.setDE(0x0001);  // Set DE to different memory location 
    loadAndRun(initial_pc, {0x02});

    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(hal.read_byte(0x0000), 0x42);
    EXPECT_EQ(hal.read_byte(0x0001), 0x00); // memory location at DE should be unaffected
    EXPECT_EQ(cpu.getFlags(), 0x02);
    EXPECT_EQ(cpu.getCyc(), 7);

}

TEST_F(OpcodeTests, STAX_DE){

    // Test SPAX rp (0x12)
    uint16_t initial_pc = cpu.getPC();
    
    // ensure memory is set to 0x00
    hal.write_byte(0x0000, 0x00);
    hal.write_byte(0x0001, 0x00);

    cpu.setA(0x42);     // Set A
    cpu.setBC(0x0000);  // Set BC to memory location
    cpu.setDE(0x0001);  // Set DE to different memory location 
    loadAndRun(initial_pc, {0x12});

    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(hal.read_byte(0x0000), 0x00); // memory location at BC should be unaffected
    EXPECT_EQ(hal.read_byte(0x0001), 0x42);
    EXPECT_EQ(cpu.getFlags(), 0x02);
    EXPECT_EQ(cpu.getCyc(), 7);
    
}

