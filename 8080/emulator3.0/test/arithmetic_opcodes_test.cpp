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
    EXPECT_EQ(cpu.getSP(), 0x0001);
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

    // Flags: Z=0, S=1, P=0, AC=0, C (unaffected)
    EXPECT_FALSE(cpu.getFlags() & FLAG_ZERO);
    EXPECT_TRUE(cpu.getFlags() & FLAG_SIGN);
    EXPECT_FALSE(cpu.getFlags() & FLAG_PARITY);
    EXPECT_TRUE(cpu.getFlags() & FLAG_AUX_CARRY);
    EXPECT_TRUE(cpu.getFlags() & FLAG_CARRY);

    EXPECT_EQ(cpu.getCyc(), 10);

}