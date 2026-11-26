#ifndef SORT_H
#define SORT_H

#include "deque.h"

int experimental_sort(Deque *deque, Deque *copied_deque, double *seconds);
void heapify(Deque *deque, int index, int heap_size, int size);
int bubble_sort(Deque *deque, Deque *copied_deque, double *seconds);
int pyramid_sort(Deque *deque, Deque *copied_deque, double *seconds);
#endif

