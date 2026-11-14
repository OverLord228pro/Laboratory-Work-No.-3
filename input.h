#ifndef INPUT_H
#define INPUT_H

#include "deque.h"
#define max_inputs 20
#define maxx 1002

int parse_numbers(Deque *deque, char *line);
void replace_commas(char *line);
void read_rest_of_input(void);

#endif
