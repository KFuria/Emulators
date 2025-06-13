#=============================================================================
# Makefile for i8080 Emulator
#
# This Makefile compiles a C++ project for an i8080 emulator. 
# It uses GoogleTest for unit testing. 
#
# Targets:
#   all     : Builds the i8080 executable. (Default)
#   clean   : Removes all compiled files and the executable.
#   
#
# Usage:
#   make          			- Builds the project in release mode.
#   make clean    			- Cleans the project.
#   make test               - Builds and runs all unit tests in test mode.
#   make test OPCODE=LXI  	- Builds and runs only LXI-related opcode tests.
#=============================================================================

#-----------------------------------------------------------------------------
# Configuration Variables
#-----------------------------------------------------------------------------

# Output Directories and Names
OUT_DIR     := out
OUT_NAME    := i8080
MAIN        := $(OUT_DIR)/$(OUT_NAME)
DIS         := $(OUT_DIR)/$(OUT_NAME).dasm

# Compiler
CXX         := g++
OPT         := -O3

# Source Directories
SRC_DIR     := src
INC_DIR     := include
TEST_DIR	:= test

#-----------------------------------------------------------------------------
# Source Files
#-----------------------------------------------------------------------------

ASM_SOURCES :=
C_SOURCES   :=
CPP_SOURCES := $(SRC_DIR)/logger.cpp \
			   $(SRC_DIR)/opcodes.cpp \
               $(SRC_DIR)/i8080.cpp \
               $(SRC_DIR)/disassemble.cpp\
			   $(SRC_DIR)/hal.cpp
			   
# Test Source Files
TEST_SOURCES := $(TEST_DIR)/main_test.cpp \
				$(TEST_DIR)/opcodes_test.cpp \
				$(TEST_DIR)/data_transfer_opcodes_test.cpp \
                $(TEST_DIR)/arithmetic_opcodes_test.cpp \
                $(TEST_DIR)/stack_opcodes_test.cpp \
				$(TEST_DIR)/logical_opcodes_test.cpp \
				$(TEST_DIR)/other_opcodes_test.cpp

			
#-----------------------------------------------------------------------------
# Object Files
#-----------------------------------------------------------------------------

# Create obj files names from source files
ASM_OBJS    := $(patsubst $(SRC_DIR)/%.S,$(OUT_DIR)/%.o,$(ASM_SOURCES))
C_OBJS      := $(patsubst $(SRC_DIR)/%.c,$(OUT_DIR)/%.o,$(C_SOURCES))
CPP_OBJS    := $(patsubst $(SRC_DIR)/%.cpp,$(OUT_DIR)/%.o,$(CPP_SOURCES))

OBJS        := $(ASM_OBJS) $(C_OBJS) $(CPP_OBJS)

# Object files for tests
TEST_OBJS   := $(patsubst $(TEST_DIR)/%.cpp,$(OUT_DIR)/%.o,$(TEST_SOURCES))



#-----------------------------------------------------------------------------
# Compilation Flags
#-----------------------------------------------------------------------------

CXXFLAGS    := -Wall -Wextra -g -std=c++23 $(OPT) -pthread
LDFLAGS     := 

# Include paths
INCLUDE_PATHS := -I$(INC_DIR) -I$(TEST_DIR)

# Libraries
LIBS        := 
TEST_LIBS	:= -lgtest -lgtest_main -pthread

# Define common flags for release build
RELEASE_FLAGS := $(CXXFLAGS) $(INCLUDE_PATHS)

# Define common flags for test/debug build (includes -DTEST_BUILD)
TEST_DEBUG_FLAGS := $(CXXFLAGS) $(INCLUDE_PATHS) -DTEST_BUILD


#-----------------------------------------------------------------------------
# Targets
#-----------------------------------------------------------------------------

.PHONY: all clean directory

all: directory $(MAIN)

$(MAIN): $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $(OBJS) $(RELEASE_FLAGS) $(LIBS)

# Rule for compiling C++ source files
$(OUT_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(RELEASE_FLAGS) -c $< -o $@

# Rule for compiling C source files (if any)
$(OUT_DIR)/%.o: $(SRC_DIR)/%.c
	$(CXX) $(RELEASE_FLAGS) -c $< -o $@

# Rule for compiling Assembly source files (if any)
$(OUT_DIR)/%.o: $(SRC_DIR)/%.S
	$(CXX) $(RELEASE_FLAGS) -c $< -o $@

# Rule for compiling test source files
$(OUT_DIR)/%.o: $(TEST_DIR)/%.cpp
	$(CXX) $(TEST_DEBUG_FLAGS) -c $< -o $@


# Target for building and running all tests
TEST_EXE := $(OUT_DIR)/test_runner

test: directory $(TEST_EXE)
	@echo "Running all unit tests..."
	@$(TEST_EXE)

$(TEST_EXE): $(OBJS) $(TEST_OBJS)
	$(CXX) $(LDFLAGS) -o $@ $(OBJS) $(TEST_OBJS) $(TEST_DEBUG_FLAGS) $(LIBS) $(TEST_LIBS)


# Define FILTER as an empty string by default
OPCODE ?= 

# Determine the gtest_filter argument based on the FILTER variable
# If FILTER is empty, use 'OpcodeTests.*' to run all opcode tests.
# Otherwise, use 'OpcodeTests.$(FILTER)*' to filter by the provided value.
ifeq ($(OPCODE),)
    GTEST_FILTER_ARG = --gtest_filter=OpcodeTests.*
	OPCODE = "all"
else
    GTEST_FILTER_ARG = --gtest_filter=OpcodeTests.$(OPCODE)*
endif

# Target for building and running specific opcode tests, now using FILTER variable
OPCODE_TEST_EXE  := $(OUT_DIR)/opcode_test_runner

test_opcode: directory $(OPCODE_TEST_EXE)
	@echo "Running OPCODE tests for $(OPCODE)..."
	@$(OPCODE_TEST_EXE) $(GTEST_FILTER_ARG)

$(OPCODE_TEST_EXE): $(OBJS) $(TEST_OBJS) # Link all test object files here for the general runner
	$(CXX) $(LDFLAGS) -o $@ $(OBJS) $(TEST_OBJS) $(TEST_DEBUG_FLAGS) $(LIBS) $(TEST_LIBS)


# Create the output directory if it doesn't exist
directory:
	@mkdir -p $(OUT_DIR)

clean:
	@echo "Cleaning project..."
	$(RM) $(OBJS) $(TEST_OBJS) $(MAIN) $(TEST_EXE) $(OPCODE_TEST_EXE)
	@echo "Clean complete."

# End of Makefile