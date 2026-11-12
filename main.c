#include <stdio.h>
#include "deque.h"
#include "sort.h"
#include <locale.h>

int main(void)
{
    setlocale(LC_ALL, "Russian");
    Deque deque;
    double value;

    deque_init(&deque);

    if (deque_push_back(&deque, -1.5) == 0 ||
        deque_push_front(&deque, 2.25) == 0) {
        printf("Ошибка выделения памяти\n");
        deque_clear(&deque);
        return 1;
    }

    printf("Deque: ");
    deque_print(&deque);
    bubble_sort(&deque);

    printf("Отсортированный Deque: ");
    deque_print(&deque);
    if (deque_pop_back(&deque, &value) != 0) {
        printf("Удален элемент с конца: %f\n", value);
    }

    printf("После pop_back: ");
    deque_print(&deque);

    if (deque_pop_front(&deque, &value) != 0) {
        printf("Удален элемент с начала: %f\n", value);
    }

    printf("Size: %d\n", deque.size);

    if (deque_pop_front(&deque, &value) == 0) {
        printf("Deque is empty\n");
    }

    deque_clear(&deque);

    return 0;
}