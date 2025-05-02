OUT_DIR=out
OUT_NAME=chip8

MAIN=$(OUT_DIR)/$(OUT_NAME).exe
DIS=$(OUT_DIR)/$(OUT_NAME).dasm

# Compiler
CC = g++
OPT = -O3

#=====================================================================
# Files
ASMFILES=

CFILES=

CPPFILES= 	main.cpp	 \
			logger.cpp	 \
			chip8.cpp	 \
			cpu.cpp		 \
			displaySDL.cpp \
			keyboardSDL.cpp	\
			
			
# Create obj files names from source files
ASMOBJS=$(patsubst %.S,%.o,$(ASMFILES))
COBJS=$(patsubst %.c,$(OUT_DIR)/%.o,$(CFILES))
CPPOBJS=$(patsubst %.cpp,$(OUT_DIR)/%.o,$(CPPFILES))

OBJS=$(ASMOBJS) $(COBJS) $(CPPOBJS)
# ==================================================================
# Flags
CC_HEADERS=

CC_FLAGS= -Wall -Wextra -g -std=c++20 $(OPT)

LIBS= -lSDL2 -lSDL2_ttf

LD_FLAGS= 

# ==================================================================

all: directory $(MAIN)

$(MAIN): $(OBJS)
	$(CC) $(LD_FLAGS) -o $@ $(OBJS) $(CC_HEADERS) $(CC_FLAGS) $(LIBS)

$(OUT_DIR)/%.o: %.S
	$(CC) $(CC_FLAGS) -c -o $@ $<

$(OUT_DIR)/%.o: %.c
	$(CC) $(CC_FLAGS) -c -o $@ $<

$(OUT_DIR)/%.o: %.cpp
	$(CC) $(CC_FLAGS) -c -o $@ $<

directory:
	mkdir -p $(OUT_DIR)


.PHONY: clean
clean:
	rm -f $(OBJS) $(MAIN)

#=====================================================================
# Debug section
print:
	$(info    OBJS is $(OBJS))
	$(info    CPPOBJS is $(CPPOBJS))
	$(info    CC is $(CC))