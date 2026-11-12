#ifndef SORT_H
#define SORT_H

#include "deque.h"

void swap(Deque *deque, DequeNode *left);
void bubble_sort(Deque *deque);
DequeNode *deque_get_node(Deque *deque, int index);
void swap_nodes(Deque *deque, DequeNode *node1, DequeNode *node2);
void sift_down(Deque *deque, int index, int heap_size);
void heap_sort(Deque *deque);
#endif

