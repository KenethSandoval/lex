CFLAGS += -std=c++17
CC      = g++

all: lex

lex: main.cpp
	$(CC) -o lex main.cpp $(CFLAGS) -lX11

run:
	./lex
