INCLUDE_DIR = ./include
LIB_DIR = ./lib
SRCS = $(wildcard ./src/*.c)

LDFLAGS = -std=c99 -I$(INCLUDE_DIR) -L$(LIB_DIR) -lm -ldl -losw -lX11 -lGL -g 


SeqGraphTest: src/main.c
	gcc $(SRCS) -o SeqGraphTest $(LDFLAGS)

SeqGraphDebug: src/main.c 
	gcc $(SRCS) -pedantic -Wall -o SeqGraphDebug $(LDFLAGS) -DDEBUG 


.PHONY: test clean debug

test: SeqGraphTest
	./SeqGraphTest

clean: 
	rm -f SeqGraph*

debug: SeqGraphDebug
	./SeqGraphDebug