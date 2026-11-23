#include "input.h"
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>


void read_rest_of_input(void)
{
    char buffer[maxx];
    while (fgets(buffer, sizeof buffer, stdin) != NULL)
    {
        if (strchr(buffer, '\n') != NULL)
        {
            break;
        }
    }
}

int parse_numbers(Deque *deque, char *line)
{
    char *current;
    char *end;
    int value;

    if (deque == NULL || line == NULL)
    {
        return 0;
    }

    current = line;

    while (*current != '\0')
    {
        while (isspace((unsigned char)*current))
        {
            current++;
        }

        if (*current == '\0')
        {
            break;
        }

        errno = 0;
        value = (int)strtol(current, &end, 10);

        if (end == current || errno == ERANGE)
        {
            deque_clear(deque);
            return 0;
        }

        if (*end != '\0' && !isspace((unsigned char)*end))
        {
            deque_clear(deque);
            return 0;
        }

        if (deque_push_back(deque, value) == 0)
        {
            deque_clear(deque);
            return -1;
        }

        current = end;
    }

    if (deque->front != NULL)
    {
        return 1;
    }
    return 0;
}

