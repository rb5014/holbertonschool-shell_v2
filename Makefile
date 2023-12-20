CC = gcc
CFLAGS = -std=c90 -Wall -Werror -Wextra -pedantic
EXE = hsh

all: *.c
	$(CC) $(CFLAGS) *.c -o $(EXE)


.PHONY: clean
clean:
	rm -f ./$(EXE)