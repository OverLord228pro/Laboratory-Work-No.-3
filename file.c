#include "file.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "sort.h"
#include <locale.h>

int write_deque(FILE *file, Deque *deque)
{
    Deque_node *current;

    if (file == NULL || deque == NULL)
    {
        return 0;
    }

    current = deque->front;

    while (current != NULL)
    {
        if (fprintf(file, "%d ", current->value) < 0)
        {
            return 0;
        }

        current = current->next;
    }

    if (fprintf(file, "\n") < 0)
    {
        return 0;
    }

    return 1;
}

int print_file(char *filename)
{
    FILE *file;
    char buffer[maxx];

    if (filename == NULL)
    {
        return 0;
    }

    file = fopen(filename, "r");

    if (file == NULL)
    {
        return 0;
    }


    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        if (printf("%s", buffer) < 0)
        {
            fclose(file);
            return 0;
        }
    }

    if (fclose(file) != 0)
    {
        return 0;
    }

    return 1;
}


int generate_file(char *filename, int count)
{
    FILE *file;
    int i;

    if (filename == NULL)
    {
        return 0;
    }

    file = fopen(filename, "w");

    if (file == NULL)
    {
        return 0;
    }

    for (i = 0; i < count; i++)
    {
        if (fprintf(file, "%d\n", min + rand() % (max - min + 1)) < 0)
        {
            fclose(file);
            return 0;
        }
    }

    if (fclose(file) != 0)
    {
        return 0;
    }

    return 1;
}

int read_deque(char *filename, Deque *deque)
{
    FILE *file;
    char line[maxx];
    char *end;
    int value;

    file = fopen(filename, "r");

    if (file == NULL)
    {
        return 0;
    }

    while (fgets(line, sizeof(line), file) != NULL)
    {
        line[strcspn(line, "\n")] = '\0';

        value = (int)strtol(line, &end, base);

        if (end == line || *end != '\0' || deque_push_back(deque, value) == 0)
        {
            fclose(file);
            deque_clear(deque);
            return 0;
        }
    }

    if (fclose(file) != 0)
    {
        return 0;
    }
    return 1;
}

int compare_file(char *filename, FILE *table)
{
    Deque deque;
    Deque copied_deque;
    int count;
    short int result;
    double bubble_seconds;
    double pyramid_seconds;
    double experimental_seconds;

    deque_init(&deque);
    deque_init(&copied_deque);

    printf("\nОбработка файла %s\n", filename);

    result = read_deque(filename, &deque);
    count = deque_size(&deque);

    if (result == 1)
    {
        result = bubble_sort(&deque, &copied_deque, &bubble_seconds);
    }

    deque_clear(&copied_deque);

    if (result == 1)
    {
        result = pyramid_sort(&deque, &copied_deque, &pyramid_seconds);
    }

    deque_clear(&copied_deque);

    if (result == 1)
    {
        result = experimental_sort(&deque, &copied_deque, &experimental_seconds);
    }

    if (result == 1)
    {
        printf("\nКоличество чисел: %d\n", count);
        printf("Пузырьковая: %.20f с.\n", bubble_seconds);
        printf("Пирамидальная: %.20f с.\n", pyramid_seconds);
        printf("Экспериментальная: %.20f с.\n", experimental_seconds);

        if (fprintf(table, "%d %.20f %.20f %.20f\n", count, bubble_seconds, pyramid_seconds, experimental_seconds) < 0)
        {
            result = 0;
        }
        else
        {
            result = 1;
        }
    }

    deque_clear(&copied_deque);
    deque_clear(&deque);

    return result;
}

int compare_files(void)
{
    FILE *table;
    short int result;
    setlocale(LC_ALL, "Russian");

    table = fopen("times.txt", "w");

    if (table == NULL)
    {
        return 0;
    }

    if (fprintf(table, "количество_чисел пузырьковая пирамидальная экспериментальная\n") < 0)
    {
        fclose(table);
        return 0;
    }

    result = compare_file("input_1000.txt", table) &&
            compare_file("input_2000.txt", table) &&
            compare_file("input_3000.txt", table) &&
            compare_file("input_4000.txt", table) &&
            compare_file("input_5000.txt", table);
            compare_file("input_6000.txt", table) &&
            compare_file("input_7000.txt", table) &&
            compare_file("input_8000.txt", table) &&
            compare_file("input_9000.txt", table) &&
            compare_file("input_10000.txt", table);

    if (fclose(table) != 0)
    {
        result = 0;
    }

    return result;
}