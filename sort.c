#include "sort.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

void swap(Deque *deque, DequeNode *left)
{
    DequeNode *right;

    if (left == NULL || left->next == NULL) 
    {
        return;
    }
    right = left->next;

    left->next = right->next;

    if (left->next != NULL) 
    {
        left->next->prev = left;
    } 
    else 
    {
        deque->back = left;
    }

    right->prev = left->prev;

    if (right->prev != NULL) 
    {
        right->prev->next = right;
    } 
    else 
    {
        deque->front = right;
    }

    right->next = left;
    left->prev = right;
}

int bubble_sort(Deque *deque, Deque *copied_deque, double *seconds)
{
    clock_t start;
    DequeNode *current;
    DequeNode *end;
    DequeNode *last_swap;
    int size;
    *seconds = 0;
    if (deque_copy(copied_deque, deque) == 0)
    {
        return 0;
    }
    size = deque_size(copied_deque);
    if (size < 2) 
    {
        return 1;
    }
    end = NULL;
    start = clock();
    while (1)
    {
        last_swap = NULL;
        current = copied_deque->front;
        while (current != NULL && current->next != NULL)
        {
            if (current->value > current->next->value)
            {
                swap(copied_deque, current);
                last_swap = current;
            }
            else
            {
                current = current->next;
            }
        }
        if (last_swap == NULL)
        {
            *seconds = (double)(clock() - start) / CLOCKS_PER_SEC;
            return 1;
        }
        end = last_swap;
    }
}

DequeNode *deque_get_node(Deque *deque, int index, int size)
{
    DequeNode *current;
    int i;
    if (deque == NULL || index < 0 || index >= size) 
    {
        return NULL;
    }

    current = deque->front;
    for (i = 0; i < index; i++) 
    {
        current = current->next;
    }

    return current;
}

void swap_nodes(Deque *deque, DequeNode *node1, DequeNode *node2)
{
    DequeNode *prev1;
    DequeNode *next1;

    if (deque == NULL || node1 == NULL || node2 == NULL || node1 == node2)
    {
        return;
    }

    if (node1 == node2->prev)
    {
        swap(deque, node1);
        return;
    }

    if (node2 == node1->prev)
    {
        swap(deque, node2);
        return;
    }

    prev1 = node1->prev;
    next1 = node1->next;

    if (prev1 != NULL)
    {
        prev1->next = node2;
    }
    else
    {
        deque->front = node2;
    }

    if (next1 != NULL)
    {
        next1->prev = node2;
    }
    else
    {
        deque->back = node2;
    }

    if (node2->prev != NULL)
    {
        node2->prev->next = node1;
    }
    else
    {
        deque->front = node1;
    }

    if (node2->next != NULL)
    {
        node2->next->prev = node1;
    }
    else
    {
        deque->back = node1;
    }

    node1->prev = node2->prev;
    node1->next = node2->next;

    node2->prev = prev1;
    node2->next = next1;
}

void heapify(Deque *deque, DequeNode *parent, int index, int heap_size)
{
    DequeNode *child;
    int child_index;
    int i;

    while (index < heap_size / 2)
    {
        child_index = index * 2 + 1;
        child = parent;

        for (i = index; i < child_index; i++)
        {
            child = child->next;
        }

        if (child_index + 1 < heap_size &&
            child->next->value > child->value)
        {
            child = child->next;
            child_index++;
        }

        if (parent->value >= child->value)
        {
            return;
        }

        swap_nodes(deque, parent, child);
        index = child_index;
    }
}

int pyramid_sort(Deque *deque, Deque *copied_deque, double *seconds)
{
    clock_t start;
    DequeNode *parent;
    DequeNode *previous;
    DequeNode *last;
    DequeNode *maximum;
    int i;
    int size;

    *seconds = 0;

    if (deque_copy(copied_deque, deque) == 0)
    {
        return 0;
    }

    size = deque_size(copied_deque);

    if (size < 2)
    {
        return 1;
    }

    start = clock();

    i = size / 2 - 1;
    parent = deque_get_node(copied_deque, i, size);

    for (i = size / 2 - 1; i >= 0; i--)
    {
        previous = parent->prev;
        heapify(copied_deque, parent, i, size);
        parent = previous;
    }

    last = copied_deque->back;

    for (i = size - 1; i > 0; i--)
    {
        maximum = copied_deque->front;
        swap_nodes(copied_deque, maximum, last);
        heapify(copied_deque, copied_deque->front, 0, i);
        last = maximum->prev;
    }

    *seconds = (double)(clock() - start) / CLOCKS_PER_SEC;

    return 1;
}