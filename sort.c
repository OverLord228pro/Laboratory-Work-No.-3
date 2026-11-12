#include "sort.h"
#include <stddef.h>

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

void bubble_sort(Deque *deque)
{
    short int swapped;
    DequeNode *current;
    if (deque == NULL || deque->size < 2) 
    {
        return;
    }
    while (1)
    {
        swapped = 0;
        current = deque->front;
        while (current != NULL && current->next != NULL)
        {
            if (current->value > current->next->value)
            {
                swap(deque, current);
                swapped = 1;
            }
            else
            {
                current = current->next;
            }
        }
        if (swapped == 0)
        {
            return;
        }
    }
}

DequeNode *deque_get_node(Deque *deque, int index)
{
    DequeNode *current;
    int i;
    if (deque == NULL || index < 0 || index >= deque->size) 
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

void sift_down(Deque *deque, int index, int heap_size)
{
    DequeNode *parent;
    DequeNode *largest;
    DequeNode *right;
    int left_index;
    int right_index;
    int largest_index;

    if (deque == NULL || heap_size < 2 ||
        heap_size > deque->size || index < 0 || index >= heap_size)
    {
        return;
    }

    parent = deque_get_node(deque, index);

    while (index < heap_size / 2)
    {
        left_index = 2 * index + 1;
        right_index = left_index + 1;

        largest_index = left_index;
        largest = deque_get_node(deque, left_index);

        if (right_index < heap_size)
        {
            right = deque_get_node(deque, right_index);

            if (right->value > largest->value)
            {
                largest = right;
                largest_index = right_index;
            }
        }

        if (parent->value >= largest->value)
        {
            return;
        }

        swap_nodes(deque, parent, largest);

        index = largest_index;
    }
}

void heap_sort(Deque *deque)
{
    DequeNode *last;
    int i;

    if (deque == NULL || deque->size < 2)
    {
        return;
    }

    for (i = deque->size / 2 - 1; i >= 0; i--)
    {
        sift_down(deque, i, deque->size);
    }

    for (i = deque->size - 1; i > 0; i--)
    {
        last = deque_get_node(deque, i);

        swap_nodes(deque, deque->front, last);

        sift_down(deque, 0, i);
    }
}