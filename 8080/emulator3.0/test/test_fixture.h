#ifndef TEST_TEST_FIXTURE_H
#define TEST_TEST_FIXTURE_H

#include <gtest/gtest.h>
#include <array>
#include <vector>
#include <cstdint>


#include "i8080.h"
#include "i8080_helpers.h"
#include "hal.h"

//-----------------------------------------------------------------------------
// Test Fixture for 8080 Opcode Tests
//-----------------------------------------------------------------------------
class OpcodeTests : public ::testing::Test {
protected:
    // Declare as static members so they are shared across all tests in the fixture
    static T8080 cpu;
    static THal hal;

    // SetUpTestSuite called once before the first test in the test suite
    static void SetUpTestSuite();

    // TearDownTestSuite
    static void TearDownTestSuite();

    // SetUp called before each test in the test suite
    void SetUp() override;

    // TearDown
    void TearDown() override;

    // Helper function to load a small program into mock memory and run it
    void loadAndRun(uint16_t start_addr, const std::vector<uint8_t>& program_bytes);
};

#endif // TEST_TEST_FIXTURE_H