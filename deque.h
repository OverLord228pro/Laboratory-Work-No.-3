#ifndef DEQUE_H
#define DEQUE_H


typedef struct Deque_node{
    int value;
    struct Deque_node *prev;
    struct Deque_node *next;
} Deque_node;

typedef struct{
    Deque_node *front;
    Deque_node *back;
} Deque;

void deque_init(Deque *deque);
short int deque_push_back(Deque *deque, int value);
short int deque_push_front(Deque *deque, int value);
short int deque_pop_front(Deque *deque, int *value);
short int deque_pop_back(Deque *deque, int *value);

void deque_clear(Deque *deque);
short int deque_change_node(Deque *deque, int pos, int value);
void deque_print(Deque *deque);
short int deque_copy(Deque *copied_deque, Deque *deque);
int deque_size(Deque *deque);

Deque_node *deque_detach_front(Deque *deque);
Deque_node *deque_detach_back(Deque *deque);
int deque_attach_back(Deque *deque, Deque_node *node);
int deque_attach_front(Deque *deque, Deque_node *node);

#endif