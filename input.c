#include "input.h"
#include <stdio.h>
#include <math.h>
#include <errno.h>

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

void replace_commas(char *line)
{
    if (line == NULL)
    {
        return;
    }

    while (*line != '\0')
    {
        if (*line == ',')
        {
            *line = '.';
        }
        line++;
    }
}

int parse_numbers(Deque *deque, char *line)
{
    char *current;
    char *end;
    double value;

    if (deque == NULL || line == NULL)
    {
        return 0;
    }

    replace_commas(line);

    current = line;

    while (*current != '\0')
    {
        while (*current == ' ')
        {
            current++;
        }

        if (*current == '\0')
        {
            break;
        }

        errno = 0;
        value = strtod(current, &end);

        if (end == current || errno == ERANGE || !isfinite(value))
        {
            deque_clear(deque);
            return 0;
        }

        if (*end != '\0' && *end != ' ' && *end != '\n')
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

    if (deque_size(deque) > 0)
    {
        return 1;
    }
    return 0;
}

