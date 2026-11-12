.PHONY: all

all: a.exe

main.o: main.c deque.h
	gcc -c -o main.o main.c

deque.o: deque.c deque.h
	gcc -c -o deque.o deque.c

sort.o: sort.c sort.h
	gcc -c -o sort.o sort.c

a.exe: main.o deque.o sort.o
	gcc main.o deque.o sort.o