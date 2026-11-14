#ifndef SORT_H
#define SORT_H

#include "deque.h"

void swap(Deque *deque, DequeNode *left);
int bubble_sort(Deque *deque, Deque *copied_deque);
DequeNode *deque_get_node(Deque *deque, int index);
void swap_nodes(Deque *deque, DequeNode *node1, DequeNode *node2);
void heapify(Deque *deque, int index, int heap_size);
int pyramid_sort(Deque *deque, Deque *copied_deque);
#endif

