INCLUDE_DIR = ./include
LIB_DIR = ./lib
SRCS = $(wildcard ./src/*.c)

LDFLAGS = -I$(INCLUDE_DIR) -L$(LIB_DIR) -lm -ldl -losw -lX11 -lGL


SeqGraphTest: src/main.c
	gcc $(SRCS) -o SeqGraphTest $(LDFLAGS)

.PHONY: test clean

test: SeqGraphTest
	./SeqGraphTest

clean: 
	rm -f SeqGraphTest
