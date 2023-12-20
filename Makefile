CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -g
EXE = hsh

all: *.c
	$(CC) $(CFLAGS) *.c -o $(EXE)

allc90: *.c
	$(CC) $(CFLAGS) -std=c90 *.c -o $(EXE)

.PHONY: clean
clean:
	rm -f ./$(EXE)