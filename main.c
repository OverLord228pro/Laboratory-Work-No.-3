#include <stdio.h>
#include "deque.h"
#include "sort.h"
#include <locale.h>
#include <float.h>
#include <string.h>
#include "input.h"

int repeat(void)
{
    char answer[maxx];
    short int count_inputs = 0;
    while (1)
    {
        if (count_inputs >= max_inputs)
        {
            printf("Слишком много ошибок ввода, попробуйте заново запустить программу.\n");
            return 0;
        }
        printf("Хотите повторить? (y/n): ");
        count_inputs++;
        if (fgets(answer, sizeof(answer), stdin) == NULL)
        {
            printf("Ошибка: ввод завершён или произошла ошибка чтения.\n");
            return 0;
        }

        if (strchr(answer, '\n') == NULL)
        {
            read_rest_of_input();
            printf("Ошибка: слишком длинный ввод.\n");
            continue;
        }

        answer[strcspn(answer, "\n")] = '\0';

        if (strcmp(answer, "y") == 0 || strcmp(answer, "Y") == 0)
        {
            return 1;
        }
        else if (strcmp(answer, "n") == 0 || strcmp(answer, "N") == 0)
        {
            printf("Программа завершена.\n");
            return 0;
        }
        else
        {
            printf("Ошибка: введен некорректный ответ.\n");
        }
    }
}

int main(void)
{
    Deque deque;
    Deque copied_deque;
    char line[maxx];
    short int result;
    short int mode;
    setlocale(LC_ALL, "Russian");
    while(1)
    {
        printf("Выберите действие:(1 — Ввести числа самостоятельно, 2 — Посмотреть готовые результаты из файла):\n");
        if (fgets(line, sizeof(line), stdin) == NULL)
        {
            printf("Ошибка: ввод завершён или произошла ошибка чтения.\n");
            return 0;
        }

        if (strchr(line, '\n') == NULL)
        {
            read_rest_of_input();
            printf("Ошибка: слишком длинный ввод. Введите 1 или 2.\n");
            if (repeat() == 0)
            {
                return 0;
            }
            continue;
        }

        line[strcspn(line, "\n")] = '\0';

        if (strcmp(line, "1") == 0)
        {
            mode = 1;
        }

        else if (strcmp(line, "2") == 0)
        {
            mode = 2;
        }
        else
        {
            printf("Ошибка: некорректный выбор. Введите 1 или 2.\n");
            if (repeat() == 0)
            {
                return 0;
            }
            continue;
        }

        if (mode == 1)
        {
            printf("Введите числа через пробел(длина строки не более 1000 символов).\n");
            printf("Разрешены целые, дробные и отрицательные числа, модуль которых не прeвышает %.16e.\n", DBL_MAX);
            printf("Числа: ");
            if (fgets(line, sizeof(line), stdin) == NULL)
            {
                printf("Ошибка: ввод завершён или произошла ошибка чтения.\n");
                return 0;
            }
            if (strchr(line, '\n') == NULL)
            {
                read_rest_of_input();
                printf("Ошибка: слишком длинный ввод. Допускается не более 1000 символов.\n");
                if (repeat() == 0)
                {
                    return 0;
                }
                continue;
            }
            deque_init(&deque);
            result = parse_numbers(&deque, line);
            if (result == 0)
            {
                printf("Ошибка: некорректный ввод чисел.\n");
                if (repeat() == 0)
                {
                    return 0;
                }
                continue;
            }
            else if (result == -1)
            {
                printf("Ошибка: недостаточно памяти для хранения чисел.\n");
                if (repeat() == 0)
                {
                    return 0;
                }
                return 0;
            }
            else
            {
                printf("Введенные числа: ");
                deque_print(&deque);

                deque_init(&copied_deque);

                if (bubble_sort(&deque, &copied_deque) == 1)
                {
                    printf("Результат сортировки пузырьком: ");
                    deque_print(&copied_deque);
                }
                else
                {
                    printf("Ошибка: не удалось создать копию для сортировки.\n");
                    if (repeat() == 0)
                    {
                        return 0;
                    }
                }

                deque_clear(&copied_deque);
                deque_init(&copied_deque);

                if (pyramid_sort(&deque, &copied_deque) == 1)
                {
                    printf("Результат пирамидальной сортировки: ");
                    deque_print(&copied_deque);
                }
                else
                {
                    printf("Ошибка: не удалось создать копию для сортировки.\n");
                    if (repeat() == 0)
                    {
                        return 0;
                    }
                }

                deque_clear(&copied_deque);
            }
            deque_clear(&deque);
            
        }
        else
        {
            printf("Будут использованы готовые результаты из файла.\n");
        }

    }
    return 0;
}