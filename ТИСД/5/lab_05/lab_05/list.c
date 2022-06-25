#include "list.h"

node_t* createelem(queue_type c)
{
    node_t *elem = malloc(sizeof(node_t));
    if (elem)
    {
        elem->type = c;
        elem->next = NULL;
    }

    return elem;
}

node_t* pushfront(node_t *head, node_t *elem)
{
    elem->next = head;
    return elem;
}

node_t* popfront(node_t **head)
{
    node_t *cur = NULL;
    if (head)
    {
        cur = *head;
        *head = (*head)->next;
    }
    return cur;
}

node_t* popend(node_t **head)
{
    node_t *end = NULL;
    if (*head != NULL)
    {
        node_t *cur = *head;
        if (cur->next)
        {
            for ( ; cur->next->next; cur = cur->next)
                ;
            end = cur->next;
            cur->next = NULL;
        }
        else
        {
            end = cur;
            *head = NULL;
        }
    }

    return end;
}

void freeall(node_t *head)
{
    node_t *next;
    for ( ; head; head = next)
    {
        next = head->next;
        free(head);
    }
}


node_t *queuelist_push(node_t *queue, queue_type c, node_t **user_memory,
                    int *user_count, node_t **free_memory,
                    int *free_count, int *second_use)
{
    node_t *item = NULL;
    item = createelem(c);
    if (item)
    {
        user_memory[*(user_count++)] = item;
        int sign = 0;
        for (int i = 0; i < *user_count; ++i)
        {
            if (item == free_memory[i])
            {
                free_memory[i] = NULL;
                sign = 1;
            }
            
            if (sign)
                free_memory[i] = free_memory[i + 1];
        }
        if (sign)
        {
            *free_count -= 1;
            *second_use += 1;
        }
        queue = pushfront(queue, item);
    }
    else
    {
        printf("Queue id full!\n");
    }

    return queue;
}
node_t *queuelist_pop(node_t **queue)
{
    node_t *cur = NULL;
    cur = popend(queue);

    if (cur == NULL)
    {
        printf("Queue is empty!\n");
    }

    return cur;
}
void queuelist_print(node_t *queue)
{
    node_t *cur = queue;
    if (queue == NULL)
    {
        printf("Queue is emrty.\n");
    }
    else
    {
        printf("Current queue:\n");
        for ( ; cur; cur = cur->next)
            printf("%c\n", cur->type);
        printf("\n");
    }
}

void sd_list(int n, int interval, times_t t1,
              times_t t2, times_t t3, times_t t4)
{
    node_t *cur;
    node_t *free_memory[MAXLENQUEUE];
    node_t *used_memory[MAXLENQUEUE];
    int free_count = 0;
    int used_count = 0;
    int second_use = 0;

    node_t *queue1 = NULL;
    queue_t que1;
    strcpy(que1.name, "FIRST QUEUE");
    que1.size = sizeof(node_t);
    que1.len= MAXLENQUEUE;
    que1.p_in = NULL;
    que1.p_out = NULL;
    que1.count_req = 0;
    que1.avg_len = 0;
    que1.cur_len = 0;
    que1.in_req = 0;
    que1.out_req = 0;
    que1.sum_time = 0;

    node_t *queue2 = NULL;
    queue_t que2;
    strcpy(que2.name, "SECOND QUEUE");
    que2.size = sizeof(node_t);
    que2.len= MAXLENQUEUE;
    que2.p_in = NULL;
    que2.p_out = NULL;
    que2.count_req = 0;
    que2.avg_len = 0;
    que2.cur_len = 0;
    que2.in_req = 0;
    que2.out_req = 0;
    que2.sum_time = 0;

    int req_in_1 = 0;
    int req_out_1 = 0;
    int req_in_2 = 0;
    int req_out_2 = 0;
    int req_show = 0;
    int out_queue2 = 0;

    double time = 0;
    double time_req1 = 0;
    double time_req2 = 0;
    double time_req_obr = 0;
    double all_time_que1 = 0;
    double all_time_que2 = 0;

    time_t time1 = clock();

    int type_queue = 0;

    while (req_out_1 < n)
    {
        if (que1.cur_len >= MAXLENQUEUE || que2.cur_len >= MAXLENQUEUE)
        {
            printf("Очередь переполнена\n");
            break;
        }

        if (fabs(time_req1) < EPS)
            time_req1 = getime(t1);

        if (fabs(time_req2) < EPS)
            time_req2 = getime(t2);

        if (fabs(time_req_obr) < EPS)
        {
            if (queue1 != NULL)
            {
                time_req_obr = getime(t3);
                type_queue = 1;
                cur = queuelist_pop(&queue1);
                if (cur != NULL)
                {
                    free_memory[free_count++] = cur;
                    free(cur);
                }
                que1.cur_len--;
                que1.avg_len += que1.cur_len;
                que1.count_req++;
                que1.out_req++;
                all_time_que1 += time_req_obr;
            }
            else if (queue2 != NULL)
            {
                time_req_obr = getime(t4);
                type_queue = 2;
                cur = queuelist_pop(&queue2);
                if (cur != NULL)
                {
                    free_memory[free_count++] = cur;
                    free(cur);
                }
                que2.cur_len--;
                que2.avg_len += que2.cur_len;
                que2.count_req++;
                que2.out_req++;
                all_time_que2 += time_req_obr;
            }
        }
        else
        {
            if (type_queue == 2 && queue1 != NULL)
            {
                queue2 = queuelist_push(queue2, '2', used_memory, &used_count, free_memory, &free_count, &second_use);
                que2.cur_len++;
                que2.avg_len += que2.cur_len;
                que2.count_req++;
                que2.in_req++;
                all_time_que2 -= time_req_obr;
                time_req_obr = 0;
                out_queue2++;

                continue;
            }
        }
        
        double timemin = 0;

        if (fabs(time_req_obr) < EPS)
            if (time_req1 - time_req2 < EPS) // найти минимум из 2х
                timemin = time_req1;
            else
                timemin = time_req2;
        else
        {
            if (time_req2 - time_req_obr < EPS) // найти минимум из 3х
                timemin = time_req2;
            else
                timemin = time_req_obr;

            if (time_req1 - timemin < EPS)
                timemin = time_req1;
        }
        
        if (fabs(timemin - time_req_obr) < EPS)
        {
            time_req_obr = 0;
            if (type_queue == 1)
                req_out_1++;
            if (type_queue == 2)
                req_out_2++;
        }

        if (req_out_1 == n)
            break;
        
        if (fabs(timemin - time_req1) < EPS)
        {
            queue1 = queuelist_push(queue1, '1', used_memory, &used_count, free_memory, &free_count, &second_use);
            que1.cur_len++;
            que1.avg_len += que1.cur_len;
            que1.count_req++;
            que1.in_req++;
            req_in_1++;
        }

        if (fabs(timemin - time_req2) < EPS)
        {
            queue2 = queuelist_push(queue2, '2', used_memory, &used_count, free_memory, &free_count, &second_use);
            que2.cur_len++;
            que2.avg_len += que2.cur_len;
            que2.count_req++;
            que2.in_req++;
            req_in_2++;
        }

        time_req1 -= timemin;
        time_req2 -= timemin;

        if (time_req_obr >= timemin)
            time_req_obr -= timemin;
        time += timemin;

        if (req_out_1 % interval == 0 && req_out_1 != req_show)
        {
            req_show = req_out_1;
            printf("Обработано заявок 1го типа: %d\n", req_out_1);
            len_swow(&que1);
            len_swow(&que2);
            printf("\n");
        }
    }
    
    time_t rtime2 = clock();
    long timerealall = rtime2 - time1;

    double avetime_in1 = (t1.max + t1.min) / 2;
    double avetime_out1 = (t3.max + t3.min) / 2;
    double avetime_in2 = (t2.max + t2.min) / 2;

    double total_avetime_in1 = n * avetime_in1;
    double total_avetime_out1 = n * avetime_out1;

    double timemodel;
    if (total_avetime_in1 - total_avetime_out1 > EPS)
        timemodel = total_avetime_in1;
    else
        timemodel = total_avetime_out1;

    double wait_in1 = time / avetime_in1;
//    double wait_in2 = time / avetime_in2;

    double totalwork = all_time_que1 + all_time_que2;
    double timewithoutwork = time - totalwork;

    printf("Общее время моделирования (в усл. ед. в.): %lf\n", time);

    if (fabs(timemodel) > EPS)
    {
        double per_out = fabs(100 * (time - timemodel) / timemodel);
        printf("Погрешность времени моделирования: %lf%% \n\n", per_out);
    }
    else
    {
        printf("Погрешность времени моделирования: 0\n\n");
    }

    printf("Число вошедших в 1 очередь: %d\n", req_in_1);
    printf("Число вышедших из 1 очереди: %d\n", req_out_1);
    printf("Число вошедших во 2 очередь: %d\n", req_in_2);
    printf("Число вышедших из 2 очереди: %d\n", req_out_2);
    printf("Число отмененных заявок для 2 очереди: %d\n\n", out_queue2);
    printf("Время работы (реальное): %ld\n", timerealall);
    printf("Время НЕработы ОА (в усл. ед. в.): %lf\n\n", fabs(timewithoutwork));

    printf("Среднее время обработки заявки 1 очереди: %lf\n", avetime_in1);
    printf("Среднее время обработки заявки 2 очереди: %lf\n\n", avetime_in2);
    

    if (fabs(wait_in1) > EPS)
    {
        double per_in1 = fabs(100 * (req_in_1 - wait_in1) / wait_in1);
        printf("Погрешность ввода 1 очередь: %lf%%\n\n", per_in1);
    }
    else
    {
        printf("Погрешность ввода 1 очереди: 0\n\n");
    }

//    if (fabs(wait_in2) > EPS)
//    {
//        double per_in2 = fabs(100 * (reqin2 - wait_in2) / wait_in2);
//        printf("Погрешность ввода 2 очередь: %lf%%\n", per_in2);
//    }
//    else
//    {
//        printf("Погрешность ввода 2 очереди: 0\n");
//    }
    
    
    int flag;
    printf("ПОКАЗАТЬ ИНФОРМАЦИЮ О ФРАГМЕНТАЦИИ ПАМЯТИ?\n"
           "1 - да | 0 - нет\n");
    int rc = scanf("%d", &flag);
    if (rc != 1 || !(flag == 1 || flag == 0))
    {
        printf("НЕКОРРЕКТНЫЙ ВВОД\n");
        free(queue1);
        free(queue2);
        return;
    }
    
    if (flag == 1)
    {
        printf("Количество повторно используемных адресов: %d\n", second_use);
        printf("Количество неиспользуемых адресов: %d\n", free_count);
        printf("Неиспользуемые адреса:\n");
        for (int i = 0; i < ((15 < free_count) ? 15 : free_count); i++)
            printf("%p\n", (void *)free_memory[i]);
        if (free_count > 15)
            printf("...\n");
        fflush(stdin);
    }
    
    freeall(queue1);
    freeall(queue2);
    fflush(stdin);
}

