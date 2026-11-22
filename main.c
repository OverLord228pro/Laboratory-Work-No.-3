#include <stdio.h>
#include "deque.h"
#include "sort.h"
#include <locale.h>
#include <string.h>
#include "input.h"
#include "file.h"
#include <stdlib.h>
#include <time.h>
#include <limits.h>

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

int main(int argc, char *argv[])
{
    Deque deque;
    Deque copied_deque;
    char line[maxx];
    short int result;
    short int file_ok;
    FILE *file;
    double bubble_seconds;
    double pyramid_seconds;
    int i;
    short int compare_mode = 0;
    setlocale(LC_ALL, "Russian");

    for (i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "--compare") == 0)
        {
            compare_mode = 1;
            break;
        }
        if (strcmp(argv[i], "--file") == 0)
        {
            if (i + 1 >= argc || argv[i + 1][0] == '\0' ||
                argv[i + 1][0] == '-')
            {
                printf("Ошибка: после --file укажи имя файла.\n");
                return 1;
            }

            result = print_file(argv[i + 1]);

            if (result == 0)
            {
                printf("Не удалось прочитать файл: %s\n", argv[i + 1]);
                return 1;
            }

            return 0;
        }
    }

    if (argc != 1 && compare_mode == 0)
    {
        printf("Запуск: a.exe, a.exe --file имя_файла или a.exe --compare\n");
        return 1;
    }

    if (compare_mode == 1)
    {
        
        srand((unsigned int)time(NULL));
        if (!generate_file("input_500.txt", 500) || !generate_file("input_1000.txt", 1000) ||
            !generate_file("input_3000.txt", 3000) || !generate_file("input_5000.txt", 5000) ||
            !generate_file("input_7000.txt", 7000) || !generate_file("input_9000.txt", 9000) ||
            !generate_file("input_10000.txt", 10000))
        {
            printf("Ошибка создания тестовых файлов.\n");
            if (repeat() == 0)
            {
                return 0;
            }
        }

        while (1)
        {
            result = compare_files();

            if (result)
            {
                printf("Измерения сохранены в times.txt.\n");
            }
            else
            {
                printf("Ошибка обработки файлов или записи измерений.\n");
            }

            if (repeat() == 0)
            {
                return result == 0;
            }
        }
    }

    if (argc == 3)
    {
        while (1)
        {
            result = print_file(argv[2]);

            if (result == 0)
            {
                printf("Ошибка при работе с файлом.\n");
            }
            if (result == 0)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
    }

    while(1)
    {
        printf("Введите числа через пробел(длина строки не более 1000 символов).\n");
        printf("Разрешены целые числа от %d до %d.\n", INT_MIN, INT_MAX);
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
        }
        else if (result == -1)
        {
            printf("Ошибка: недостаточно памяти для хранения чисел.\n");
        }
        else
        {
            printf("Введенные числа: ");
            deque_print(&deque);
            file_ok = 1;
            file = fopen("results.txt", "w");

            if (file == NULL)
            {
                printf("Ошибка: не удалось открыть файл для записи.\n");
                file_ok = 0;
            }
            else
            {
                if (fprintf(file, "Изначальный дек\n") < 0 || write_deque(file, &deque) == 0)
                {
                    printf("Ошибка записи исходной последовательности.\n");
                    file_ok = 0;
                }

                if (fclose(file) != 0)
                {
                    printf("Ошибка закрытия файла.\n");
                    file_ok = 0;
                }
            }

            deque_init(&copied_deque);

            if (bubble_sort(&deque, &copied_deque, &bubble_seconds) == 1)
            {
                printf("Результат сортировки пузырьком: ");
                deque_print(&copied_deque);
                if (file_ok)
                {
                    file = fopen("results.txt", "a");

                    if (file == NULL)
                    {
                        printf("Ошибка открытия файла для дописывания.\n");
                        file_ok = 0;
                    }
                    else
                    {
                        if (fprintf(file, "Сортировка пузырьком\n") < 0 || write_deque(file, &copied_deque) == 0)
                        {
                            printf("Ошибка записи результата сортировки.\n");
                            file_ok = 0;
                        }

                        if (fclose(file) != 0)
                        {
                            printf("Ошибка закрытия файла.\n");
                            file_ok = 0;
                        }
                    }
                }
            }
            else
            {
                printf("Ошибка: не удалось создать копию для сортировки пузырьком.\n");
                file_ok = 0;
            }

            deque_clear(&copied_deque);

            if (pyramid_sort(&deque, &copied_deque, &pyramid_seconds) == 1)
            {
                printf("Результат пирамидальной сортировки: ");
                deque_print(&copied_deque);
                if (file_ok)
                {
                    file = fopen("results.txt", "a");

                    if (file == NULL)
                    {
                        printf("Ошибка открытия файла для дописывания.\n");
                        file_ok = 0;
                    }
                    else
                    {
                        if (fprintf(file, "Пирамидальная сортировка\n") < 0 ||
                            write_deque(file, &copied_deque) == 0)
                        {
                            printf("Ошибка записи результата сортировки.\n");
                            file_ok = 0;
                        }

                        if (fclose(file) != 0)
                        {
                            printf("Ошибка закрытия файла.\n");
                            file_ok = 0;
                        }
                    }
                }
            }
            else
            {
                printf("Ошибка: не удалось создать копию для пирамидальной сортировки.\n");
                file_ok = 0;
            }
            
            deque_clear(&copied_deque);
        }
        deque_clear(&deque);
        if (repeat() == 0)
        {
            return 0;
        }
    }
}