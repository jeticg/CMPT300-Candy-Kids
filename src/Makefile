## This is a simple Makefile with lots of comments
## Check Unix Programming Tools handout for more info.

# Define what compiler to use and the flags.
CC=cc
CXX=CC
CCFLAGS= -std=c99 -D_POSIX_C_SOURCE=200809L -Wall -Werror -Wextra -Wconversion

all: candykids

debug: CCFLAGS += -DDEBUG -g
debug: candykids

# Compile all .c files into .o files
# % matches all (like * in a command)
# $< is the source file (.c file)

%.o : %.c
	$(CC) -c $(CCFLAGS) $<

candykids: candykids.o aux.o bbuff.o
	$(CC) -o candykids *.o $(CCFLAGS)

clean:
	rm -f *.o candykids
