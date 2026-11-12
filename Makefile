.PHONY: all

all: a.exe

main.o: main.c deque.h
	gcc -c -o main.o main.c

deque.o: deque.c deque.h
	gcc -c -o deque.o deque.c

a.exe: main.o deque.o
	gcc main.o deque.o