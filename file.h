#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include "deque.h"
#define maxx 1002
#define min -10000
#define max 30000
#define base 10

int write_deque(FILE *file, Deque *deque);
int print_file(char *filename);
int generate_file(char *filename, int count);
int read_deque(char *filename, Deque *deque);
int compare_file(char *filename, FILE *table);
int compare_files(void);

#endif