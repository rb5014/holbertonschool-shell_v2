CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -g
EXE = hsh
SOURCES = $(shell find src -type f -name '*.c')

all: $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $(EXE)

allc90: $(SOURCES)
	$(CC) $(CFLAGS) -std=c90 $(SOURCES) -o $(EXE)

.PHONY: clean
clean:
	rm -f ./$(EXE)
