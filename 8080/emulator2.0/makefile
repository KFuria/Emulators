TBIN = i8080_test
PATHS = src/
PATHT = test/
PATHI = include/
PATHB = build/
PATHO = build/objs/
PATHD = build/depends/

CC = gcc
OPT = -O3
DEPFLAGS = -MT $@ -MD -MP -MF $(PATHD)$*.d # make .d files while compiling
CFLAGS = -Wall -Wextra -g -I. -I$(PATHI) $(OPT) $(DEPFLAGS)

.PHONY: all clean test

BUILD_PATHS = $(PATHB) $(PATHD) $(PATHO) $(PATHR)

SRC_CFILES = $(wildcard $(PATHS)*.c)
SRC_OBJS = $(SRC_CFILES:$(PATHS)%.c=$(PATHO)%.o)
SRC_DEPENDS = $(SRC_CFILES:$(PATHS)%.c=$(PATHD)%.d)

TEST_CFILES = $(wildcard $(PATHT)*.c)
TEST_OBJS = $(TEST_CFILES:$(PATHT)%.c=$(PATHO)%.o)
TEST_DEPENDS = $(TEST_CFILES:$(PATHT)%.c=$(PATHD)%.d)

# emulator and 8080 test build
test: $(BUILD_PATHS) $(TBIN)

$(TBIN): $(SRC_OBJS) $(TEST_OBJS)
	$(CC) -o $@ $^

$(PATHO)%.o: $(PATHS)%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(PATHO)%.o: $(PATHT)%.c
	$(CC) $(CFLAGS) -c $< -o $@


# application build
all: 



# Make directories if they don't exist
$(PATHB):
	mkdir -p $(PATHB)

$(PATHD):
	mkdir -p $(PATHD)

$(PATHO):
	mkdir -p $(PATHO)

clean: 
	rm -rf $(TBIN) $(SRC_OBJS) $(TEST_OBJS) $(SRC_DEPENDS) $(TEST_DEPENDS)

-include $(SRC_DEPENDS) $(TEST_DEPENDS)