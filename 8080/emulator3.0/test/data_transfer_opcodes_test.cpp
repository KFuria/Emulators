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

TEST_F(OpcodeTests, LHLD){

    // Test LHLD D16 (0x2A)
    uint16_t initial_pc = cpu.getPC();

    // Set memory
    hal.write_byte(0x0011, 0x34);
    hal.write_byte(0x0012, 0x12);

    loadAndRun(initial_pc, {0x2A, 0x11, 0x00});
    EXPECT_EQ(cpu.getPC(), initial_pc + 3);
    EXPECT_EQ(cpu.getHL(), 0x1234);
    EXPECT_EQ(cpu.getFlags(), 0x02);
    EXPECT_EQ(cpu.getCyc(), 16);

}

TEST_F(OpcodeTests, STA){

    // Test STA D16 (0x32)
    uint16_t initial_pc = cpu.getPC();
    
    // Ensure memory is 00
    hal.write_byte(0x0011, 0x00);
    hal.write_byte(0x0012, 0x00);

    cpu.setA(0x42);

    loadAndRun(initial_pc, {0x32, 0x11, 0x00});
    EXPECT_EQ(cpu.getPC(), initial_pc + 3);
    EXPECT_EQ(hal.read_byte(0x0011), 0x42);
    EXPECT_EQ(cpu.getFlags(), 0x02);
    EXPECT_EQ(cpu.getCyc(), 13);

}

TEST_F(OpcodeTests, LDA){

    // Test LDA D16 (0x3A)
    uint16_t initial_pc = cpu.getPC();
    
    // Set memory
    hal.write_byte(0x0011, 0x42);

    loadAndRun(initial_pc, {0x3A, 0x11, 0x00});
    EXPECT_EQ(cpu.getPC(), initial_pc + 3);
    EXPECT_EQ(cpu.getA(), 0x42);
    EXPECT_EQ(cpu.getFlags(), 0x02);
    EXPECT_EQ(cpu.getCyc(), 13);

}

TEST_F(OpcodeTests, MOV_B){

    // Test MOV B, r (0x40-0x47)
    uint16_t initial_pc = cpu.getPC();
    
    // Test MOV B, B (0x40)
    cpu.setB(0xAA);
    loadAndRun(initial_pc, {0x40});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getBC(), 0xAA00);
    EXPECT_EQ(cpu.getDE(), 0x0000);
    EXPECT_EQ(cpu.getHL(), 0x0000);
    EXPECT_EQ(cpu.getA(), 0x00);
    EXPECT_EQ(cpu.getFlags(), 0x02);
    EXPECT_EQ(cpu.getCyc(), 5);

    // Test MOV B, C (0x41)
    cpu.setC(0xBB);
    loadAndRun(initial_pc, {0x41}); 
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getBC(), 0xBBBB);
    EXPECT_EQ(cpu.getDE(), 0x0000);
    EXPECT_EQ(cpu.getHL(), 0x0000);
    EXPECT_EQ(cpu.getA(), 0x00);
    EXPECT_EQ(cpu.getFlags(), 0x02);
    EXPECT_EQ(cpu.getCyc(), 10);

    // Test MOV B, D (0x42)
    cpu.setD(0xCC);
    loadAndRun(initial_pc, {0x42});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getBC(), 0xCCBB);
    EXPECT_EQ(cpu.getDE(), 0xCC00);
    EXPECT_EQ(cpu.getHL(), 0x0000);
    EXPECT_EQ(cpu.getA(), 0x00);
    EXPECT_EQ(cpu.getFlags(), 0x02);
    EXPECT_EQ(cpu.getCyc(), 15);

    // Test MOV B, E (0x43)    
    cpu.setE(0xDD);
    loadAndRun(initial_pc, {0x43});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getBC(), 0xDDBB);
    EXPECT_EQ(cpu.getDE(), 0xCCDD);
    EXPECT_EQ(cpu.getHL(), 0x0000);
    EXPECT_EQ(cpu.getA(), 0x00);
    EXPECT_EQ(cpu.getFlags(), 0x02);
    EXPECT_EQ(cpu.getCyc(), 20);

    // Test MOV B, H (0x44)
    cpu.setH(0xEE);
    loadAndRun(initial_pc, {0x44});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getBC(), 0xEEBB);
    EXPECT_EQ(cpu.getDE(), 0xCCDD);
    EXPECT_EQ(cpu.getHL(), 0xEE00);
    EXPECT_EQ(cpu.getA(), 0x00);
    EXPECT_EQ(cpu.getFlags(), 0x02);
    EXPECT_EQ(cpu.getCyc(), 25);

    // Test MOV B, L (0x45)
    cpu.setL(0xFF);
    loadAndRun(initial_pc, {0x45});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getBC(), 0xFFBB);
    EXPECT_EQ(cpu.getDE(), 0xCCDD);
    EXPECT_EQ(cpu.getHL(), 0xEEFF);
    EXPECT_EQ(cpu.getA(), 0x00);
    EXPECT_EQ(cpu.getFlags(), 0x02);
    EXPECT_EQ(cpu.getCyc(), 30);

    // Test MOV B, M (0x46)
    cpu.setHL(0x2000);
    hal.write_byte(0x2000, 0x11); // Set memory at HL to 0x11
    loadAndRun(initial_pc, {0x46});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getBC(), 0x11BB);
    EXPECT_EQ(cpu.getDE(), 0xCCDD);
    EXPECT_EQ(cpu.getHL(), 0x2000);
    EXPECT_EQ(cpu.getA(), 0x00);
    EXPECT_EQ(cpu.getFlags(), 0x02);
    EXPECT_EQ(cpu.getCyc(), 37);

    // Test MOV B, A (0x47)
    cpu.setA(0x22);
    loadAndRun(initial_pc, {0x47});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getBC(), 0x22BB);
    EXPECT_EQ(cpu.getDE(), 0xCCDD);
    EXPECT_EQ(cpu.getHL(), 0x2000);
    EXPECT_EQ(cpu.getA(), 0x22);
    EXPECT_EQ(cpu.getFlags(), 0x02);
    EXPECT_EQ(cpu.getCyc(), 42);

}

TEST_F(OpcodeTests, MOV_C){

    // Test MOV C, r (0x48-0x4F)
    uint16_t initial_pc = cpu.getPC();
    
    // Test MOV C, B (0x48)
    cpu.setB(0xAA);
    loadAndRun(initial_pc, {0x48});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getBC(), 0xAAAA);
    EXPECT_EQ(cpu.getDE(), 0x0000);
    EXPECT_EQ(cpu.getHL(), 0x0000);
    EXPECT_EQ(cpu.getA(), 0x00);
    EXPECT_EQ(cpu.getFlags(), 0x02);
    EXPECT_EQ(cpu.getCyc(), 5);

    // Test MOV C, C (0x49)
    cpu.setC(0xBB);
    loadAndRun(initial_pc, {0x49}); 
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getBC(), 0xAABB);
    EXPECT_EQ(cpu.getDE(), 0x0000);
    EXPECT_EQ(cpu.getHL(), 0x0000);
    EXPECT_EQ(cpu.getA(), 0x00);
    EXPECT_EQ(cpu.getFlags(), 0x02);
    EXPECT_EQ(cpu.getCyc(), 10);

    // Test MOV C, D (0x4A)
    cpu.setD(0xCC);
    loadAndRun(initial_pc, {0x4A});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getBC(), 0xAACC);
    EXPECT_EQ(cpu.getDE(), 0xCC00);
    EXPECT_EQ(cpu.getHL(), 0x0000);
    EXPECT_EQ(cpu.getA(), 0x00);
    EXPECT_EQ(cpu.getFlags(), 0x02);
    EXPECT_EQ(cpu.getCyc(), 15);

    // Test MOV C, E (0x4B)    
    cpu.setE(0xDD);
    loadAndRun(initial_pc, {0x4B});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getBC(), 0xAADD);
    EXPECT_EQ(cpu.getDE(), 0xCCDD);
    EXPECT_EQ(cpu.getHL(), 0x0000);
    EXPECT_EQ(cpu.getA(), 0x00);
    EXPECT_EQ(cpu.getFlags(), 0x02);
    EXPECT_EQ(cpu.getCyc(), 20);

    // Test MOV C, H (0x4C)
    cpu.setH(0xEE); 
    loadAndRun(initial_pc, {0x4C});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getBC(), 0xAAEE);
    EXPECT_EQ(cpu.getDE(), 0xCCDD);
    EXPECT_EQ(cpu.getHL(), 0xEE00);
    EXPECT_EQ(cpu.getA(), 0x00);
    EXPECT_EQ(cpu.getFlags(), 0x02);
    EXPECT_EQ(cpu.getCyc(), 25);

    // Test MOV C, L (0x4D)
    cpu.setL(0xFF);
    loadAndRun(initial_pc, {0x4D});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getBC(), 0xAAFF);
    EXPECT_EQ(cpu.getDE(), 0xCCDD);
    EXPECT_EQ(cpu.getHL(), 0xEEFF);
    EXPECT_EQ(cpu.getA(), 0x00);
    EXPECT_EQ(cpu.getFlags(), 0x02);
    EXPECT_EQ(cpu.getCyc(), 30);

    // Test MOV C, M (0x4E)
    cpu.setHL(0x2000);
    hal.write_byte(0x2000, 0x11); // Set memory at HL to 0x11
    loadAndRun(initial_pc, {0x4E});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getBC(), 0xAA11);
    EXPECT_EQ(cpu.getDE(), 0xCCDD);
    EXPECT_EQ(cpu.getHL(), 0x2000);
    EXPECT_EQ(cpu.getA(), 0x00);
    EXPECT_EQ(cpu.getFlags(), 0x02);
    EXPECT_EQ(cpu.getCyc(), 37);

    // Test MOV C, A (0x4F)
    cpu.setA(0x22);
    loadAndRun(initial_pc, {0x4F});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getBC(), 0xAA22);
    EXPECT_EQ(cpu.getDE(), 0xCCDD);
    EXPECT_EQ(cpu.getHL(), 0x2000);
    EXPECT_EQ(cpu.getA(), 0x22);
    EXPECT_EQ(cpu.getFlags(), 0x02);
    EXPECT_EQ(cpu.getCyc(), 42);

}

TEST_F(OpcodeTests, MOV_D){

    // Test MOV D, r (0x50-0x57)
    uint16_t initial_pc = cpu.getPC();
    
    // Test MOV D, B (0x50)
    cpu.setB(0xAA);
    loadAndRun(initial_pc, {0x50});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getBC(), 0xAA00);
    EXPECT_EQ(cpu.getDE(), 0xAA00);
    EXPECT_EQ(cpu.getHL(), 0x0000);
    EXPECT_EQ(cpu.getA(), 0x00);
    EXPECT_EQ(cpu.getFlags(), 0x02);
    EXPECT_EQ(cpu.getCyc(), 5);

    // Test MOV D, C (0x51)
    cpu.setC(0xBB);
    loadAndRun(initial_pc, {0x51}); 
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getBC(), 0xAABB);
    EXPECT_EQ(cpu.getDE(), 0xBB00);
    EXPECT_EQ(cpu.getHL(), 0x0000);
    EXPECT_EQ(cpu.getA(), 0x00);
    EXPECT_EQ(cpu.getFlags(), 0x02);
    EXPECT_EQ(cpu.getCyc(), 10);

    // Test MOV D, D (0x52)
    cpu.setD(0xCC);
    loadAndRun(initial_pc, {0x52});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getBC(), 0xAABB);
    EXPECT_EQ(cpu.getDE(), 0xCC00);
    EXPECT_EQ(cpu.getHL(), 0x0000);
    EXPECT_EQ(cpu.getA(), 0x00);
    EXPECT_EQ(cpu.getFlags(), 0x02);
    EXPECT_EQ(cpu.getCyc(), 15);

    // Test MOV D, E (0x53)
    cpu.setE(0xDD);
    loadAndRun(initial_pc, {0x53});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getBC(), 0xAABB);
    EXPECT_EQ(cpu.getDE(), 0xDDDD);
    EXPECT_EQ(cpu.getHL(), 0x0000);
    EXPECT_EQ(cpu.getA(), 0x00);
    EXPECT_EQ(cpu.getFlags(), 0x02);
    EXPECT_EQ(cpu.getCyc(), 20);

    // Test MOV D, H (0x54)
    cpu.setH(0xEE);
    loadAndRun(initial_pc, {0x54});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getBC(), 0xAABB);
    EXPECT_EQ(cpu.getDE(), 0xEEDD);
    EXPECT_EQ(cpu.getHL(), 0xEE00);
    EXPECT_EQ(cpu.getA(), 0x00);
    EXPECT_EQ(cpu.getFlags(), 0x02);
    EXPECT_EQ(cpu.getCyc(), 25);

    // Test MOV D, L (0x55)
    cpu.setL(0xFF);
    loadAndRun(initial_pc, {0x55});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getBC(), 0xAABB);
    EXPECT_EQ(cpu.getDE(), 0xFFDD);
    EXPECT_EQ(cpu.getHL(), 0xEEFF);
    EXPECT_EQ(cpu.getA(), 0x00);
    EXPECT_EQ(cpu.getFlags(), 0x02);
    EXPECT_EQ(cpu.getCyc(), 30);

    // Test MOV D, M (0x56)
    cpu.setHL(0x2000);
    hal.write_byte(0x2000, 0x11); // Set memory at HL to 0x11
    loadAndRun(initial_pc, {0x56});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getBC(), 0xAABB);
    EXPECT_EQ(cpu.getDE(), 0x11DD);
    EXPECT_EQ(cpu.getHL(), 0x2000);
    EXPECT_EQ(cpu.getA(), 0x00);
    EXPECT_EQ(cpu.getFlags(), 0x02);
    EXPECT_EQ(cpu.getCyc(), 37);

    // Test MOV D, A (0x57)
    cpu.setA(0x22);
    loadAndRun(initial_pc, {0x57});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getBC(), 0xAABB);
    EXPECT_EQ(cpu.getDE(), 0x22DD);
    EXPECT_EQ(cpu.getHL(), 0x2000);
    EXPECT_EQ(cpu.getA(), 0x22);
    EXPECT_EQ(cpu.getFlags(), 0x02);
    EXPECT_EQ(cpu.getCyc(), 42);

}

TEST_F(OpcodeTests, MOV_E){

    // Test MOV E, r (0x58-0x5F)
    uint16_t initial_pc = cpu.getPC();
    
    // Test MOV E, B (0x58)
    cpu.setB(0xAA);
    loadAndRun(initial_pc, {0x58});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getBC(), 0xAA00);
    EXPECT_EQ(cpu.getDE(), 0x00AA);
    EXPECT_EQ(cpu.getHL(), 0x0000);
    EXPECT_EQ(cpu.getA(), 0x00);
    EXPECT_EQ(cpu.getFlags(), 0x02);
    EXPECT_EQ(cpu.getCyc(), 5);

    // Test MOV E, C (0x59)
    cpu.setC(0xBB);
    loadAndRun(initial_pc, {0x59}); 
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getBC(), 0xAABB);
    EXPECT_EQ(cpu.getDE(), 0x00BB);
    EXPECT_EQ(cpu.getHL(), 0x0000);
    EXPECT_EQ(cpu.getA(), 0x00);
    EXPECT_EQ(cpu.getFlags(), 0x02);
    EXPECT_EQ(cpu.getCyc(), 10);

    // Test MOV E, D (0x5A)
    cpu.setD(0xCC);
    loadAndRun(initial_pc, {0x5A});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getBC(), 0xAABB);
    EXPECT_EQ(cpu.getDE(), 0xCCCC);
    EXPECT_EQ(cpu.getHL(), 0x0000);
    EXPECT_EQ(cpu.getA(), 0x00);
    EXPECT_EQ(cpu.getFlags(), 0x02);
    EXPECT_EQ(cpu.getCyc(), 15);

    // Test MOV E, E (0x5B)
    cpu.setE(0xDD);
    loadAndRun(initial_pc, {0x5B});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getBC(), 0xAABB);
    EXPECT_EQ(cpu.getDE(), 0xCCDD);
    EXPECT_EQ(cpu.getHL(), 0x0000);
    EXPECT_EQ(cpu.getA(), 0x00);
    EXPECT_EQ(cpu.getFlags(), 0x02);
    EXPECT_EQ(cpu.getCyc(), 20);

    // Test MOV E, H (0x5C)
    cpu.setH(0xEE);
    loadAndRun(initial_pc, {0x5C});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getBC(), 0xAABB);
    EXPECT_EQ(cpu.getDE(), 0xCCEE);
    EXPECT_EQ(cpu.getHL(), 0xEE00);
    EXPECT_EQ(cpu.getA(), 0x00);
    EXPECT_EQ(cpu.getFlags(), 0x02);
    EXPECT_EQ(cpu.getCyc(), 25);

    // Test MOV E, L (0x5D)
    cpu.setL(0xFF);
    loadAndRun(initial_pc, {0x5D});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getBC(), 0xAABB);
    EXPECT_EQ(cpu.getDE(), 0xCCFF);
    EXPECT_EQ(cpu.getHL(), 0xEEFF);
    EXPECT_EQ(cpu.getA(), 0x00);
    EXPECT_EQ(cpu.getFlags(), 0x02);
    EXPECT_EQ(cpu.getCyc(), 30);

    // Test MOV E, M (0x5E)
    cpu.setHL(0x2000);
    hal.write_byte(0x2000, 0x11); // Set memory at HL to 0x11
    loadAndRun(initial_pc, {0x5E});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getBC(), 0xAABB);
    EXPECT_EQ(cpu.getDE(), 0xCC11);
    EXPECT_EQ(cpu.getHL(), 0x2000);
    EXPECT_EQ(cpu.getA(), 0x00);
    EXPECT_EQ(cpu.getFlags(), 0x02);
    EXPECT_EQ(cpu.getCyc(), 37);

    // Test MOV E, A (0x5F)
    cpu.setA(0x22);
    loadAndRun(initial_pc, {0x5F});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getBC(), 0xAABB);
    EXPECT_EQ(cpu.getDE(), 0xCC22);
    EXPECT_EQ(cpu.getHL(), 0x2000);
    EXPECT_EQ(cpu.getA(), 0x22);
    EXPECT_EQ(cpu.getFlags(), 0x02);
    EXPECT_EQ(cpu.getCyc(), 42);

}

TEST_F(OpcodeTests, MOV_H){

    // Test MOV H, r (0x60-0x67)
    uint16_t initial_pc = cpu.getPC();
    
    // Test MOV H, B (0x60)
    cpu.setB(0xAA);
    loadAndRun(initial_pc, {0x60});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getBC(), 0xAA00);
    EXPECT_EQ(cpu.getDE(), 0x0000);
    EXPECT_EQ(cpu.getHL(), 0xAA00);
    EXPECT_EQ(cpu.getA(), 0x00);
    EXPECT_EQ(cpu.getFlags(), 0x02);
    EXPECT_EQ(cpu.getCyc(), 5);

    // Test MOV H, C (0x61)
    cpu.setC(0xBB);
    loadAndRun(initial_pc, {0x61}); 
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getBC(), 0xAABB);
    EXPECT_EQ(cpu.getDE(), 0x0000);
    EXPECT_EQ(cpu.getHL(), 0xBB00);
    EXPECT_EQ(cpu.getA(), 0x00);
    EXPECT_EQ(cpu.getFlags(), 0x02);
    EXPECT_EQ(cpu.getCyc(), 10);

    // Test MOV H, D (0x62)
    cpu.setD(0xCC);
    loadAndRun(initial_pc, {0x62});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getBC(), 0xAABB);
    EXPECT_EQ(cpu.getDE(), 0xCC00);
    EXPECT_EQ(cpu.getHL(), 0xCC00);
    EXPECT_EQ(cpu.getA(), 0x00);
    EXPECT_EQ(cpu.getFlags(), 0x02);
    EXPECT_EQ(cpu.getCyc(), 15);

    // Test MOV H, E (0x63)
    cpu.setE(0xDD);
    loadAndRun(initial_pc, {0x63});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getBC(), 0xAABB);
    EXPECT_EQ(cpu.getDE(), 0xCCDD);
    EXPECT_EQ(cpu.getHL(), 0xDD00);
    EXPECT_EQ(cpu.getA(), 0x00);
    EXPECT_EQ(cpu.getFlags(), 0x02);
    EXPECT_EQ(cpu.getCyc(), 20);

    // Test MOV H, H (0x64)
    cpu.setH(0xEE);
    loadAndRun(initial_pc, {0x64});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getBC(), 0xAABB);
    EXPECT_EQ(cpu.getDE(), 0xCCDD);
    EXPECT_EQ(cpu.getHL(), 0xEE00);
    EXPECT_EQ(cpu.getA(), 0x00);
    EXPECT_EQ(cpu.getFlags(), 0x02);
    EXPECT_EQ(cpu.getCyc(), 25);

    // Test MOV H, L (0x65)
    cpu.setL(0xFF);
    loadAndRun(initial_pc, {0x65});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getBC(), 0xAABB);
    EXPECT_EQ(cpu.getDE(), 0xCCDD);
    EXPECT_EQ(cpu.getHL(), 0xFFFF);
    EXPECT_EQ(cpu.getA(), 0x00);
    EXPECT_EQ(cpu.getFlags(), 0x02);
    EXPECT_EQ(cpu.getCyc(), 30);

    // Test MOV H, M (0x66)
    cpu.setHL(0x2000);
    hal.write_byte(0x2000, 0x11); // Set memory at HL to 0x11
    loadAndRun(initial_pc, {0x66});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getBC(), 0xAABB);
    EXPECT_EQ(cpu.getDE(), 0xCCDD);
    EXPECT_EQ(cpu.getHL(), 0x1100);
    EXPECT_EQ(hal.read_byte(0x2000), 0x11); // Memory at HL should remain unchanged
    EXPECT_EQ(cpu.getA(), 0x00);
    EXPECT_EQ(cpu.getFlags(), 0x02);
    EXPECT_EQ(cpu.getCyc(), 37);

    // Test MOV H, A (0x67)
    cpu.setA(0x22);
    loadAndRun(initial_pc, {0x67});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getBC(), 0xAABB);
    EXPECT_EQ(cpu.getDE(), 0xCCDD);
    EXPECT_EQ(cpu.getHL(), 0x2200);
    EXPECT_EQ(cpu.getA(), 0x22);
    EXPECT_EQ(cpu.getFlags(), 0x02);
    EXPECT_EQ(cpu.getCyc(), 42);

}

TEST_F(OpcodeTests, MOV_L){

    // Test MOV L, r (0x68-0x6F)
    uint16_t initial_pc = cpu.getPC();
    
    // Test MOV L, B (0x68)
    cpu.setB(0xAA);
    loadAndRun(initial_pc, {0x68});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getBC(), 0xAA00);
    EXPECT_EQ(cpu.getDE(), 0x0000);
    EXPECT_EQ(cpu.getHL(), 0x00AA);
    EXPECT_EQ(cpu.getA(), 0x00);
    EXPECT_EQ(cpu.getFlags(), 0x02);
    EXPECT_EQ(cpu.getCyc(), 5);

    // Test MOV L, C (0x69)
    cpu.setC(0xBB);
    loadAndRun(initial_pc, {0x69}); 
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getBC(), 0xAABB);
    EXPECT_EQ(cpu.getDE(), 0x0000);
    EXPECT_EQ(cpu.getHL(), 0x00BB);
    EXPECT_EQ(cpu.getA(), 0x00);
    EXPECT_EQ(cpu.getFlags(), 0x02);
    EXPECT_EQ(cpu.getCyc(), 10);

    // Test MOV L, D (0x6A)
    cpu.setD(0xCC);
    loadAndRun(initial_pc, {0x6A});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getBC(), 0xAABB);
    EXPECT_EQ(cpu.getDE(), 0xCC00);
    EXPECT_EQ(cpu.getHL(), 0x00CC);
    EXPECT_EQ(cpu.getA(), 0x00);
    EXPECT_EQ(cpu.getFlags(), 0x02);
    EXPECT_EQ(cpu.getCyc(), 15);

    // Test MOV L, E (0x6B)
    cpu.setE(0xDD);
    loadAndRun(initial_pc, {0x6B});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getBC(), 0xAABB);
    EXPECT_EQ(cpu.getDE(), 0xCCDD);
    EXPECT_EQ(cpu.getHL(), 0x00DD);
    EXPECT_EQ(cpu.getA(), 0x00);
    EXPECT_EQ(cpu.getFlags(), 0x02);
    EXPECT_EQ(cpu.getCyc(), 20);

    // Test MOV L, H (0x6C)
    cpu.setH(0xEE);
    loadAndRun(initial_pc, {0x6C});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getBC(), 0xAABB);
    EXPECT_EQ(cpu.getDE(), 0xCCDD);
    EXPECT_EQ(cpu.getHL(), 0xEEEE);
    EXPECT_EQ(cpu.getA(), 0x00);
    EXPECT_EQ(cpu.getFlags(), 0x02);
    EXPECT_EQ(cpu.getCyc(), 25);

    // Test MOV L, L (0x6D)
    cpu.setL(0xFF);
    loadAndRun(initial_pc, {0x6D});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getBC(), 0xAABB);
    EXPECT_EQ(cpu.getDE(), 0xCCDD);
    EXPECT_EQ(cpu.getHL(), 0xEEFF);
    EXPECT_EQ(cpu.getA(), 0x00);
    EXPECT_EQ(cpu.getFlags(), 0x02);
    EXPECT_EQ(cpu.getCyc(), 30);

    // Test MOV L, M (0x6E)
    cpu.setHL(0x2000);
    hal.write_byte(0x2000, 0x11); // Set memory at HL to 0x11
    loadAndRun(initial_pc, {0x6E});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getBC(), 0xAABB);
    EXPECT_EQ(cpu.getDE(), 0xCCDD);
    EXPECT_EQ(cpu.getHL(), 0x2011);
    EXPECT_EQ(hal.read_byte(0x2000), 0x11); // Memory at HL should remain unchanged
    EXPECT_EQ(cpu.getA(), 0x00);
    EXPECT_EQ(cpu.getFlags(), 0x02);
    EXPECT_EQ(cpu.getCyc(), 37);

    // Test MOV L, A (0x6F)
    cpu.setA(0x22);
    loadAndRun(initial_pc, {0x6F});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getBC(), 0xAABB);
    EXPECT_EQ(cpu.getDE(), 0xCCDD);
    EXPECT_EQ(cpu.getHL(), 0x2022);
    EXPECT_EQ(cpu.getA(), 0x22);
    EXPECT_EQ(cpu.getFlags(), 0x02);
    EXPECT_EQ(cpu.getCyc(), 42);

}

TEST_F(OpcodeTests, MOV_M){

    // Test MOV M, r (0x70-0x77)
    uint16_t initial_pc = cpu.getPC();
    cpu.setHL(0x2000); // Set HL to a specific memory location

    // Test MOV M, B (0x70)
    cpu.setB(0xAA);
    loadAndRun(initial_pc, {0x70});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getBC(), 0xAA00);
    EXPECT_EQ(cpu.getDE(), 0x0000);
    EXPECT_EQ(cpu.getHL(), 0x2000);
    EXPECT_EQ(hal.read_byte(0x2000), 0xAA);
    EXPECT_EQ(cpu.getA(), 0x00);
    EXPECT_EQ(cpu.getFlags(), 0x02);
    EXPECT_EQ(cpu.getCyc(), 7);

    // Test MOV M, C (0x71)
    cpu.setC(0xBB);
    loadAndRun(initial_pc, {0x71}); 
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getBC(), 0xAABB);
    EXPECT_EQ(cpu.getDE(), 0x0000);
    EXPECT_EQ(cpu.getHL(), 0x2000);
    EXPECT_EQ(hal.read_byte(0x2000), 0xBB);
    EXPECT_EQ(cpu.getA(), 0x00);
    EXPECT_EQ(cpu.getFlags(), 0x02);
    EXPECT_EQ(cpu.getCyc(), 14);

    // Test MOV M, D (0x72)
    cpu.setD(0xCC);
    loadAndRun(initial_pc, {0x72});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getBC(), 0xAABB);
    EXPECT_EQ(cpu.getDE(), 0xCC00);
    EXPECT_EQ(cpu.getHL(), 0x2000);
    EXPECT_EQ(hal.read_byte(0x2000), 0xCC);
    EXPECT_EQ(cpu.getA(), 0x00);
    EXPECT_EQ(cpu.getFlags(), 0x02);
    EXPECT_EQ(cpu.getCyc(), 21);

    // Test MOV M, E (0x73)
    cpu.setE(0xDD);
    loadAndRun(initial_pc, {0x73});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getBC(), 0xAABB);
    EXPECT_EQ(cpu.getDE(), 0xCCDD);
    EXPECT_EQ(cpu.getHL(), 0x2000);
    EXPECT_EQ(hal.read_byte(0x2000), 0xDD);
    EXPECT_EQ(cpu.getA(), 0x00);
    EXPECT_EQ(cpu.getFlags(), 0x02);
    EXPECT_EQ(cpu.getCyc(), 28);

    // Test MOV M, H (0x74)
    loadAndRun(initial_pc, {0x74});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getBC(), 0xAABB);
    EXPECT_EQ(cpu.getDE(), 0xCCDD);
    EXPECT_EQ(cpu.getHL(), 0x2000);
    EXPECT_EQ(hal.read_byte(0x2000), 0x20);
    EXPECT_EQ(cpu.getA(), 0x00);
    EXPECT_EQ(cpu.getFlags(), 0x02);
    EXPECT_EQ(cpu.getCyc(), 35);

    // Test MOV M, L (0x75)
    cpu.setL(0x01);
    loadAndRun(initial_pc, {0x75});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getBC(), 0xAABB);
    EXPECT_EQ(cpu.getDE(), 0xCCDD);
    EXPECT_EQ(cpu.getHL(), 0x2001);
    EXPECT_EQ(hal.read_byte(0x2001), 0x01);
    EXPECT_EQ(cpu.getA(), 0x00);
    EXPECT_EQ(cpu.getFlags(), 0x02);
    EXPECT_EQ(cpu.getCyc(), 42);

    // Test MOV M, A (0x77)
    cpu.setA(0x22);
    loadAndRun(initial_pc, {0x77});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getBC(), 0xAABB);
    EXPECT_EQ(cpu.getDE(), 0xCCDD);
    EXPECT_EQ(cpu.getHL(), 0x2001);
    EXPECT_EQ(hal.read_byte(0x2001), 0x22);
    EXPECT_EQ(cpu.getA(), 0x22);
    EXPECT_EQ(cpu.getFlags(), 0x02);
    EXPECT_EQ(cpu.getCyc(), 49);

}
