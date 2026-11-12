#include <stdio.h>
#include "deque.h"

int main(void)
{
    Deque deque;
    double value;

    deque_init(&deque);

    if (deque_push_back(&deque, 1.5) == 0 ||
        deque_push_front(&deque, -2.25) == 0) {
        printf("Memory allocation error\n");
        deque_clear(&deque);
        return 1;
    }

    printf("Deque: ");
    deque_print(&deque);
    if (deque_pop_back(&deque, &value) != 0) {
        printf("Removed back: %f\n", value);
    }

    printf("After pop_back: ");
    deque_print(&deque);

    if (deque_pop_front(&deque, &value) != 0) {
        printf("Removed front: %f\n", value);
    }

    printf("Size: %d\n", deque.size);

    if (deque_pop_front(&deque, &value) == 0) {
        printf("Deque is empty\n");
    }

    deque_clear(&deque);

    return 0;
}