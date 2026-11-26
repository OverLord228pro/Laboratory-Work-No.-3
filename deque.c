#include "deque.h"
#include <stdlib.h>
#include <stdio.h>

void deque_init(Deque *deque)
{
    deque->front = NULL;
    deque->back = NULL;
}

Deque_node *deque_detach_front(Deque *deque)
{
    Deque_node *node;

    if (deque->front == NULL)
    {
        return NULL;
    }

    node = deque->front;
    deque->front = node->next;

    if (deque->front != NULL)
    {
        deque->front->prev = NULL;
    }
    else
    {
        deque->back = NULL;
    }

    node->next = NULL;
    return node;
}

Deque_node *deque_detach_back(Deque *deque)
{
    Deque_node *node;

    if (deque->back == NULL)
    {
        return NULL;
    }

    node = deque->back;
    deque->back = node->prev;

    if (deque->back != NULL)
    {
        deque->back->next = NULL;
    }
    else
    {
        deque->front = NULL;
    }

    node->prev = NULL;
    return node;
}

int deque_attach_front(Deque *deque, Deque_node *node)
{
    if (node == NULL)
    {
        return 0;
    }

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
    return 1;
}

int deque_attach_back(Deque *deque, Deque_node *node)
{
    if (node == NULL)
    {
        return 0;
    }

    node->next = NULL;
    node->prev = deque->back;

    if (deque->back != NULL)
    {
        deque->back->next = node;
    }
    else
    {
        deque->front = node;
    }

    deque->back = node;
    return 1;
}

short int deque_push_back(Deque *deque, int value)
{
    short int attempt = 0;
    Deque_node *node;

    for (attempt = 0; attempt < 3; attempt++) 
    {
        node = malloc(sizeof(Deque_node));

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
    return 1;
}

short int deque_push_front(Deque *deque, int value)
{
    short int attempt = 0;
    Deque_node *node;
    
    for (attempt = 0; attempt < 3; attempt++) 
    {
        node = malloc(sizeof(Deque_node));

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
    return 1;
}

short int deque_pop_front(Deque *deque, int *value)
{
    Deque_node *node;

    if (deque == NULL)
    {
        return 0;
    }

    node = deque_detach_front(deque);
    if (node == NULL)
    {
        return 0;
    }

    if (value != NULL)
    {
        *value = node->value;
    }

    free(node);
    return 1;
}

short int deque_pop_back(Deque *deque, int *value)
{
    Deque_node *node;

    if (deque == NULL)
    {
        return 0;
    }

    node = deque_detach_back(deque);
    if (node == NULL)
    {
        return 0;
    }

    if (value != NULL)
    {
        *value = node->value;
    }

    free(node);
    return 1;
}

void deque_clear(Deque *deque)
{
    int value;
    while (deque->front != NULL)
    {
        deque_pop_front(deque, &value);
    }
}

int deque_size(Deque *deque)
{
    Deque_node *last;
    Deque_node *node = NULL;
    int size = 0;

    if (deque == NULL)
    {
        return -1;
    }

    last = deque->back;

    while (node != last)
    {
        node = deque_detach_front(deque);
        deque_attach_back(deque, node);
        size++;
    }

    return size;
}

short int deque_change_node(Deque *deque, int pos, int value)
{
    Deque_node *last;
    Deque_node *node = NULL;
    int i;

    if (deque == NULL || pos < 0)
    {
        return 0;
    }

    last = deque->back;

    for (i = 0; node != last; i++)
    {
        node = deque_detach_front(deque);

        if (i == pos)
        {
            node->value = value;
        }

        deque_attach_back(deque, node);
    }
    if (pos < i)
    {
        return 1;
    }
    return 0;
}

void deque_print(Deque *deque)
{
    Deque_node *last = deque->back;
    Deque_node *node = NULL;

    while (node != last)
    {
        node = deque_detach_front(deque);
        printf("%d ", node->value);
        deque_attach_back(deque, node);
    }

    printf("\n");
}

short int deque_copy(Deque *copied_deque, Deque *deque)
{
    Deque_node *last;
    Deque_node *node = NULL;
    short int flag = 1;

    if (copied_deque == NULL || deque == NULL || copied_deque == deque || copied_deque->front != NULL)
    {
        return 0;
    }

    last = deque->back;

    while (node != last)
    {
        node = deque_detach_front(deque);

        if (flag && deque_push_back(copied_deque, node->value) == 0)
        {
            flag = 0;
        }

        deque_attach_back(deque, node);
    }

    if (flag == 0)
    {
        deque_clear(copied_deque);
    }

    return flag;
}