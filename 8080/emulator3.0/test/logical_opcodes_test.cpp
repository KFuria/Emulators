#include "test_fixture.h"

TEST_F(OpcodeTests, RLC_Carry0) {

    // Test RLC (0x07)
    uint16_t initial_pc = cpu.getPC();
    cpu.setA(0b01010100);   // A = 0x54
    cpu.setFlags(cpu.getFlags() | FLAG_CARRY); // Carry = 1

    loadAndRun(initial_pc, {0x07});

    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getA(), 0b10101000); // A = 0xA8
    EXPECT_FALSE(cpu.getFlags() & FLAG_CARRY); // Bit 7 (0) went to Carry
    EXPECT_FALSE(cpu.getFlags() & FLAG_SIGN);
    EXPECT_FALSE(cpu.getFlags() & FLAG_ZERO);
    EXPECT_FALSE(cpu.getFlags() & FLAG_AUX_CARRY);
    EXPECT_FALSE(cpu.getFlags() & FLAG_PARITY);
    EXPECT_EQ(cpu.getCyc(), 4);

}

TEST_F(OpcodeTests, RLC_Carry1) {

    // Test RLC (0x07)
    uint16_t initial_pc = cpu.getPC();
    cpu.setA(0b10101010); // A = 0xAA (Bit 7 is 1)
    cpu.setFlags(cpu.getFlags() & ~FLAG_CARRY);   // Carry = 0

    loadAndRun(initial_pc, {0x07}); // RLC

    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getA(), 0b01010101); // A = 0x55
    EXPECT_TRUE(cpu.getFlags() & FLAG_CARRY); // Bit 7 (1) went to Carry
    EXPECT_FALSE(cpu.getFlags() & FLAG_SIGN);
    EXPECT_FALSE(cpu.getFlags() & FLAG_ZERO);
    EXPECT_FALSE(cpu.getFlags() & FLAG_AUX_CARRY);
    EXPECT_FALSE(cpu.getFlags() & FLAG_PARITY);
    EXPECT_EQ(cpu.getCyc(), 4);

}

TEST_F(OpcodeTests, RRC_Carry0) {

    // Test RRC (0x0F)
    uint16_t initial_pc = cpu.getPC();
    cpu.setA(0b10101000); // A = 0xA8
    cpu.setFlags(cpu.getFlags() | FLAG_CARRY); // Carry = 1

    loadAndRun(initial_pc, {0x0F});

    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getA(), 0b01010100); // A should be 0x54
    EXPECT_FALSE(cpu.getFlags() & FLAG_CARRY); // Bit 0 (0) went to Carry
    EXPECT_FALSE(cpu.getFlags() & FLAG_SIGN);
    EXPECT_FALSE(cpu.getFlags() & FLAG_ZERO);
    EXPECT_FALSE(cpu.getFlags() & FLAG_AUX_CARRY);
    EXPECT_FALSE(cpu.getFlags() & FLAG_PARITY);
    EXPECT_EQ(cpu.getCyc(), 4);

}

TEST_F(OpcodeTests, RRC_Carry1) {

    // Test RRC (0x0F)
    uint16_t initial_pc = cpu.getPC();
    cpu.setA(0b00000101); // A = 0x05
    cpu.setFlags(cpu.getFlags() & ~FLAG_CARRY);   // Carry = 0

    loadAndRun(initial_pc, {0x0F});

    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getA(), 0b10000010); // A = 0x82
    EXPECT_TRUE(cpu.getFlags() & FLAG_CARRY); // Bit 0 (1) went to Carry
    EXPECT_FALSE(cpu.getFlags() & FLAG_SIGN);
    EXPECT_FALSE(cpu.getFlags() & FLAG_ZERO);
    EXPECT_FALSE(cpu.getFlags() & FLAG_AUX_CARRY);
    EXPECT_FALSE(cpu.getFlags() & FLAG_PARITY);
    EXPECT_EQ(cpu.getCyc(), 4);

}

TEST_F(OpcodeTests, RAL_Carry0Bit7Is0) {

    // Test RAL (0x17)
    uint16_t initial_pc = cpu.getPC();
    cpu.setA(0b01010100); // A = 0x54 (Bit 7 is 0)
    cpu.setFlags(cpu.getFlags() & ~FLAG_CARRY);   // Carry is 0

    loadAndRun(initial_pc, {0x17}); // RAL

    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getA(), 0b10101000); // A should be 0xA8
    EXPECT_FALSE(cpu.getFlags() & FLAG_CARRY); // Old A7 (0) went to Carry
    EXPECT_EQ(cpu.getCyc(), 4);
}

TEST_F(OpcodeTests, RAL_Carry0Bit7Is1) {

    // Test RAL (0x17)
    uint16_t initial_pc = cpu.getPC();
    cpu.setA(0b10101010); // A = 0xAA (Bit 7 is 1)
    cpu.setFlags(cpu.getFlags() & ~FLAG_CARRY);   // Carry is 0

    loadAndRun(initial_pc, {0x17}); // RAL

    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getA(), 0b01010100); // A should be 0x55 (Old Carry 0 goes to A0)
    EXPECT_TRUE(cpu.getFlags() & FLAG_CARRY); // Old A7 (1) goes to Carry
    EXPECT_EQ(cpu.getCyc(), 4);
}

TEST_F(OpcodeTests, RAL_Carry1Bit7Is0) {

    // Test RAL (0x17)
    uint16_t initial_pc = cpu.getPC();
    cpu.setA(0b01010100); // A = 0x54 (Bit 7 is 0)
    cpu.setFlags(cpu.getFlags() | FLAG_CARRY); // Carry is 1

    loadAndRun(initial_pc, {0x17}); // RAL

    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getA(), 0b10101001); // A should be 0xA9 (Old Carry 1 goes to A0)
    EXPECT_FALSE(cpu.getFlags() & FLAG_CARRY); // Old A7 (0) goes to Carry
    EXPECT_EQ(cpu.getCyc(), 4);
}

TEST_F(OpcodeTests, RAR_Carry0Bit0Is0) {

    // Test RAR (0x1F)
    uint16_t initial_pc = cpu.getPC();
    cpu.setA(0b01010100); // A = 0x54 (Bit 0 is 0)
    cpu.setFlags(cpu.getFlags() & ~FLAG_CARRY);   // Carry is 0

    loadAndRun(initial_pc, {0x1F}); // RAL

    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getA(), 0b00101010); // A should be 0x2A
    EXPECT_FALSE(cpu.getFlags() & FLAG_CARRY); // Old A0 (0) went to Carry
    EXPECT_EQ(cpu.getCyc(), 4);
}

TEST_F(OpcodeTests, RAR_Carry0Bit0Is1) {

    // Test RAR (0x1F)
    uint16_t initial_pc = cpu.getPC();
    cpu.setA(0b01010101); // A = 0xAA (Bit 0 is 1)
    cpu.setFlags(cpu.getFlags() & ~FLAG_CARRY);   // Carry is 0

    loadAndRun(initial_pc, {0x1F}); // RAL

    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getA(), 0b00101010); // A should be 0x2A (Old Carry 0 goes to A0)
    EXPECT_TRUE(cpu.getFlags() & FLAG_CARRY); // Old A0 (1) goes to Carry
    EXPECT_EQ(cpu.getCyc(), 4);
}

TEST_F(OpcodeTests, RAR_Carry1Bit0Is0) {

    // Test RAR (0x1F)
    uint16_t initial_pc = cpu.getPC();
    cpu.setA(0b01010100); // A = 0x54 (Bit 7 is 0)
    cpu.setFlags(cpu.getFlags() | FLAG_CARRY); // Carry is 1

    loadAndRun(initial_pc, {0x1F}); // RAL

    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getA(), 0b10101010); // A should be 0xAA (Old Carry 1 goes to A7)
    EXPECT_FALSE(cpu.getFlags() & FLAG_CARRY); // Old A0 (0) goes to Carry
    EXPECT_EQ(cpu.getCyc(), 4);
}

TEST_F(OpcodeTests, CMA) {

    // Test CMA (0x2F)
    uint16_t initial_pc = cpu.getPC();
    cpu.setA(0b10101010); // A = 0xAA

    loadAndRun(initial_pc, {0x2F}); // CMA

    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getA(), 0b01010101); // A should be 0x55 (bitwise NOT)
    EXPECT_FALSE(cpu.getFlags() & FLAG_CARRY);
    EXPECT_FALSE(cpu.getFlags() & FLAG_SIGN);
    EXPECT_FALSE(cpu.getFlags() & FLAG_ZERO);
    EXPECT_FALSE(cpu.getFlags() & FLAG_AUX_CARRY);
    EXPECT_FALSE(cpu.getFlags() & FLAG_PARITY);
    EXPECT_EQ(cpu.getCyc(), 4);

}

TEST_F(OpcodeTests, STC) {

    // Test STC (0x37)
    uint16_t initial_pc = cpu.getPC();
    cpu.setFlags(cpu.getFlags() & ~FLAG_CARRY); // Clear Carry

    loadAndRun(initial_pc, {0x37}); // STC

    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_TRUE(cpu.getFlags() & FLAG_CARRY); // Carry should be set
    EXPECT_EQ(cpu.getCyc(), 4);

}

TEST_F(OpcodeTests, CMC_setCarry) {

    // Test CMC (0x3F)
    uint16_t initial_pc = cpu.getPC();
    cpu.setFlags(cpu.getFlags() & ~FLAG_CARRY); // Clear Carry

    loadAndRun(initial_pc, {0x3F}); // CMC

    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_TRUE(cpu.getFlags() & FLAG_CARRY); // Carry should be set
    EXPECT_EQ(cpu.getCyc(), 4);

}

TEST_F(OpcodeTests, CMC_clearCarry) {

    // Test CMC (0x3F)
    uint16_t initial_pc = cpu.getPC();
    cpu.setFlags(cpu.getFlags() | FLAG_CARRY); // Set Carry

    loadAndRun(initial_pc, {0x3F}); // CMC

    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_FALSE(cpu.getFlags() & FLAG_CARRY); // Carry should be cleared
    EXPECT_EQ(cpu.getCyc(), 4);

}

TEST_F(OpcodeTests, ANA_B){
    
    // Test ANA B (0xA0)
    uint16_t initial_pc = cpu.getPC();
    cpu.setA(0xFD);
    cpu.setB(0x0F);
    cpu.setFlags(0x02); // Set flags
    loadAndRun(initial_pc, {0xA0});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getA(), 0x0D);        // A = 0xFD && 0x0F = 0x0D
    EXPECT_EQ(cpu.getBC(), 0x0F00);
    EXPECT_EQ(cpu.getDE(), 0x0000);
    EXPECT_EQ(cpu.getHL(), 0x0000);
    
    // Flags: Z=0, S=0, P=0, AC=1, C=0
    EXPECT_FALSE(cpu.getFlags() & FLAG_ZERO);
    EXPECT_FALSE(cpu.getFlags() & FLAG_SIGN);
    EXPECT_FALSE(cpu.getFlags() & FLAG_PARITY);
    EXPECT_TRUE(cpu.getFlags() & FLAG_AUX_CARRY);
    EXPECT_FALSE(cpu.getFlags() & FLAG_CARRY);

    EXPECT_EQ(cpu.getCyc(), 4);

}

TEST_F(OpcodeTests, ANA_C_ClearCarry){
    
    // Test ANA C (0xA1)
    uint16_t initial_pc = cpu.getPC();
    cpu.setA(0x12);
    cpu.setC(0xF0);
    cpu.setFlags(0x02 | FLAG_CARRY); // Set flags
    loadAndRun(initial_pc, {0xA1});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getA(), 0x10);        // A = 0x12 && 0xF0 = 0x10
    EXPECT_EQ(cpu.getBC(), 0x00F0);
    EXPECT_EQ(cpu.getDE(), 0x0000);
    EXPECT_EQ(cpu.getHL(), 0x0000);
    
    // Flags: Z=0, S=0, P=0, AC=0, C=0
    EXPECT_FALSE(cpu.getFlags() & FLAG_ZERO);
    EXPECT_FALSE(cpu.getFlags() & FLAG_SIGN);
    EXPECT_FALSE(cpu.getFlags() & FLAG_PARITY);
    EXPECT_FALSE(cpu.getFlags() & FLAG_AUX_CARRY);
    EXPECT_FALSE(cpu.getFlags() & FLAG_CARRY);

    EXPECT_EQ(cpu.getCyc(), 4);

}

TEST_F(OpcodeTests, ANA_D_ZerroFlag){
    
    // Test ANA D (0xA2)
    uint16_t initial_pc = cpu.getPC();
    cpu.setA(0xAA);
    cpu.setD(0x55);
    cpu.setFlags(0x02); // Set flags
    loadAndRun(initial_pc, {0xA2});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getA(), 0x00);        // A = 0xAA && 0x55 = 0x00
    EXPECT_EQ(cpu.getBC(), 0x0000);
    EXPECT_EQ(cpu.getDE(), 0x5500);
    EXPECT_EQ(cpu.getHL(), 0x0000);
    
    // Flags: Z=1, S=0, P=1, AC=0, C=0
    EXPECT_TRUE(cpu.getFlags() & FLAG_ZERO);
    EXPECT_FALSE(cpu.getFlags() & FLAG_SIGN);
    EXPECT_TRUE(cpu.getFlags() & FLAG_PARITY);
    EXPECT_FALSE(cpu.getFlags() & FLAG_AUX_CARRY);
    EXPECT_FALSE(cpu.getFlags() & FLAG_CARRY);

    EXPECT_EQ(cpu.getCyc(), 4);

}

TEST_F(OpcodeTests, ANA_E_SignFlag){
    
    // Test ANA E (0xA3)
    uint16_t initial_pc = cpu.getPC();
    cpu.setA(0xF0);
    cpu.setE(0x80);
    cpu.setFlags(0x02); // Set flags
    loadAndRun(initial_pc, {0xA3});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getA(), 0x80);        // A = 0xF0 && 0x80 = 0x80
    EXPECT_EQ(cpu.getBC(), 0x0000);
    EXPECT_EQ(cpu.getDE(), 0x0080);
    EXPECT_EQ(cpu.getHL(), 0x0000);
    
    // Flags: Z=0, S=1, P=0, AC=0, C=0
    EXPECT_FALSE(cpu.getFlags() & FLAG_ZERO);
    EXPECT_TRUE(cpu.getFlags() & FLAG_SIGN);
    EXPECT_FALSE(cpu.getFlags() & FLAG_PARITY);
    EXPECT_FALSE(cpu.getFlags() & FLAG_AUX_CARRY);
    EXPECT_FALSE(cpu.getFlags() & FLAG_CARRY);

    EXPECT_EQ(cpu.getCyc(), 4);

}

TEST_F(OpcodeTests, ANA_H){
    
    // Test ANA H (0xA4)
    uint16_t initial_pc = cpu.getPC();
    cpu.setA(0x0F);
    cpu.setH(0x02);
    cpu.setFlags(0x02 | FLAG_AUX_CARRY | FLAG_CARRY | FLAG_PARITY | FLAG_SIGN | FLAG_ZERO); // Set flags
    loadAndRun(initial_pc, {0xA4});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getA(), 0x02);        // A = 0x0F && 0x02 = 0x02
    EXPECT_EQ(cpu.getBC(), 0x0000);
    EXPECT_EQ(cpu.getDE(), 0x0000);
    EXPECT_EQ(cpu.getHL(), 0x0200);
    
    // Flags: Z=0, S=0, P=0, AC=0, C=0
    EXPECT_FALSE(cpu.getFlags() & FLAG_ZERO);
    EXPECT_FALSE(cpu.getFlags() & FLAG_SIGN);
    EXPECT_FALSE(cpu.getFlags() & FLAG_PARITY);
    EXPECT_FALSE(cpu.getFlags() & FLAG_AUX_CARRY);
    EXPECT_FALSE(cpu.getFlags() & FLAG_CARRY);

    EXPECT_EQ(cpu.getCyc(), 4);

}

TEST_F(OpcodeTests, ANA_L){

    // Test ANA L (0xA5)
    uint16_t initial_pc = cpu.getPC();
    cpu.setA(0xFC);
    cpu.setL(0x0F);
    cpu.setFlags(0x02); // Clear flags
    loadAndRun(initial_pc, {0xA5});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getA(), 0x0C);        // A = 0xFC && 0x0F = 0x0C
    EXPECT_EQ(cpu.getBC(), 0x0000);
    EXPECT_EQ(cpu.getDE(), 0x0000);
    EXPECT_EQ(cpu.getHL(), 0x000F);
    
    // Flags: Z=0, S=0, P=1, AC=1, C=0
    EXPECT_FALSE(cpu.getFlags() & FLAG_ZERO);
    EXPECT_FALSE(cpu.getFlags() & FLAG_SIGN);
    EXPECT_TRUE(cpu.getFlags() & FLAG_PARITY);
    EXPECT_TRUE(cpu.getFlags() & FLAG_AUX_CARRY);
    EXPECT_FALSE(cpu.getFlags() & FLAG_CARRY);

    EXPECT_EQ(cpu.getCyc(), 4);

}

TEST_F(OpcodeTests, ANA_M){

    // Test ANA M (0xA6)
    uint16_t initial_pc = cpu.getPC();
    cpu.setHL(0x2000);
    hal.write_byte(0x2000, 0x20);
    cpu.setA(0x02);
    cpu.setFlags(0x02); // Clear flags
    loadAndRun(initial_pc, {0xA6});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getA(), 0x00);        // A = 0x20 && 0x02 = 0x00
    EXPECT_EQ(cpu.getBC(), 0x0000);
    EXPECT_EQ(cpu.getDE(), 0x0000);
    EXPECT_EQ(cpu.getHL(), 0x2000);
    
    // Flags: Z=1, S=0, P=1, AC=0, C=0
    EXPECT_TRUE(cpu.getFlags() & FLAG_ZERO);
    EXPECT_FALSE(cpu.getFlags() & FLAG_SIGN);
    EXPECT_TRUE(cpu.getFlags() & FLAG_PARITY);
    EXPECT_FALSE(cpu.getFlags() & FLAG_AUX_CARRY);
    EXPECT_FALSE(cpu.getFlags() & FLAG_CARRY);

    EXPECT_EQ(cpu.getCyc(), 7);

}

TEST_F(OpcodeTests, ANA_A){

    // Test ANA A (0xA7)
    uint16_t initial_pc = cpu.getPC();
    cpu.setA(0x11);
    cpu.setFlags(0x02); // Clear flags
    loadAndRun(initial_pc, {0xA7});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getA(), 0x11);        // A = 0x11 && 0x11 = 0x11
    EXPECT_EQ(cpu.getBC(), 0x0000);
    EXPECT_EQ(cpu.getDE(), 0x0000);
    EXPECT_EQ(cpu.getHL(), 0x0000);
    
    // Flags: Z=0, S=0, P=1, AC=0, C=0
    EXPECT_FALSE(cpu.getFlags() & FLAG_ZERO);
    EXPECT_FALSE(cpu.getFlags() & FLAG_SIGN);
    EXPECT_TRUE(cpu.getFlags() & FLAG_PARITY);
    EXPECT_FALSE(cpu.getFlags() & FLAG_AUX_CARRY);
    EXPECT_FALSE(cpu.getFlags() & FLAG_CARRY);

    EXPECT_EQ(cpu.getCyc(), 4);

}

TEST_F(OpcodeTests, XRA_B){
    
    // Test XRA B (0xA8)
    uint16_t initial_pc = cpu.getPC();
    cpu.setA(0xFD);
    cpu.setB(0x0F);
    cpu.setFlags(0x02); // Set flags
    loadAndRun(initial_pc, {0xA8});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getA(), 0xF2);        // A = 0xFD ^ 0x0F = 0xF2
    EXPECT_EQ(cpu.getBC(), 0x0F00);
    EXPECT_EQ(cpu.getDE(), 0x0000);
    EXPECT_EQ(cpu.getHL(), 0x0000);
    
    // Flags: Z=0, S=1, P=0, AC=0, C=0
    EXPECT_FALSE(cpu.getFlags() & FLAG_ZERO);
    EXPECT_TRUE(cpu.getFlags() & FLAG_SIGN);
    EXPECT_FALSE(cpu.getFlags() & FLAG_PARITY);
    EXPECT_FALSE(cpu.getFlags() & FLAG_AUX_CARRY);
    EXPECT_FALSE(cpu.getFlags() & FLAG_CARRY);

    EXPECT_EQ(cpu.getCyc(), 4);

}

TEST_F(OpcodeTests, XRA_C){
    
    // Test XRA C (0xA9)
    uint16_t initial_pc = cpu.getPC();
    cpu.setA(0x12);
    cpu.setC(0xF0);
    cpu.setFlags(0x02 | FLAG_CARRY); // Set flags
    loadAndRun(initial_pc, {0xA9});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getA(), 0xE2);        // A = 0x12 ^ 0xF0 = 0xE2
    EXPECT_EQ(cpu.getBC(), 0x00F0);
    EXPECT_EQ(cpu.getDE(), 0x0000);
    EXPECT_EQ(cpu.getHL(), 0x0000);
    
    // Flags: Z=0, S=1, P=1, AC=0, C=0
    EXPECT_FALSE(cpu.getFlags() & FLAG_ZERO);
    EXPECT_TRUE(cpu.getFlags() & FLAG_SIGN);
    EXPECT_TRUE(cpu.getFlags() & FLAG_PARITY);
    EXPECT_FALSE(cpu.getFlags() & FLAG_AUX_CARRY);
    EXPECT_FALSE(cpu.getFlags() & FLAG_CARRY);

    EXPECT_EQ(cpu.getCyc(), 4);

}

TEST_F(OpcodeTests, XRA_D){
    
    // Test XRA D (0xAA)
    uint16_t initial_pc = cpu.getPC();
    cpu.setA(0xAA);
    cpu.setD(0x55);
    cpu.setFlags(0x02); // Set flags
    loadAndRun(initial_pc, {0xAA});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getA(), 0xFF);        // A = 0xAA ^ 0x55 = 0xFF
    EXPECT_EQ(cpu.getBC(), 0x0000);
    EXPECT_EQ(cpu.getDE(), 0x5500);
    EXPECT_EQ(cpu.getHL(), 0x0000);
    
    // Flags: Z=0, S=1, P=1, AC=0, C=0
    EXPECT_FALSE(cpu.getFlags() & FLAG_ZERO);
    EXPECT_TRUE(cpu.getFlags() & FLAG_SIGN);
    EXPECT_TRUE(cpu.getFlags() & FLAG_PARITY);
    EXPECT_FALSE(cpu.getFlags() & FLAG_AUX_CARRY);
    EXPECT_FALSE(cpu.getFlags() & FLAG_CARRY);

    EXPECT_EQ(cpu.getCyc(), 4);

}

TEST_F(OpcodeTests, XRA_E){
    
    // Test XRA E (0xAB)
    uint16_t initial_pc = cpu.getPC();
    cpu.setA(0xF0);
    cpu.setE(0x80);
    cpu.setFlags(0x02); // Set flags
    loadAndRun(initial_pc, {0xAB});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getA(), 0x70);        // A = 0xF0 ^ 0x80 = 0x70
    EXPECT_EQ(cpu.getBC(), 0x0000);
    EXPECT_EQ(cpu.getDE(), 0x0080);
    EXPECT_EQ(cpu.getHL(), 0x0000);
    
    // Flags: Z=0, S=0, P=0, AC=0, C=0
    EXPECT_FALSE(cpu.getFlags() & FLAG_ZERO);
    EXPECT_FALSE(cpu.getFlags() & FLAG_SIGN);
    EXPECT_FALSE(cpu.getFlags() & FLAG_PARITY);
    EXPECT_FALSE(cpu.getFlags() & FLAG_AUX_CARRY);
    EXPECT_FALSE(cpu.getFlags() & FLAG_CARRY);

    EXPECT_EQ(cpu.getCyc(), 4);

}

TEST_F(OpcodeTests, XRA_H){
    
    // Test XRA H (0xAC)
    uint16_t initial_pc = cpu.getPC();
    cpu.setA(0x0F);
    cpu.setH(0x02);
    cpu.setFlags(0x02 | FLAG_AUX_CARRY | FLAG_CARRY | FLAG_PARITY | FLAG_SIGN | FLAG_ZERO); // Set flags
    loadAndRun(initial_pc, {0xAC});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getA(), 0x0D);        // A = 0x0F && 0x02 = 0x0D
    EXPECT_EQ(cpu.getBC(), 0x0000);
    EXPECT_EQ(cpu.getDE(), 0x0000);
    EXPECT_EQ(cpu.getHL(), 0x0200);
    
    // Flags: Z=0, S=0, P=0, AC=0, C=0
    EXPECT_FALSE(cpu.getFlags() & FLAG_ZERO);
    EXPECT_FALSE(cpu.getFlags() & FLAG_SIGN);
    EXPECT_FALSE(cpu.getFlags() & FLAG_PARITY);
    EXPECT_FALSE(cpu.getFlags() & FLAG_AUX_CARRY);
    EXPECT_FALSE(cpu.getFlags() & FLAG_CARRY);

    EXPECT_EQ(cpu.getCyc(), 4);

}

TEST_F(OpcodeTests, XRA_L){

    // Test XRA L (0xAD)
    uint16_t initial_pc = cpu.getPC();
    cpu.setA(0xFC);
    cpu.setL(0x0F);
    cpu.setFlags(0x02); // Clear flags
    loadAndRun(initial_pc, {0xAD});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getA(), 0xF3);        // A = 0xFC ^ 0x0F = 0xF3
    EXPECT_EQ(cpu.getBC(), 0x0000);
    EXPECT_EQ(cpu.getDE(), 0x0000);
    EXPECT_EQ(cpu.getHL(), 0x000F);
    
    // Flags: Z=0, S=1, P=1, AC=0, C=0
    EXPECT_FALSE(cpu.getFlags() & FLAG_ZERO);
    EXPECT_TRUE(cpu.getFlags() & FLAG_SIGN);
    EXPECT_TRUE(cpu.getFlags() & FLAG_PARITY);
    EXPECT_FALSE(cpu.getFlags() & FLAG_AUX_CARRY);
    EXPECT_FALSE(cpu.getFlags() & FLAG_CARRY);

    EXPECT_EQ(cpu.getCyc(), 4);

}

TEST_F(OpcodeTests, XRA_M){

    // Test XRA M (0xAE)
    uint16_t initial_pc = cpu.getPC();
    cpu.setHL(0x2000);
    hal.write_byte(0x2000, 0x20);
    cpu.setA(0x02);
    cpu.setFlags(0x02); // Clear flags
    loadAndRun(initial_pc, {0xAE});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getA(), 0x22);        // A = 0x20 ^ 0x02 = 0x22
    EXPECT_EQ(cpu.getBC(), 0x0000);
    EXPECT_EQ(cpu.getDE(), 0x0000);
    EXPECT_EQ(cpu.getHL(), 0x2000);
    
    // Flags: Z=0, S=0, P=1, AC=0, C=0
    EXPECT_FALSE(cpu.getFlags() & FLAG_ZERO);
    EXPECT_FALSE(cpu.getFlags() & FLAG_SIGN);
    EXPECT_TRUE(cpu.getFlags() & FLAG_PARITY);
    EXPECT_FALSE(cpu.getFlags() & FLAG_AUX_CARRY);
    EXPECT_FALSE(cpu.getFlags() & FLAG_CARRY);

    EXPECT_EQ(cpu.getCyc(), 7);

}

TEST_F(OpcodeTests, XRA_A){

    // Test XRA A (0xAF)
    uint16_t initial_pc = cpu.getPC();
    cpu.setA(0x11);
    cpu.setFlags(0x02); // Clear flags
    loadAndRun(initial_pc, {0xAF});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getA(), 0x00);        // A = 0x11 ^ 0x11 = 0x00
    EXPECT_EQ(cpu.getBC(), 0x0000);
    EXPECT_EQ(cpu.getDE(), 0x0000);
    EXPECT_EQ(cpu.getHL(), 0x0000);
    
    // Flags: Z=1, S=0, P=1, AC=0, C=0
    EXPECT_TRUE(cpu.getFlags() & FLAG_ZERO);
    EXPECT_FALSE(cpu.getFlags() & FLAG_SIGN);
    EXPECT_TRUE(cpu.getFlags() & FLAG_PARITY);
    EXPECT_FALSE(cpu.getFlags() & FLAG_AUX_CARRY);
    EXPECT_FALSE(cpu.getFlags() & FLAG_CARRY);

    EXPECT_EQ(cpu.getCyc(), 4);

}

