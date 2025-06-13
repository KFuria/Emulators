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
    uint16_t initial_pc = cpu.getPC();
    cpu.setA(0b01010100); // A = 0x54 (Bit 7 is 0)
    cpu.setFlags(cpu.getFlags() | FLAG_CARRY); // Carry is 1

    loadAndRun(initial_pc, {0x1F}); // RAL

    EXPECT_EQ(cpu.getPC(), initial_pc + 1);
    EXPECT_EQ(cpu.getA(), 0b10101010); // A should be 0xAA (Old Carry 1 goes to A7)
    EXPECT_FALSE(cpu.getFlags() & FLAG_CARRY); // Old A0 (0) goes to Carry
    EXPECT_EQ(cpu.getCyc(), 4);
}