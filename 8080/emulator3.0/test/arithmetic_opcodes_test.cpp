#include "test_fixture.h"

TEST_F(OpcodeTests, INX_B){

    // Test INX B (0x03)
    uint16_t initial_pc = cpu.getPC();

    loadAndRun(initial_pc, {0x03});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getBC(), 0x0001);
    EXPECT_EQ(cpu.getDE(), 0x0000);
    EXPECT_EQ(cpu.getHL(), 0x0000);
    EXPECT_EQ(cpu.getA(), 0x00);
    EXPECT_EQ(cpu.getFlags(), 0x02);
    EXPECT_EQ(cpu.getCyc(), 5);

}

TEST_F(OpcodeTests, INX_D){

    // Test INX D (0x13)
    uint16_t initial_pc = cpu.getPC();

    loadAndRun(initial_pc, {0x13});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getBC(), 0x0000);
    EXPECT_EQ(cpu.getDE(), 0x0001);
    EXPECT_EQ(cpu.getHL(), 0x0000);
    EXPECT_EQ(cpu.getA(), 0x00);
    EXPECT_EQ(cpu.getFlags(), 0x02);
    EXPECT_EQ(cpu.getCyc(), 5);

}

TEST_F(OpcodeTests, INX_H){

    // Test INX H (0x23)
    uint16_t initial_pc = cpu.getPC();

    loadAndRun(initial_pc, {0x23});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getBC(), 0x0000);
    EXPECT_EQ(cpu.getDE(), 0x0000);
    EXPECT_EQ(cpu.getHL(), 0x0001);
    EXPECT_EQ(cpu.getA(), 0x00);
    EXPECT_EQ(cpu.getFlags(), 0x02);
    EXPECT_EQ(cpu.getCyc(), 5);

}

TEST_F(OpcodeTests, INX_SP){

    // Test INX SP (0x33)
    uint16_t initial_pc = cpu.getPC();

    loadAndRun(initial_pc, {0x33});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getSP(), 0xFF01);     // SP reset value is 0xFF00
    EXPECT_EQ(cpu.getBC(), 0x0000);
    EXPECT_EQ(cpu.getDE(), 0x0000);
    EXPECT_EQ(cpu.getHL(), 0x0000);
    EXPECT_EQ(cpu.getA(), 0x00);
    EXPECT_EQ(cpu.getFlags(), 0x02);
    EXPECT_EQ(cpu.getCyc(), 5);

}

TEST_F(OpcodeTests, DCX_B){

    // Test DCX B (0x0B)
    uint16_t initial_pc = cpu.getPC();

    loadAndRun(initial_pc, {0x0B});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getBC(), 0xFFFF);
    EXPECT_EQ(cpu.getDE(), 0x0000);
    EXPECT_EQ(cpu.getHL(), 0x0000);
    EXPECT_EQ(cpu.getA(), 0x00);
    EXPECT_EQ(cpu.getFlags(), 0x02);
    EXPECT_EQ(cpu.getCyc(), 5);

}

TEST_F(OpcodeTests, DCX_D){

    // Test DCX D (0x1B)
    uint16_t initial_pc = cpu.getPC();

    loadAndRun(initial_pc, {0x1B});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getBC(), 0x0000);
    EXPECT_EQ(cpu.getDE(), 0xFFFF);
    EXPECT_EQ(cpu.getHL(), 0x0000);
    EXPECT_EQ(cpu.getA(), 0x00);
    EXPECT_EQ(cpu.getFlags(), 0x02);
    EXPECT_EQ(cpu.getCyc(), 5);

}

TEST_F(OpcodeTests, DCX_H){

    // Test DCX H (0x2B)
    uint16_t initial_pc = cpu.getPC();

    loadAndRun(initial_pc, {0x2B});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getBC(), 0x0000);
    EXPECT_EQ(cpu.getDE(), 0x0000);
    EXPECT_EQ(cpu.getHL(), 0xFFFF);
    EXPECT_EQ(cpu.getA(), 0x00);
    EXPECT_EQ(cpu.getFlags(), 0x02);
    EXPECT_EQ(cpu.getCyc(), 5);

}

TEST_F(OpcodeTests, DCX_SP){

    // Test INX SP (0x33)
    uint16_t initial_pc = cpu.getPC();

    loadAndRun(initial_pc, {0x3B});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getSP(), 0xFEFF);     // SP reset value is 0xFF00
    EXPECT_EQ(cpu.getBC(), 0x0000);
    EXPECT_EQ(cpu.getDE(), 0x0000);
    EXPECT_EQ(cpu.getHL(), 0x0000);
    EXPECT_EQ(cpu.getA(), 0x00);
    EXPECT_EQ(cpu.getFlags(), 0x02);
    EXPECT_EQ(cpu.getCyc(), 5);

}

TEST_F(OpcodeTests, INR_B){

    // Test INR B (0x04)
    uint16_t initial_pc = cpu.getPC();

    loadAndRun(initial_pc, {0x04});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getBC(), 0x0100);     // B increments
    EXPECT_EQ(cpu.getDE(), 0x0000);
    EXPECT_EQ(cpu.getHL(), 0x0000);
    EXPECT_EQ(cpu.getA(), 0x00);
    EXPECT_EQ(cpu.getFlags(), 0x02); // Flags: Z=0, S=0, P=0, AC=0, C (unaffected)
    EXPECT_EQ(cpu.getCyc(), 5);

}

TEST_F(OpcodeTests, INR_C_ZeroFlag){

    // Test INR C (0x0C)
    uint16_t initial_pc = cpu.getPC();
    cpu.setC(0xFF);

    loadAndRun(initial_pc, {0x0C});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getBC(), 0x0000);     // C = 0x00 after incrementing
    EXPECT_EQ(cpu.getDE(), 0x0000);
    EXPECT_EQ(cpu.getHL(), 0x0000);
    EXPECT_EQ(cpu.getA(), 0x00);
    
    // Flags: Z=1, S=0, P=1, AC=1, C (unaffected)
    EXPECT_TRUE(cpu.getFlags() & FLAG_ZERO);
    EXPECT_FALSE(cpu.getFlags() & FLAG_SIGN);
    EXPECT_TRUE(cpu.getFlags() & FLAG_PARITY);
    EXPECT_TRUE(cpu.getFlags() & FLAG_AUX_CARRY);
    EXPECT_FALSE(cpu.getFlags() & FLAG_CARRY);

    EXPECT_EQ(cpu.getCyc(), 5);

}

TEST_F(OpcodeTests, INR_D_SignFlag){

    // Test INR D (0x14)
    uint16_t initial_pc = cpu.getPC();
    cpu.setD(0x82);

    loadAndRun(initial_pc, {0x14});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getBC(), 0x0000);       
    EXPECT_EQ(cpu.getDE(), 0x8300);     // D = 0x83 after incrementing
    EXPECT_EQ(cpu.getHL(), 0x0000);
    EXPECT_EQ(cpu.getA(), 0x00);
    
    // Flags: Z=0, S=1, P=0, AC=0, C (unaffected)
    EXPECT_FALSE(cpu.getFlags() & FLAG_ZERO);
    EXPECT_TRUE(cpu.getFlags() & FLAG_SIGN);
    EXPECT_FALSE(cpu.getFlags() & FLAG_PARITY);
    EXPECT_FALSE(cpu.getFlags() & FLAG_AUX_CARRY);
    EXPECT_FALSE(cpu.getFlags() & FLAG_CARRY);

    EXPECT_EQ(cpu.getCyc(), 5);

}

TEST_F(OpcodeTests, INR_E_ParityFlag){

    // Test INR E (0x1C)
    uint16_t initial_pc = cpu.getPC();
    cpu.setE(0x02);

    loadAndRun(initial_pc, {0x1C});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getBC(), 0x0000);       
    EXPECT_EQ(cpu.getDE(), 0x0003);     // E = 0x03 after incrementing
    EXPECT_EQ(cpu.getHL(), 0x0000);
    EXPECT_EQ(cpu.getA(), 0x00);
    
    // Flags: Z=0, S=0, P=1, AC=0, C (unaffected)
    EXPECT_FALSE(cpu.getFlags() & FLAG_ZERO);
    EXPECT_FALSE(cpu.getFlags() & FLAG_SIGN);
    EXPECT_TRUE(cpu.getFlags() & FLAG_PARITY);
    EXPECT_FALSE(cpu.getFlags() & FLAG_AUX_CARRY);
    EXPECT_FALSE(cpu.getFlags() & FLAG_CARRY);

    EXPECT_EQ(cpu.getCyc(), 5);

}

TEST_F(OpcodeTests, INR_H_AuxiliaryFlag){

    // Test INR H (0x24)
    uint16_t initial_pc = cpu.getPC();
    cpu.setH(0x0F);

    loadAndRun(initial_pc, {0x24});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getBC(), 0x0000);       
    EXPECT_EQ(cpu.getDE(), 0x0000);     
    EXPECT_EQ(cpu.getHL(), 0x1000);     // H = 0x10 after incrementing
    EXPECT_EQ(cpu.getA(), 0x00);
    
    // Flags: Z=0, S=0, P=0, AC=1, C (unaffected)
    EXPECT_FALSE(cpu.getFlags() & FLAG_ZERO);
    EXPECT_FALSE(cpu.getFlags() & FLAG_SIGN);
    EXPECT_FALSE(cpu.getFlags() & FLAG_PARITY);
    EXPECT_TRUE(cpu.getFlags() & FLAG_AUX_CARRY);
    EXPECT_FALSE(cpu.getFlags() & FLAG_CARRY);

    EXPECT_EQ(cpu.getCyc(), 5);

}

TEST_F(OpcodeTests, INR_L_CarryFlag){

    // Test INR D (0x2C)
    uint16_t initial_pc = cpu.getPC();
    cpu.setL(0x7E);
    cpu.setFlags(cpu.getFlags() | FLAG_CARRY);

    loadAndRun(initial_pc, {0x2C});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getBC(), 0x0000);       
    EXPECT_EQ(cpu.getDE(), 0x0000);     
    EXPECT_EQ(cpu.getHL(), 0x007F);     // L = 0x7F after incrementing
    EXPECT_EQ(cpu.getA(), 0x00);
    
    // Flags: Z=0, S=1, P=0, AC=0, C (unaffected)
    EXPECT_FALSE(cpu.getFlags() & FLAG_ZERO);
    EXPECT_FALSE(cpu.getFlags() & FLAG_SIGN);
    EXPECT_FALSE(cpu.getFlags() & FLAG_PARITY);
    EXPECT_FALSE(cpu.getFlags() & FLAG_AUX_CARRY);
    EXPECT_TRUE(cpu.getFlags() & FLAG_CARRY);

    EXPECT_EQ(cpu.getCyc(), 5);

}

TEST_F(OpcodeTests, INR_M){

    // Test INR D (0x2C)
    uint16_t initial_pc = cpu.getPC();
    uint16_t memory_addr = 0x2000;
    cpu.setHL(memory_addr); // HL points to 0x2000

    hal.write_byte(memory_addr, 0x7F);
    cpu.setFlags(cpu.getFlags() | FLAG_CARRY);

    loadAndRun(initial_pc, {0x34});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getBC(), 0x0000);       
    EXPECT_EQ(cpu.getDE(), 0x0000);     
    EXPECT_EQ(cpu.getHL(), 0x2000);     // HL should not change
    EXPECT_EQ(cpu.getA(), 0x00);

    EXPECT_EQ(hal.read_byte(memory_addr), 0x80);

    // Flags: Z=0, S=1, P=0, AC=1, C (unaffected)
    EXPECT_FALSE(cpu.getFlags() & FLAG_ZERO);
    EXPECT_TRUE(cpu.getFlags() & FLAG_SIGN);
    EXPECT_FALSE(cpu.getFlags() & FLAG_PARITY);
    EXPECT_TRUE(cpu.getFlags() & FLAG_AUX_CARRY);
    EXPECT_TRUE(cpu.getFlags() & FLAG_CARRY);

    EXPECT_EQ(cpu.getCyc(), 10);

}

TEST_F(OpcodeTests, INR_A){

    // Test INR A (0x3C)
    uint16_t initial_pc = cpu.getPC();

    loadAndRun(initial_pc, {0x3C});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getBC(), 0x0000);     
    EXPECT_EQ(cpu.getDE(), 0x0000);
    EXPECT_EQ(cpu.getHL(), 0x0000);
    EXPECT_EQ(cpu.getA(), 0x01);        // A increments
    EXPECT_EQ(cpu.getFlags(), 0x02);    // Flags: Z=0, S=0, P=0, AC=0, C (unaffected)
    EXPECT_EQ(cpu.getCyc(), 5);

}

TEST_F(OpcodeTests, DCR_B){

    // Test DCR B (0x05)
    uint16_t initial_pc = cpu.getPC();
    cpu.setB(0x02);

    loadAndRun(initial_pc, {0x05});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getBC(), 0x0100);     // B decrements
    EXPECT_EQ(cpu.getDE(), 0x0000);
    EXPECT_EQ(cpu.getHL(), 0x0000);
    EXPECT_EQ(cpu.getA(), 0x00);
    EXPECT_EQ(cpu.getFlags(), 0x02); // Flags: Z=0, S=0, P=0, AC=0, C (unaffected)
    EXPECT_EQ(cpu.getCyc(), 5);

}

TEST_F(OpcodeTests, DCR_C_ZeroFlag){

    // Test DCR C (0x0D)
    uint16_t initial_pc = cpu.getPC();
    cpu.setC(0x01);

    loadAndRun(initial_pc, {0x0D});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getBC(), 0x0000);     // C = 0x00 after decrementing
    EXPECT_EQ(cpu.getDE(), 0x0000);
    EXPECT_EQ(cpu.getHL(), 0x0000);
    EXPECT_EQ(cpu.getA(), 0x00);
    
    // Flags: Z=1, S=0, P=1, AC=0, C (unaffected)
    EXPECT_TRUE(cpu.getFlags() & FLAG_ZERO);
    EXPECT_FALSE(cpu.getFlags() & FLAG_SIGN);
    EXPECT_TRUE(cpu.getFlags() & FLAG_PARITY);
    EXPECT_FALSE(cpu.getFlags() & FLAG_AUX_CARRY);
    EXPECT_FALSE(cpu.getFlags() & FLAG_CARRY);

    EXPECT_EQ(cpu.getCyc(), 5);

}

TEST_F(OpcodeTests, DCR_D_SignFlag){

    // Test DCR D (0x15)
    uint16_t initial_pc = cpu.getPC();
    cpu.setD(0x84);

    loadAndRun(initial_pc, {0x15});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getBC(), 0x0000);       
    EXPECT_EQ(cpu.getDE(), 0x8300);     // D = 0x83 after decrementing
    EXPECT_EQ(cpu.getHL(), 0x0000);
    EXPECT_EQ(cpu.getA(), 0x00);
    
    // Flags: Z=0, S=1, P=0, AC=0, C (unaffected)
    EXPECT_FALSE(cpu.getFlags() & FLAG_ZERO);
    EXPECT_TRUE(cpu.getFlags() & FLAG_SIGN);
    EXPECT_FALSE(cpu.getFlags() & FLAG_PARITY);
    EXPECT_FALSE(cpu.getFlags() & FLAG_AUX_CARRY);
    EXPECT_FALSE(cpu.getFlags() & FLAG_CARRY);

    EXPECT_EQ(cpu.getCyc(), 5);

}

TEST_F(OpcodeTests, DCR_E_ParityFlag){

    // Test DCR E (0x1D)
    uint16_t initial_pc = cpu.getPC();
    cpu.setE(0x04);

    loadAndRun(initial_pc, {0x1D});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getBC(), 0x0000);       
    EXPECT_EQ(cpu.getDE(), 0x0003);     // E = 0x03 after decrementing
    EXPECT_EQ(cpu.getHL(), 0x0000);
    EXPECT_EQ(cpu.getA(), 0x00);
    
    // Flags: Z=0, S=0, P=1, AC=0, C (unaffected)
    EXPECT_FALSE(cpu.getFlags() & FLAG_ZERO);
    EXPECT_FALSE(cpu.getFlags() & FLAG_SIGN);
    EXPECT_TRUE(cpu.getFlags() & FLAG_PARITY);
    EXPECT_FALSE(cpu.getFlags() & FLAG_AUX_CARRY);
    EXPECT_FALSE(cpu.getFlags() & FLAG_CARRY);

    EXPECT_EQ(cpu.getCyc(), 5);

}

TEST_F(OpcodeTests, DCR_H_AuxiliaryFlag){

    // Test DCR H (0x25)
    uint16_t initial_pc = cpu.getPC();
    cpu.setH(0x20);

    loadAndRun(initial_pc, {0x25});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getBC(), 0x0000);       
    EXPECT_EQ(cpu.getDE(), 0x0000);     
    EXPECT_EQ(cpu.getHL(), 0x1F00);     // H = 0x0F after decrementing
    EXPECT_EQ(cpu.getA(), 0x00);
    
    // Flags: Z=0, S=0, P=0, AC=1, C (unaffected)
    EXPECT_FALSE(cpu.getFlags() & FLAG_ZERO);
    EXPECT_FALSE(cpu.getFlags() & FLAG_SIGN);
    EXPECT_FALSE(cpu.getFlags() & FLAG_PARITY);
    EXPECT_TRUE(cpu.getFlags() & FLAG_AUX_CARRY);
    EXPECT_FALSE(cpu.getFlags() & FLAG_CARRY);

    EXPECT_EQ(cpu.getCyc(), 5);

}

TEST_F(OpcodeTests, DCR_L_CarryFlag){

    // Test DCR D (0x2D)
    uint16_t initial_pc = cpu.getPC();
    cpu.setL(0x7F);
    cpu.setFlags(cpu.getFlags() | FLAG_CARRY);

    loadAndRun(initial_pc, {0x2D});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getBC(), 0x0000);       
    EXPECT_EQ(cpu.getDE(), 0x0000);     
    EXPECT_EQ(cpu.getHL(), 0x007E);     // L = 0x7F after decrementing
    EXPECT_EQ(cpu.getA(), 0x00);
    
    // Flags: Z=0, S=0, P=1, AC=0, C=1 (unaffected)
    EXPECT_FALSE(cpu.getFlags() & FLAG_ZERO);
    EXPECT_FALSE(cpu.getFlags() & FLAG_SIGN);
    EXPECT_TRUE(cpu.getFlags() & FLAG_PARITY);
    EXPECT_FALSE(cpu.getFlags() & FLAG_AUX_CARRY);
    EXPECT_TRUE(cpu.getFlags() & FLAG_CARRY);

    EXPECT_EQ(cpu.getCyc(), 5);

}

TEST_F(OpcodeTests, DCR_M){

    // Test DCR D (0x2D)
    uint16_t initial_pc = cpu.getPC();
    uint16_t memory_addr = 0x2000;
    cpu.setHL(memory_addr); // HL points to 0x2000

    hal.write_byte(memory_addr, 0x80);
    cpu.setFlags(cpu.getFlags() | FLAG_CARRY);

    loadAndRun(initial_pc, {0x35});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getBC(), 0x0000);       
    EXPECT_EQ(cpu.getDE(), 0x0000);     
    EXPECT_EQ(cpu.getHL(), 0x2000);     // HL should not change
    EXPECT_EQ(cpu.getA(), 0x00);

    EXPECT_EQ(hal.read_byte(memory_addr), 0x7F);

    // Flags: Z=0, S=0, P=0, AC=1, C=1 (unaffected)
    EXPECT_FALSE(cpu.getFlags() & FLAG_ZERO);
    EXPECT_FALSE(cpu.getFlags() & FLAG_SIGN);
    EXPECT_FALSE(cpu.getFlags() & FLAG_PARITY);
    EXPECT_TRUE(cpu.getFlags() & FLAG_AUX_CARRY);
    EXPECT_TRUE(cpu.getFlags() & FLAG_CARRY);

    EXPECT_EQ(cpu.getCyc(), 10);

}

TEST_F(OpcodeTests, DCR_A){

    // Test DCR A (0x3D)
    uint16_t initial_pc = cpu.getPC();
    cpu.setA(0x02);

    loadAndRun(initial_pc, {0x3D});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getBC(), 0x0000);     
    EXPECT_EQ(cpu.getDE(), 0x0000);
    EXPECT_EQ(cpu.getHL(), 0x0000);
    EXPECT_EQ(cpu.getA(), 0x01);        // A decrements
    EXPECT_EQ(cpu.getFlags(), 0x02);    // Flags: Z=0, S=0, P=0, AC=0, C (unaffected)
    EXPECT_EQ(cpu.getCyc(), 5);

}

TEST_F(OpcodeTests, DAD_B){

    // Test DAD B (0x09)
    uint16_t initial_pc = cpu.getPC();
    cpu.setBC(0xFFFF);
    cpu.setHL(0x1235);

    loadAndRun(initial_pc, {0x09});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getBC(), 0xFFFF);     
    EXPECT_EQ(cpu.getDE(), 0x0000);
    EXPECT_EQ(cpu.getHL(), 0x1234);
    EXPECT_EQ(cpu.getA(), 0x00);
    
    // Flags: Z=0, S=0, P=0, AC=0, C=1
    EXPECT_FALSE(cpu.getFlags() & FLAG_ZERO);
    EXPECT_FALSE(cpu.getFlags() & FLAG_SIGN);
    EXPECT_FALSE(cpu.getFlags() & FLAG_PARITY);
    EXPECT_FALSE(cpu.getFlags() & FLAG_AUX_CARRY);
    EXPECT_TRUE(cpu.getFlags() & FLAG_CARRY);

    EXPECT_EQ(cpu.getCyc(), 10);

}

TEST_F(OpcodeTests, DAD_D){

    // Test DAD D (0x19)
    uint16_t initial_pc = cpu.getPC();
    cpu.setDE(0xFFFF);
    cpu.setHL(0x0001);

    loadAndRun(initial_pc, {0x19});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getBC(), 0x0000);     
    EXPECT_EQ(cpu.getDE(), 0xFFFF);
    EXPECT_EQ(cpu.getHL(), 0x0000);
    EXPECT_EQ(cpu.getA(), 0x00);
    
    // Flags: Z=0, S=0, P=0, AC=0, C=1
    EXPECT_FALSE(cpu.getFlags() & FLAG_ZERO);
    EXPECT_FALSE(cpu.getFlags() & FLAG_SIGN);
    EXPECT_FALSE(cpu.getFlags() & FLAG_PARITY);
    EXPECT_FALSE(cpu.getFlags() & FLAG_AUX_CARRY);
    EXPECT_TRUE(cpu.getFlags() & FLAG_CARRY);

    EXPECT_EQ(cpu.getCyc(), 10);

}

TEST_F(OpcodeTests, DAD_H){

    // Test DAD H (0x29)
    uint16_t initial_pc = cpu.getPC();
    cpu.setHL(0x1234);

    loadAndRun(initial_pc, {0x29});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getBC(), 0x0000);     
    EXPECT_EQ(cpu.getDE(), 0x0000);
    EXPECT_EQ(cpu.getHL(), 0x2468);
    EXPECT_EQ(cpu.getA(), 0x00);
    
    // Flags: Z=0, S=0, P=0, AC=0, C=0
    EXPECT_FALSE(cpu.getFlags() & FLAG_ZERO);
    EXPECT_FALSE(cpu.getFlags() & FLAG_SIGN);
    EXPECT_FALSE(cpu.getFlags() & FLAG_PARITY);
    EXPECT_FALSE(cpu.getFlags() & FLAG_AUX_CARRY);
    EXPECT_FALSE(cpu.getFlags() & FLAG_CARRY);

    EXPECT_EQ(cpu.getCyc(), 10);

}

TEST_F(OpcodeTests, DAD_SP){

    // Test DAD SP (0x39)
    uint16_t initial_pc = cpu.getPC();
    cpu.setSP(0x0001);
    cpu.setHL(0x0001);

    loadAndRun(initial_pc, {0x39});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getBC(), 0x0000);     
    EXPECT_EQ(cpu.getDE(), 0x0000);
    EXPECT_EQ(cpu.getHL(), 0x0002);
    EXPECT_EQ(cpu.getA(), 0x00);
    EXPECT_EQ(cpu.getSP(), 0x0001);

    // Flags: Z=0, S=0, P=0, AC=0, C=0
    EXPECT_FALSE(cpu.getFlags() & FLAG_ZERO);
    EXPECT_FALSE(cpu.getFlags() & FLAG_SIGN);
    EXPECT_FALSE(cpu.getFlags() & FLAG_PARITY);
    EXPECT_FALSE(cpu.getFlags() & FLAG_AUX_CARRY);
    EXPECT_FALSE(cpu.getFlags() & FLAG_CARRY);

    EXPECT_EQ(cpu.getCyc(), 10);

}

TEST_F(OpcodeTests, DAA_HighLowNibble){

    // Test DAA (0x27)
    uint16_t initial_pc = cpu.getPC();
    cpu.setA(0x9B);

    loadAndRun(initial_pc, {0x27});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    // Bits 0-3 are greater than 9, 
    // hence A += 0x06 which is 0xA1, AC is set
    // Bits 4-7 are greater than 9, 
    // hence A += 0x60 which is 0x01, C is set
    EXPECT_EQ(cpu.getA(), 0x01);
    
    // Flags: Z=0, S=0, P=0, AC=1, C=1
    EXPECT_FALSE(cpu.getFlags() & FLAG_ZERO);
    EXPECT_FALSE(cpu.getFlags() & FLAG_SIGN);
    EXPECT_FALSE(cpu.getFlags() & FLAG_PARITY);
    EXPECT_TRUE(cpu.getFlags() & FLAG_AUX_CARRY);
    EXPECT_TRUE(cpu.getFlags() & FLAG_CARRY);    

    EXPECT_EQ(cpu.getCyc(), 4);
}

TEST_F(OpcodeTests, DAA_validBCD){

    // Test DAA (0x27)
    uint16_t initial_pc = cpu.getPC();
    cpu.setA(0x32);

    loadAndRun(initial_pc, {0x27});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getA(), 0x32);    //0x32 is valid BCD hence no change
    
    // Flags: Z=0, S=0, P=0, AC=0, C=0
    EXPECT_FALSE(cpu.getFlags() & FLAG_ZERO);
    EXPECT_FALSE(cpu.getFlags() & FLAG_SIGN);
    EXPECT_FALSE(cpu.getFlags() & FLAG_PARITY);
    EXPECT_FALSE(cpu.getFlags() & FLAG_AUX_CARRY);
    EXPECT_FALSE(cpu.getFlags() & FLAG_CARRY);    

    EXPECT_EQ(cpu.getCyc(), 4);
}

TEST_F(OpcodeTests, DAA_LowNibble){

    // Test DAA (0x27)
    uint16_t initial_pc = cpu.getPC();
    cpu.setA(0x1A);

    loadAndRun(initial_pc, {0x27});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getA(), 0x20);    // 0x1A + 0x06 = 0x20 
    
    // Flags: Z=0, S=0, P=0, AC=1, C=0
    EXPECT_FALSE(cpu.getFlags() & FLAG_ZERO);
    EXPECT_FALSE(cpu.getFlags() & FLAG_SIGN);
    EXPECT_FALSE(cpu.getFlags() & FLAG_PARITY);
    EXPECT_TRUE(cpu.getFlags() & FLAG_AUX_CARRY);
    EXPECT_FALSE(cpu.getFlags() & FLAG_CARRY);    

    EXPECT_EQ(cpu.getCyc(), 4);
}

TEST_F(OpcodeTests, DAA_ACFlagSet){

    // Test DAA (0x27)
    uint16_t initial_pc = cpu.getPC();
    cpu.setA(0x12);
    cpu.setFlags(cpu.getFlags() | FLAG_AUX_CARRY);

    loadAndRun(initial_pc, {0x27});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getA(), 0x18);    // 0x12 + 0x06 = 0x18
    
    // Flags: Z=0, S=0, P=1, AC=1, C=0
    EXPECT_FALSE(cpu.getFlags() & FLAG_ZERO);
    EXPECT_FALSE(cpu.getFlags() & FLAG_SIGN);
    EXPECT_TRUE(cpu.getFlags() & FLAG_PARITY);
    EXPECT_TRUE(cpu.getFlags() & FLAG_AUX_CARRY);
    EXPECT_FALSE(cpu.getFlags() & FLAG_CARRY);    

    EXPECT_EQ(cpu.getCyc(), 4);
}

TEST_F(OpcodeTests, DAA_HighNibble){

    // Test DAA (0x27)
    uint16_t initial_pc = cpu.getPC();
    cpu.setA(0xA2);

    loadAndRun(initial_pc, {0x27});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getA(), 0x02);    // 0xA2 + 0x60 = 0x102 (wraps to 0x02), sets C
    
    // Flags: Z=0, S=0, P=0, AC=0, C=1
    EXPECT_FALSE(cpu.getFlags() & FLAG_ZERO);
    EXPECT_FALSE(cpu.getFlags() & FLAG_SIGN);
    EXPECT_FALSE(cpu.getFlags() & FLAG_PARITY);
    EXPECT_FALSE(cpu.getFlags() & FLAG_AUX_CARRY);
    EXPECT_TRUE(cpu.getFlags() & FLAG_CARRY);    

    EXPECT_EQ(cpu.getCyc(), 4);
}

TEST_F(OpcodeTests, DAA_CFlagSet){

    // Test DAA (0x27)
    uint16_t initial_pc = cpu.getPC();
    cpu.setA(0x12);
    cpu.setFlags(cpu.getFlags() | FLAG_CARRY);

    loadAndRun(initial_pc, {0x27});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getA(), 0x72);    // 0x12 + 0x60 = 0x72 (wraps to 0x02), sets C
    
    // Flags: Z=0, S=0, P=1, AC=0, C=1
    EXPECT_FALSE(cpu.getFlags() & FLAG_ZERO);
    EXPECT_FALSE(cpu.getFlags() & FLAG_SIGN);
    EXPECT_TRUE(cpu.getFlags() & FLAG_PARITY);
    EXPECT_FALSE(cpu.getFlags() & FLAG_AUX_CARRY);
    EXPECT_TRUE(cpu.getFlags() & FLAG_CARRY);    

    EXPECT_EQ(cpu.getCyc(), 4);
}

TEST_F(OpcodeTests, ADD_B_NoFlags){

    // Test ADD B (0x80)
    uint16_t initial_pc = cpu.getPC();
    cpu.setA(0x01);
    cpu.setB(0x01);
    cpu.setFlags(0x02); // Clear flags
    loadAndRun(initial_pc, {0x80});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getA(), 0x02);        // A = 0x01 + 0x01
    EXPECT_EQ(cpu.getBC(), 0x0100);
    EXPECT_EQ(cpu.getDE(), 0x0000);
    EXPECT_EQ(cpu.getHL(), 0x0000);
    EXPECT_EQ(cpu.getFlags(), 0x02);    // Flags: Z=0, S=0, P=0, AC=0, C=0
    EXPECT_EQ(cpu.getCyc(), 4);
}

TEST_F(OpcodeTests, ADD_C_ZeroCarryParityFlag){

    // Test ADD C (0x81)
    uint16_t initial_pc = cpu.getPC();
    cpu.setA(0xF0);
    cpu.setC(0x10);
    cpu.setFlags(0x02); // Clear flags
    loadAndRun(initial_pc, {0x81});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getA(), 0x00);        // A = 0xFF + 0x01 = 0x00
    EXPECT_EQ(cpu.getBC(), 0x0010);
    EXPECT_EQ(cpu.getDE(), 0x0000);
    EXPECT_EQ(cpu.getHL(), 0x0000);
    
    // Flags: Z=1, S=0, P=1, AC=0, C=1
    EXPECT_TRUE(cpu.getFlags() & FLAG_ZERO);
    EXPECT_FALSE(cpu.getFlags() & FLAG_SIGN);
    EXPECT_TRUE(cpu.getFlags() & FLAG_PARITY);
    EXPECT_FALSE(cpu.getFlags() & FLAG_AUX_CARRY);
    EXPECT_TRUE(cpu.getFlags() & FLAG_CARRY);

    EXPECT_EQ(cpu.getCyc(), 4);
}

TEST_F(OpcodeTests, ADD_D_SignFlag){

    // Test ADD D (0x82)
    uint16_t initial_pc = cpu.getPC();
    cpu.setA(0x7F);
    cpu.setD(0x10);
    cpu.setFlags(0x02); // Clear flags
    loadAndRun(initial_pc, {0x82});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getA(), 0x8F);        // A = 0x7F + 0x10 = 0x8F
    EXPECT_EQ(cpu.getBC(), 0x0000);
    EXPECT_EQ(cpu.getDE(), 0x1000);
    EXPECT_EQ(cpu.getHL(), 0x0000);
    
    // Flags: Z=0, S=1, P=0, AC=0, C=0
    EXPECT_FALSE(cpu.getFlags() & FLAG_ZERO);
    EXPECT_TRUE(cpu.getFlags() & FLAG_SIGN);
    EXPECT_FALSE(cpu.getFlags() & FLAG_PARITY);
    EXPECT_FALSE(cpu.getFlags() & FLAG_AUX_CARRY);
    EXPECT_FALSE(cpu.getFlags() & FLAG_CARRY);

    EXPECT_EQ(cpu.getCyc(), 4);
}

TEST_F(OpcodeTests, ADD_E_ParityFlag){

    // Test ADD E (0x83)
    uint16_t initial_pc = cpu.getPC();
    cpu.setA(0x01);
    cpu.setE(0x01);
    cpu.setFlags(cpu.getFlags() | FLAG_PARITY); // Clear flags
    loadAndRun(initial_pc, {0x83});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getA(), 0x02);        // A = 0x01 + 0x01 = 0x02
    EXPECT_EQ(cpu.getBC(), 0x0000);
    EXPECT_EQ(cpu.getDE(), 0x0001);
    EXPECT_EQ(cpu.getHL(), 0x0000);
    
    // Flags: Z=0, S=0, P=0, AC=0, C=0
    EXPECT_FALSE(cpu.getFlags() & FLAG_ZERO);
    EXPECT_FALSE(cpu.getFlags() & FLAG_SIGN);
    EXPECT_FALSE(cpu.getFlags() & FLAG_PARITY);
    EXPECT_FALSE(cpu.getFlags() & FLAG_AUX_CARRY);
    EXPECT_FALSE(cpu.getFlags() & FLAG_CARRY);

    EXPECT_EQ(cpu.getCyc(), 4);
}

TEST_F(OpcodeTests, ADD_H_AuxiliaryFlag){

    // Test ADD H (0x84)
    uint16_t initial_pc = cpu.getPC();
    cpu.setA(0x0F);
    cpu.setH(0x01);
    cpu.setFlags(0x02); // Clear flags
    loadAndRun(initial_pc, {0x84});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getA(), 0x10);        // A = 0x0F + 0x01
    EXPECT_EQ(cpu.getBC(), 0x0000);
    EXPECT_EQ(cpu.getDE(), 0x0000);
    EXPECT_EQ(cpu.getHL(), 0x0100);
    
    // Flags: Z=0, S=0, P=0, AC=1, C=0
    EXPECT_FALSE(cpu.getFlags() & FLAG_ZERO);
    EXPECT_FALSE(cpu.getFlags() & FLAG_SIGN);
    EXPECT_FALSE(cpu.getFlags() & FLAG_PARITY);
    EXPECT_TRUE(cpu.getFlags() & FLAG_AUX_CARRY);
    EXPECT_FALSE(cpu.getFlags() & FLAG_CARRY);

    EXPECT_EQ(cpu.getCyc(), 4);
}

TEST_F(OpcodeTests, ADD_L){

    // Test ADD L (0x85)
    uint16_t initial_pc = cpu.getPC();
    cpu.setA(0x7E);
    cpu.setL(0x01);
    cpu.setFlags(cpu.getFlags() | FLAG_PARITY | FLAG_SIGN | FLAG_ZERO | FLAG_AUX_CARRY | FLAG_CARRY); // Set flags
    loadAndRun(initial_pc, {0x85});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getA(), 0x7F);        // A = 0x7E + 0x01
    EXPECT_EQ(cpu.getBC(), 0x0000);
    EXPECT_EQ(cpu.getDE(), 0x0000);
    EXPECT_EQ(cpu.getHL(), 0x0001);
    
    // Flags: Z=0, S=0, P=0, AC=0, C=0
    EXPECT_FALSE(cpu.getFlags() & FLAG_ZERO);
    EXPECT_FALSE(cpu.getFlags() & FLAG_SIGN);
    EXPECT_FALSE(cpu.getFlags() & FLAG_PARITY);
    EXPECT_FALSE(cpu.getFlags() & FLAG_AUX_CARRY);
    EXPECT_FALSE(cpu.getFlags() & FLAG_CARRY);

    EXPECT_EQ(cpu.getCyc(), 4);
}

TEST_F(OpcodeTests, ADD_M){

    // Test ADD M (0x86)
    uint16_t initial_pc = cpu.getPC();
    cpu.setHL(0x2000);
    hal.write_byte(0x2000, 0x01);
    cpu.setA(0x7E);
    cpu.setFlags(0x02); // Clear flags

    loadAndRun(initial_pc, {0x86});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getA(), 0x7F);        // A = 0x7E + 0x01
    EXPECT_EQ(cpu.getBC(), 0x0000);
    EXPECT_EQ(cpu.getDE(), 0x0000);
    EXPECT_EQ(cpu.getHL(), 0x2000); // HL should not change
    EXPECT_EQ(hal.read_byte(0x2000), 0x01); // Memory value remains unchanged
    
    // Flags: Z=0, S=0, P=0, AC=0, C=0
    EXPECT_FALSE(cpu.getFlags() & FLAG_ZERO);
    EXPECT_FALSE(cpu.getFlags() & FLAG_SIGN);
    EXPECT_FALSE(cpu.getFlags() & FLAG_PARITY);
    EXPECT_FALSE(cpu.getFlags() & FLAG_AUX_CARRY);
    EXPECT_FALSE(cpu.getFlags() & FLAG_CARRY);

    EXPECT_EQ(cpu.getCyc(), 7);
}

TEST_F(OpcodeTests, ADD_A){

    // Test ADD A (0x87)
    uint16_t initial_pc = cpu.getPC();
    cpu.setA(0x01);
    cpu.setFlags(0x02); // Clear flags

    loadAndRun(initial_pc, {0x87});
    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getA(), 0x02);        // A = 0x01 + 0x01
    EXPECT_EQ(cpu.getBC(), 0x0000);
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