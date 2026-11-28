#include "sort.h"
#include <time.h>

int experimental_sort(Deque *deque, Deque *copied_deque, double *seconds)
{
    clock_t start;
    Deque_node *left;
    Deque_node *right;
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
            left = deque_detach_front(copied_deque);

            if (left->value > copied_deque->front->value)
            {
                right = deque_detach_front(copied_deque);
                deque_attach_front(copied_deque, left);
                deque_attach_back(copied_deque, right);
                swapped = 1;
            }
            else
            {
                deque_attach_back(copied_deque, left);
            }
        }

        for (i = end; i < size; i++)
        {
            left = deque_detach_front(copied_deque);
            deque_attach_back(copied_deque, left);
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
    Deque_node *left;
    Deque_node *right;
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
                left = deque_detach_front(copied_deque);
                deque_attach_back(copied_deque, left);
            }

            left = deque_detach_front(copied_deque);

            if (left->value > copied_deque->front->value)
            {
                right = deque_detach_front(copied_deque);
                deque_attach_front(copied_deque, left);
                deque_attach_front(copied_deque, right);
                swapped = 1;
            }
            else
            {
                deque_attach_front(copied_deque, left);
            }

            for (j = 0; j < i; j++)
            {
                right = deque_detach_back(copied_deque);
                deque_attach_front(copied_deque, right);
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

int heap_rotate_values(Deque *deque, int shift)
{
    int value;

    while (shift > 0)
    {
        if (deque_pop_front(deque, &value) == 0 || deque_push_back(deque, value) == 0)
        {
            return 0;
        }
        shift--;
    }

    while (shift < 0)
    {
        if (deque_pop_back(deque, &value) == 0 || deque_push_front(deque, value) == 0)
        {
            return 0;
        }
        shift++;
    }

    return 1;
}

int heap_value(Deque *deque, int index, int size, int *value)
{
    if (heap_rotate_values(deque, index) == 0)
    {
        return 0;
    }

    *value = deque->front->value;
    return heap_rotate_values(deque, size - index);
}

int heap_swap_values(Deque *deque, int first_index, int second_index)
{
    int first;
    int second;
    int between;

    between = second_index - first_index - 1;

    if (heap_rotate_values(deque, first_index) == 0 || deque_pop_front(deque, &first) == 0 ||
        heap_rotate_values(deque, between) == 0 || deque_pop_front(deque, &second) == 0)
    {
        return 0;
    }

    return deque_push_front(deque, first) && heap_rotate_values(deque, -between) &&
           deque_push_front(deque, second) && heap_rotate_values(deque, -first_index);
}

int heapify(Deque *deque, int index, int heap_size, int size)
{
    int parent_value;
    int child_value;
    int right_value;
    int child_index;

    while (index < heap_size / 2)
    {
        child_index = 2 * index + 1;

        if (heap_value(deque, index, size, &parent_value) == 0 || heap_value(deque, child_index, size, &child_value) == 0)
        {
            return 0;
        }

        if (child_index + 1 < heap_size)
        {
            if (heap_value(deque, child_index + 1, size, &right_value) == 0)
            {
                return 0;
            }

            if (right_value > child_value)
            {
                child_index++;
                child_value = right_value;
            }
        }

        if (parent_value >= child_value)
        {
            return 1;
        }

        if (heap_swap_values(deque, index, child_index) == 0)
        {
            return 0;
        }

        index = child_index;
    }

    return 1;
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
        if (heapify(copied_deque, i, size, size) == 0)
        {
            deque_clear(copied_deque);
            return 0;
        }
    }

    for (i = size - 1; i > 0; i--)
    {
        if (heap_swap_values(copied_deque, 0, i) == 0 ||
            heapify(copied_deque, 0, i, size) == 0)
        {
            deque_clear(copied_deque);
            return 0;
        }
    }

    *seconds = (double)(clock() - start) / CLOCKS_PER_SEC;
    return 1;
}