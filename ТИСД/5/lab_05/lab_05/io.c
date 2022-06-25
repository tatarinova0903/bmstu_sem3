#include "io.h"

void print_menu(void)
{
    printf("1 - Моделирование и характеристика для очереди в виде массива.\n"
           "2 - Моделирование и характеристика для очереди в виде списка.\n"
           "3 - Изменить время обработки заявки.\n"
           "4 - Вывод сравнения времени при выполнении операций.\n\n"

           "0 - Выход из программы.\n\n"
           );
}

int check_number(int *const number, const int l, const int r)
{
    char num[3];
    char *n;
    fflush(stdin);
    n = fgets(num, 4, stdin);
    if (n == NULL || num[0] == '\n')
        return DONT_INT_NUM_CHOICE;
    num[strlen(num) - 1] = '\0';
    *number = (int)atoi(num);

    if (*number < l || *number > r)
    {
        return INV_NUM_CHOICE;
    }

    return EXIT_SUCCESS;
}

void len_swow(queue_t *queue)
{
    printf("Текущая длина %s: %d\n", queue->name, queue->cur_len);
    if (queue->count_req > 0)
    {
        printf("Средняя длина %s: %lf\n", queue->name,
                (double)queue->avg_len / (double)queue->count_req);
    }
}
