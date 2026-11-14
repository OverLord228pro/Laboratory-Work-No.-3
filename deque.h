#ifndef DEQUE_H
#define DEQUE_H


typedef struct DequeNode{
    double value;
    struct DequeNode *prev;
    struct DequeNode *next;
} DequeNode;

typedef struct Deque{
    DequeNode *front;
    DequeNode *back;
} Deque;

void deque_init(Deque *deque);
int deque_push_back(Deque *deque, double value);
int deque_push_front(Deque *deque, double value);
void deque_clear(Deque *deque);
int deque_pop_front(Deque *deque, double *value);
int deque_pop_back(Deque *deque, double *value);
int deque_change(Deque *deque, int pos, double value);
void deque_print(Deque *deque);
int deque_size(Deque *deque);
int deque_copy(Deque *copied_deque, Deque *deque);

#endif