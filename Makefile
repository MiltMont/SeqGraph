INCLUDE_DIR = ./include
LIB_DIR = ./lib
SRCS = $(wildcard ./src/*.c)

LDFLAGS = -std=c99 -I$(INCLUDE_DIR) -L$(LIB_DIR) -lm -ldl -losw -lX11 -lGL 


SeqGraphTest: src/main.c
	gcc $(SRCS) -o SeqGraphTest $(LDFLAGS) 

SeqGraphDebug: src/main.c 
	gcc $(SRCS) -o SeqGraphDebug $(LDFLAGS) -DDEBUG

SeqGraphProf: src/main.c
	gcc $(SRCS) -o SeqGraphProfile $(LDFLAGS) -pg

.PHONY: test clean debug

test: SeqGraphTest
	./SeqGraphTest

debug: SeqGraphDebug
	./SeqGraphDebug

profile: SeqGraphProf
	./SeqGraphProfile 
	gprof ./SeqGraphProfile > results.md

clean: 
	rm SeqGraph* gmon.out results.md

