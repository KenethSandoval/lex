C      = gcc

all: lex

lex: lex.c
	$(C) -o lex lex.c -lX11

run:
	./lex
