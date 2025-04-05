CC = g++
OPT = -O3
LIBS = -lSDL2 -lSDL2_ttf
CPPFLAGS = -Wall -Wextra -g -std=c++17 $(OPT) -pedantic
MAIN = main

SRC_FILES = $(wildcard *.cpp)
OBJS_FILES = $(SRC_FILES:.cpp=.o)

all: $(MAIN)

$(MAIN): $(OBJS_FILES)
	$(CC) $(CPPFLAGS) -o $(MAIN).exe $(OBJS_FILES) $(LIBS)

.c.o:
	$(CC) $(CPPFLAGS) -c $< -o $@

clean: 
	$(RM) *.o *~ $(MAIN).exe