ifeq ($(OSTYPE),cygwin)
	CLEANUP=rm -f
	MKDIR=mkdir -p
	TARGET_EXTENSION=out
else ifeq ($(OS),Windows_NT)
	CLEANUP=rm -f
	MKDIR=mkdir
	TARGET_EXTENSION=exe
else
	CLEANUP=rm -f
	MKDIR=mkdir -p
	TARGET_EXTENSION=out
endif

TBIN = i8080_test
PATHb = bin/
PATHS = src/
PATHI = inc/
PATHB = build/
PATHO = build/objs/
PATHD = build/depends/

CC = gcc
OPT = -O0
DEPFLAGS = -MT $@ -MD -MP -MF $(PATHD)$*.d # make .d files while compiling
CFLAGS = -Wall -Wextra -g -std=c99 -pedantic -I. -I$(PATHI) $(OPT) $(DEPFLAGS)

.PHONY: all clean test

BUILD_PATHS = $(PATHB) $(PATHD) $(PATHO) $(PATHb)

SRC_CFILES = $(wildcard $(PATHS)*.c)
SRC_OBJS = $(SRC_CFILES:$(PATHS)%.c=$(PATHO)%.o)
SRC_DEPENDS = $(SRC_CFILES:$(PATHS)%.c=$(PATHD)%.d)


# emulator and 8080 test build
test: $(BUILD_PATHS) $(PATHb)$(TBIN).$(TARGET_EXTENSION)

$(PATHb)$(TBIN).$(TARGET_EXTENSION): $(SRC_OBJS)
	$(CC) -o $@ $^

$(PATHO)%.o: $(PATHS)%.c
	$(CC) $(CFLAGS) -c $< -o $@


# application build
all: 


# Make directories if they don't exist
$(PATHB):
	$(MKDIR) $(PATHB)

$(PATHD):
	$(MKDIR) $(PATHD)

$(PATHO):
	$(MKDIR) $(PATHO)

$(PATHb):
	$(MKDIR) $(PATHb)

clean: 
	$(CLEANUP) $(PATHb)$(TBIN).$(TARGET_EXTENSION) $(SRC_OBJS) $(SRC_DEPENDS)


.PRECIOUS: $(PATHb)$(TBIN).$(TARGET_EXTENSION)
.PRECIOUS: $(PATHO)%.o
.PRECIOUS: $(PATHD)%.d

-include $(SRC_DEPENDS)