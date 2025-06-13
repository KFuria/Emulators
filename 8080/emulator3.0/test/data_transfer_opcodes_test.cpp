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

TEST_F(OpcodeTests, MVI_B){

    // Test MVI B, D8 (0x06)
    uint16_t initial_pc = cpu.getPC();

    loadAndRun(initial_pc, {0x06, 0xAA});
    EXPECT_EQ(cpu.getPC(), initial_pc+2);
    EXPECT_EQ(cpu.getBC(), 0xAA00);
    EXPECT_EQ(cpu.getDE(), 0x0000);
    EXPECT_EQ(cpu.getHL(), 0x0000);
    EXPECT_EQ(cpu.getPSW(), 0x0002);
    EXPECT_EQ(cpu.getCyc(), 7);

}

TEST_F(OpcodeTests, MVI_C){

    // Test MVI C, D8 (0x0E)
    uint16_t initial_pc = cpu.getPC();

    loadAndRun(initial_pc, {0x0E, 0xAA});
    EXPECT_EQ(cpu.getPC(), initial_pc+2);
    EXPECT_EQ(cpu.getBC(), 0x00AA);
    EXPECT_EQ(cpu.getDE(), 0x0000);
    EXPECT_EQ(cpu.getHL(), 0x0000);
    EXPECT_EQ(cpu.getPSW(), 0x0002);
    EXPECT_EQ(cpu.getCyc(), 7);

}

TEST_F(OpcodeTests, MVI_D){

    // Test MVI D, D8 (0x16)
    uint16_t initial_pc = cpu.getPC();

    loadAndRun(initial_pc, {0x16, 0xAA});
    EXPECT_EQ(cpu.getPC(), initial_pc+2);
    EXPECT_EQ(cpu.getBC(), 0x0000);
    EXPECT_EQ(cpu.getDE(), 0xAA00);
    EXPECT_EQ(cpu.getHL(), 0x0000);
    EXPECT_EQ(cpu.getPSW(), 0x0002);
    EXPECT_EQ(cpu.getCyc(), 7);

}

TEST_F(OpcodeTests, MVI_E){

    // Test MVI E, D8 (0x1E)
    uint16_t initial_pc = cpu.getPC();

    loadAndRun(initial_pc, {0x1E, 0xAA});
    EXPECT_EQ(cpu.getPC(), initial_pc+2);
    EXPECT_EQ(cpu.getBC(), 0x0000);
    EXPECT_EQ(cpu.getDE(), 0x00AA);
    EXPECT_EQ(cpu.getHL(), 0x0000);
    EXPECT_EQ(cpu.getPSW(), 0x0002);
    EXPECT_EQ(cpu.getCyc(), 7);

}

TEST_F(OpcodeTests, MVI_H){

    // Test MVI H, D8 (0x26)
    uint16_t initial_pc = cpu.getPC();

    loadAndRun(initial_pc, {0x26, 0xAA});
    EXPECT_EQ(cpu.getPC(), initial_pc+2);
    EXPECT_EQ(cpu.getBC(), 0x0000);
    EXPECT_EQ(cpu.getDE(), 0x0000);
    EXPECT_EQ(cpu.getHL(), 0xAA00);
    EXPECT_EQ(cpu.getPSW(), 0x0002);
    EXPECT_EQ(cpu.getCyc(), 7);

}

TEST_F(OpcodeTests, MVI_L){

    // Test MVI L, D8 (0x2E)
    uint16_t initial_pc = cpu.getPC();

    loadAndRun(initial_pc, {0x2E, 0xAA});
    EXPECT_EQ(cpu.getPC(), initial_pc+2);
    EXPECT_EQ(cpu.getBC(), 0x0000);
    EXPECT_EQ(cpu.getDE(), 0x0000);
    EXPECT_EQ(cpu.getHL(), 0x00AA);
    EXPECT_EQ(cpu.getPSW(), 0x0002);
    EXPECT_EQ(cpu.getCyc(), 7);

}

TEST_F(OpcodeTests, MVI_M){

    // Test MVI M, D8 (0x36)
    uint16_t initial_pc = cpu.getPC();
    cpu.setHL(0x2000);

    loadAndRun(initial_pc, {0x36, 0xAA});
    EXPECT_EQ(cpu.getPC(), initial_pc+2);
    EXPECT_EQ(cpu.getBC(), 0x0000);
    EXPECT_EQ(cpu.getDE(), 0x0000);
    EXPECT_EQ(cpu.getHL(), 0x2000);
    EXPECT_EQ(cpu.getPSW(), 0x0002);
    EXPECT_EQ(hal.read_byte(0x2000), 0xAA);
    EXPECT_EQ(cpu.getCyc(), 10);

}

TEST_F(OpcodeTests, MVI_A){

    // Test MVI A, D8 (0x3E)
    uint16_t initial_pc = cpu.getPC();

    loadAndRun(initial_pc, {0x3E, 0xAA});
    EXPECT_EQ(cpu.getPC(), initial_pc+2);
    EXPECT_EQ(cpu.getBC(), 0x0000);
    EXPECT_EQ(cpu.getDE(), 0x0000);
    EXPECT_EQ(cpu.getHL(), 0x0000);
    EXPECT_EQ(cpu.getPSW(), 0xAA02);
    EXPECT_EQ(cpu.getCyc(), 7);

}

TEST_F(OpcodeTests, LDAX_BC){

    // Test LDAX B (0x0A)
    uint16_t initial_pc = cpu.getPC();
    
    // Set memory
    hal.write_byte(0x0000, 0xAA);
    hal.write_byte(0x0001, 0xBB);

    cpu.setBC(0x0000);  // Set BC to memory location
    cpu.setDE(0x0001);  // Set DE to different memory location 
    
    loadAndRun(initial_pc, {0x0A});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getA(), 0xAA);
    EXPECT_EQ(cpu.getFlags(), 0x02);
    EXPECT_EQ(cpu.getCyc(), 7);

}

TEST_F(OpcodeTests, LDAX_DE){

    // Test LDAX DE (0x1A)
    uint16_t initial_pc = cpu.getPC();
    
    // Set memory
    hal.write_byte(0x0000, 0xAA);
    hal.write_byte(0x0001, 0xBB);

    cpu.setBC(0x0000);  // Set BC to memory location
    cpu.setDE(0x0001);  // Set DE to different memory location 
    
    loadAndRun(initial_pc, {0x1A});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getA(), 0xBB);
    EXPECT_EQ(cpu.getFlags(), 0x02);
    EXPECT_EQ(cpu.getCyc(), 7);
    
}

TEST_F(OpcodeTests, SHLD){

    // Test SHLD D16 (0x22)
    uint16_t initial_pc = cpu.getPC();

    // Ensure memory is 00
    hal.write_byte(0x0011, 0x00);
    hal.write_byte(0x0012, 0x00);

    cpu.setHL(0x1234);

    loadAndRun(initial_pc, {0x22, 0x11, 0x00});
    EXPECT_EQ(cpu.getPC(), initial_pc + 3);
    EXPECT_EQ(hal.read_byte(0x0011), 0x34);
    EXPECT_EQ(hal.read_byte(0x0012), 0x12);
    EXPECT_EQ(cpu.getHL(), 0x1234);
    EXPECT_EQ(cpu.getFlags(), 0x02);
    EXPECT_EQ(cpu.getCyc(), 16);
}


