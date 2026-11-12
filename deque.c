#include "deque.h"
#include <stdlib.h>
#include <stdio.h>

void deque_init(Deque *deque)
{
    deque->front = NULL;
    deque->back = NULL;
    deque->size = 0;
}

int deque_push_back(Deque *deque, double value)
{
    short int attempt = 0;
    DequeNode *node;

    for (attempt = 0; attempt < 3; attempt++) 
    {
        node = malloc(sizeof(DequeNode));

        if (node != NULL) 
        {
            break;
        }
    }

    if (node == NULL) 
    {
        return 0;
    }

    node->value = value;
    node->prev = deque->back;
    node->next = NULL;

    if (deque->back != NULL) 
    {
        deque->back->next = node;
    } 
    else 
    {
        deque->front = node;
    }

    deque->back = node;
    deque->size++;
    return 1;
}

int deque_push_front(Deque *deque, double value)
{
    short int attempt = 0;
    DequeNode *node;
    
    for (attempt = 0; attempt < 3; attempt++) 
    {
        node = malloc(sizeof(DequeNode));

        if (node != NULL) 
        {
            break;
        }
    }

    if (node == NULL) 
    {
        return 0;
    }

    node->value = value;
    node->prev = NULL;
    node->next = deque->front;

    if (deque->front != NULL) 
    {
        deque->front->prev = node;
    } 
    else 
    {
        deque->back = node;
    }

    deque->front = node;
    deque->size++;
    return 1;
}

void deque_clear(Deque *deque)
{
    DequeNode *node = deque->front;
    DequeNode *next;

    while (node != NULL) 
    {
        next = node->next;
        free(node);
        node = next;
    }

    deque_init(deque);
}

int deque_pop_front(Deque *deque, double *value)
{
    DequeNode *node;
    if (deque->front == NULL) 
    {
        return 0;
    }
    *value = deque->front->value;
    node = deque->front;
    deque->front = deque->front->next;

    if (deque->front != NULL) 
    {
        deque->front->prev = NULL;
    } 
    else 
    {
        deque->back = NULL;
    }

    free(node);
    deque->size--;
    return 1;
}

int deque_pop_back(Deque *deque, double *value)
{
    DequeNode *node;

    if (deque->back == NULL)
    {
        return 0;
    }

    *value = deque->back->value;
    node = deque->back;
    deque->back = deque->back->prev;

    if (deque->back != NULL)
    {
        deque->back->next = NULL;
    }

    else
    {
        deque->front = NULL;
    }

    free(node);
    deque->size--;
    return 1;
}

int deque_set(Deque *deque, int pos, double value)
{
    DequeNode *node;
    int i;

    if (pos < 0 || pos >= deque->size) 
    {
        return 0;
    }

    node = deque->front;

    for (i = 0; i < pos; i++) 
    {
        node = node->next;
    }

    node->value = value;

    return 1;
}

void deque_print(Deque *deque)
{
    DequeNode *node;

    node = deque->front;

    while (node != NULL) 
    {
        printf("%f ", node->value);
        node = node->next;
    }

    printf("\n");
}