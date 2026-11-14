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

int bubble_sort(Deque *deque, Deque *copied_deque)
{
    short int swapped;
    DequeNode *current;
    int size;
    if (deque_copy(copied_deque, deque) == 0)
    {
        return 0;
    }
    size = deque_size(copied_deque);
    if (size < 2) 
    {
        return 1;
    }
    while (1)
    {
        swapped = 0;
        current = copied_deque->front;
        while (current != NULL && current->next != NULL)
        {
            if (current->value > current->next->value)
            {
                swap(copied_deque, current);
                swapped = 1;
            }
            else
            {
                current = current->next;
            }
        }
        if (swapped == 0)
        {
            return 1;
        }
    }
}

DequeNode *deque_get_node(Deque *deque, int index)
{
    DequeNode *current;
    int i;
    int size = deque_size(deque);
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

void heapify(Deque *deque, int index, int heap_size)
{
    int largest = index;
    int left = index * 2 + 1;
    int right = index * 2 + 2;
    DequeNode *parent = deque_get_node(deque, largest);
    DequeNode *left_node = deque_get_node(deque, left);
    DequeNode *right_node = deque_get_node(deque, right);
    if (left_node != NULL && left_node->value > parent->value)
    {
        largest = left;
    }
    if (largest == left)
    {
        if (right_node != NULL && right_node->value > left_node->value)
        {
            largest = right;
        }
    }
    else
    {
        if (right_node != NULL && right_node->value > parent->value)
        {
            largest = right;
        }
    }
    if (largest != index)
    {
        if (largest == left)
        {
            swap_nodes(deque, parent, left_node);
        }
        else
        {
            swap_nodes(deque, parent, right_node);
        }
        heapify(deque, largest, heap_size);
    }
}

int pyramid_sort(Deque *deque, Deque *copied_deque)
{
    int i;
    int size;
    if (deque_copy(copied_deque, deque) == 0)
    {
        return 0;
    }
    size = deque_size(copied_deque);
    if (size < 2) 
    {
        return 1;
    }
    for (i = size / 2 - 1; i >= 0; i--)
    {
        heapify(copied_deque, i, size);
    }
    for (i = size - 1; i >= 0; i--)
    {
        swap_nodes(copied_deque, copied_deque->front, deque_get_node(copied_deque, i));
        heapify(copied_deque, 0, i);
    }
    return 1;
}