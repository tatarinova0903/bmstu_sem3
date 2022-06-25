#include "queue.h"
#include "io.h"
#include "array.h"
#include "time_mem.h"
#include "list.h"

int main()
{
    int n = 1000;
    int interval = 100;
    times_t t1 = { 1, 5 };
    times_t t2 = { 0, 3 };
    times_t t3 = { 0, 4 };
    times_t t4 = { 0, 1 };
    print_menu();
    
    int num_command = -1;

    while (num_command != 0)
    {
        printf("%s","ВАШ ВЫБОР: ");
        if (check_number(&num_command, 0, 5) != EXIT_SUCCESS)
        {
            fflush(stdin);
            printf("НЕКОРРЕКТНЫЙ ВВОД\n");
            print_menu();
        }
        else
        {
            fflush(stdin);
            switch (num_command)
            {
                case 1:
                    printf("МАССИВ:\n");
                    sd_array(n, interval, t1, t2, t3, t4);

                    break;
                case 2:
                    printf("СПИСОК:");
                    fflush(stdin);
                    sd_list(n, interval, t1, t2, t3, t4);
                    fflush(stdin);
                    break;
                case 3:
                    printf("ИЗМЕНЕНИЕ ВРЕМЯ\n");
                    double l, r;
                    int c;
                    printf("1: min = %lf; max = %lf\n", t1.min, t1.max);
                    printf("2: min = %lf; max = %lf\n", t2.min, t2.max);
                    printf("3: min = %lf; max = %lf\n", t3.min, t3.max);
                    printf("4: min = %lf; max = %lf\n", t4.min, t4.max);
                    printf("КАКОЙ ИНТЕРВАЛ ИЗМЕНИТЬ?\n");
                    if (check_number(&c, 1, 4) != EXIT_SUCCESS)
                    {
                        fflush(stdin);
                        printf("НЕКОРРЕКТНЫЙ ВВОД\n");
                        break;
                    }
                    else
                    {
                        printf("ВВЕДИТЕ ПРАВУЮ И ЛЕВУЮ ГРАНИЦЫ: ");
                        int rc = scanf("%lf", &l);
                        if (rc != 1)
                        {
                            printf("НЕКОРРЕКТНЫЙ ВВОД\n");
                            break;
                        }
                        rc = scanf("%lf", &r);
                        if (rc != 1)
                        {
                            printf("НЕКОРРЕКТНЫЙ ВВОД\n");
                            break;
                        }
                        if (c == 1)
                        {
                            t1.min = l;
                            t1.max = r;
                        }
                        if (c == 2)
                        {
                            t2.min = l;
                            t2.max = r;
                        }
                        if (c == 3)
                        {
                            t3.min = l;
                            t3.max = r;
                        }
                        if (c == 4)
                        {
                            t4.min = l;
                            t4.max = r;
                        }
                        printf("ИТОГ:\n");
                        printf("1: min = %lf; max = %lf\n", t1.min, t1.max);
                        printf("2: min = %lf; max = %lf\n", t2.min, t2.max);
                        printf("3: min = %lf; max = %lf\n", t3.min, t3.max);
                        printf("4: min = %lf; max = %lf\n", t4.min, t4.max);
                    }
                    break;
                case 4:
                    printf("Вывод сравнений по времени\n");
                    check_memory_time();
                    break;
                case 5:
                    print_menu();
                    break;
            }
        }
    }
    return EXIT_SUCCESS;
}
