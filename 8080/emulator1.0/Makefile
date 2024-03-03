bin = i8080_test
src = $(wildcard *.c)
obj = $(src:.c=.o)
CFLAGS = -Wall -Wextra -g -std=c99 -pedantic
LDFLAGS =

.PHONY: all clean

all: $(bin)

$(bin): $(obj)
	$(CC) -o  $@ $^ $(LDFLAGS)

clean:
	-rm $(bin) $(obj)