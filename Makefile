.PHONY: all

all: a.exe

main.o: main.c deque.h sort.h input.h
	gcc -c -o main.o main.c

deque.o: deque.c deque.h
	gcc -c -o deque.o deque.c

sort.o: sort.c sort.h deque.h
	gcc -c -o sort.o sort.c

input.o: input.c input.h deque.h
	gcc -c -o input.o input.c

file.o: file.c file.h deque.h
	gcc -c -o file.o file.c

a.exe: main.o deque.o sort.o input.o file.o
	gcc -o a.exe main.o deque.o sort.o input.o file.o