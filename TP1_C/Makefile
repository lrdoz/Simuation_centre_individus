CC=gcc
FH=include
FC=src/*
FILE=configue.properties
GTK=$(shell pkg-config --libs --cflags gtk+-2.0)

CFLAGS =-c -I $(FH) -Wformat-security -Wint-conversion -pedantic -Wunused-parameter -Wunused-value -Wunused-variable -g
CFLAGS += $(shell pkg-config --cflags gtk+-2.0)

exec : compilation main clean

main :
	$(CC) main.c $(CFLAGS)
	$(CC) -o main.out *.o $(GTK)

compilation:
	clear
	$(CC) $(FC) $(CFLAGS)

run : 
	./main.out < $(FILE)

gdb :
	gdb main.out

clean :
	rm -f *.o

real_clean: clean
	rm -f *.out
