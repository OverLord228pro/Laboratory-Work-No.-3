#include "sort.h"
#include <time.h>

int experimental_sort(Deque *deque, Deque *copied_deque, double *seconds)
{
    clock_t start;
    int left;
    int right;
    int size;
    int end;
    int i;
    short int swapped;

    *seconds = 0;

    if (deque_copy(copied_deque, deque) == 0)
    {
        return 0;
    }

    size = deque_size(copied_deque);
    if (size == -1)
    {
        deque_clear(copied_deque);
        return 0;
    }

    if (size < 2)
    {
        return 1;
    }

    start = clock();

    for (end = size - 1; end > 0; end--)
    {
        swapped = 0;
        for (i = 0; i < end; i++)
        {
            deque_pop_front(copied_deque, &left);

            if (left > copied_deque->front->value)
            {
                deque_pop_front(copied_deque, &right);
                if (deque_push_front(copied_deque, left) == 0 || deque_push_front(copied_deque, right) == 0)
                {
                    return 0;
                }
                swapped = 1;
            }
            else
            {
                if (deque_push_front(copied_deque, left) == 0)
                {
                    return 0;
                }
            }

            deque_pop_front(copied_deque, &left);
            if (deque_push_back(copied_deque, left) == 0)
            {
                return 0;
            }
        }

        for (i = end; i < size; i++)
        {
            deque_pop_front(copied_deque, &left);
            if (deque_push_back(copied_deque, left) == 0)
            {
                return 0;
            }
        }
        if (swapped == 0)
        {
            break;
        }
    }
    *seconds = (double)(clock() - start) / CLOCKS_PER_SEC;
    return 1;
}


int bubble_sort(Deque *deque, Deque *copied_deque, double *seconds)
{
    clock_t start;
    int left;
    int right;
    int size;
    int end;
    int i;
    int j;
    short int swapped;

    *seconds = 0;

    if (deque_copy(copied_deque, deque) == 0)
    {
        return 0;
    }

    size = deque_size(copied_deque);
    if (size == -1)
    {
        deque_clear(copied_deque);
        return 0;
    }

    if (size < 2)
    {
        return 1;
    }

    start = clock();

    for (end = size - 1; end > 0; end--)
    {
        swapped = 0;

        for (i = 0; i < end; i++)
        {
            for (j = 0; j < i; j++)
            {
                if (deque_pop_front(copied_deque, &left) == 0 || deque_push_back(copied_deque, left) == 0)
                {
                    return 0;
                }
            }

            if (deque_pop_front(copied_deque, &left) == 0)
            {
                return 0;
            }

            if (left > copied_deque->front->value)
            {
                if (deque_pop_front(copied_deque, &right) == 0 ||
                    deque_push_front(copied_deque, left) == 0 ||
                    deque_push_front(copied_deque, right) == 0)
                {
                    return 0;
                }

                swapped = 1;
            }
            else
            {
                if (deque_push_front(copied_deque, left) == 0)
                {
                    return 0;
                }
            }

            for (j = 0; j < i; j++)
            {
                if (deque_pop_back(copied_deque, &right) == 0 || deque_push_front(copied_deque, right) == 0)
                {
                    return 0;
                }
            }
        }

        if (swapped == 0)
        {
            break;
        }
    }

    *seconds = (double)(clock() - start) / CLOCKS_PER_SEC;
    return 1;
}

void heap_rotate(Deque *deque, int shift, int size)
{
    if (shift > size / 2)
    {
        shift -= size;
    }
    else if (shift < -(size / 2))
    {
        shift += size;
    }

    while (shift > 0)
    {
        deque_attach_back(deque, deque_detach_front(deque));
        shift--;
    }

    while (shift < 0)
    {
        deque_attach_front(deque, deque_detach_back(deque));
        shift++;
    }
}

void heap_swap_nodes(Deque *deque, int first_index, int second_index, int size)
{
    Deque_node *first;
    Deque_node *second;
    int between;

    between = second_index - first_index - 1;

    heap_rotate(deque, first_index, size);
    first = deque_detach_front(deque);

    heap_rotate(deque, between, size - 1);
    second = deque_detach_front(deque);

    deque_attach_front(deque, first);
    heap_rotate(deque, -between, size - 1);

    deque_attach_front(deque, second);
    heap_rotate(deque, -first_index, size);
}

void heapify(Deque *deque, int index, int heap_size, int size)
{
    int parent_value;
    int left_index;
    int front_index;
    int child_index;
    int child_value;

    if (index >= heap_size / 2)
    {
        return;
    }

    heap_rotate(deque, index, size);
    parent_value = deque->front->value;
    heap_rotate(deque, -index, size);

    while (index < heap_size / 2)
    {
        left_index = 2 * index + 1;
        front_index = left_index;

        if (left_index + 1 < heap_size)
        {
            front_index++;
        }

        heap_rotate(deque, front_index, size);

        child_index = front_index;
        child_value = deque->front->value;

        if (front_index != left_index && deque->back->value >= child_value)
        {
            child_index = left_index;
            child_value = deque->back->value;
        }

        heap_rotate(deque, -front_index, size);

        if (parent_value >= child_value)
        {
            return;
        }

        heap_swap_nodes(deque, index, child_index, size);
        index = child_index;
    }
}

int pyramid_sort(Deque *deque, Deque *copied_deque, double *seconds)
{
    clock_t start;
    int i;
    int size;

    *seconds = 0;

    if (deque_copy(copied_deque, deque) == 0)
    {
        return 0;
    }

    size = deque_size(copied_deque);
    if (size == -1)
    {
        deque_clear(copied_deque);
        return 0;
    }

    if (size < 2)
    {
        return 1;
    }

    start = clock();

    for (i = size / 2 - 1; i >= 0; i--)
    {
        heapify(copied_deque, i, size, size);
    }

    for (i = size - 1; i > 0; i--)
    {
        heap_swap_nodes(copied_deque, 0, i, size);
        heapify(copied_deque, 0, i, size);
    }

    *seconds = (double)(clock() - start) / CLOCKS_PER_SEC;
    return 1;
}