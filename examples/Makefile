CC = gcc
VERSION = -std=c89
OPT = -O2 -march=native
OUTPUT = a.out

LIBS =
HEADERS =

SRC = main.c

all: main

main: $(SRC)
	    $(CC) $(VERSION) $(OPT) $(HEADERS) $(LIBS) -o $(OUTPUT) $^

clean: $(OUTPUT)
	rm $^
