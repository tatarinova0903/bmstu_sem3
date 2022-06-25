#include "array.h"
#include "time.h"
#include "io.h"

void queuearray_push(queue_t *queue, char c_elem)
{
    char *p_in = queue->p_in;
    
    if (queue->p_in == queue->p_out &&
        *((char*)queue->p_in) != '\0')
    {
        printf("ATTENTION!\nQueue is full!\n");
    }
    else
    {
        *((char*)queue->p_in) = c_elem;
        if (queue->p_in != queue->up)
        {
            queue->p_in = p_in + 1;
        }
        else
        {
            queue->p_in = queue->low;
        }
    }
}

char queuearray_pop(queue_t *queue)
{
    char *p_out = queue->p_out;
    char ps = '\0';

    if (queue->p_in == queue->p_out &&
        *((char*)queue->p_in) == '\0')
    {
        printf("ATTENTION!\nQueue is empty!\n");
    }
    else
    {
        ps = *((char*)queue->p_out);
        *((char*)queue->p_out) = '\0';
        if (queue->p_out != queue->up)
        {
            queue->p_out = p_out + 1;
        }
        else
        {
            queue->p_out = queue->low;
        }
    }
    return ps;
}
void queuearray_print(queue_t *queue)
{
    if (queue->p_out == queue->p_in &&
        *((char*)queue->p_in) == '\0')
    {
        printf("ATTENTION!\nQueue is empty!\n");
    }
    else
    {
        char *begin = queue->p_out;
        char *end = queue->p_in;
        while (begin != end)
        {
            printf("%c\n", *begin);
            if (begin != queue->up)
            {
                begin++;
            }
            else
            {
                begin = queue->low;
            }
        }
    }
}

void sd_array(int n, int interval, times_t t1,
              times_t t2, times_t t3, times_t t4)
{
    // Создание 1 очереди
    queue_t queue1;
    strcpy(queue1.name, "FIRST QUEUE");
    queue1.len = MAXLENQUEUE;
    queue1.size = sizeof(queue_type);
    char *quearr1;
    quearr1 = (queue_type *)malloc(queue1.len * sizeof(queue_type));
    queue1.low = quearr1;
    queue1.up = quearr1 + queue1.len;
    queue1.p_in = quearr1;
    queue1.p_out = quearr1;
    for (int i = 0; i < queue1.len; i++)
        quearr1[i] = '\0';
    queue1.out_req = 0;
    queue1.in_req = 0;
    queue1.count_req = 0;
    queue1.avg_len = 0;
    queue1.sum_time = 0;
    queue1.cur_len = 0;

    // Создание 2 очереди
    queue_t queue2;
    strcpy(queue2.name, "SECOND QUEUE");
    queue2.len = MAXLENQUEUE;
    queue2.size = sizeof(queue_type);
    char *quearr2;
    quearr2 = (queue_type *)malloc(queue2.len * sizeof(queue_type));
    queue2.low = quearr2;
    queue2.up = quearr2 + queue2.len;
    queue2.p_in = quearr2;
    queue2.p_out = quearr2;
    for (int i = 0; i < queue2.len; i++)
        quearr2[i] = '\0';
    queue2.out_req = 0;
    queue2.in_req = 0;
    queue2.count_req = 0;
    queue2.avg_len = 0;
    queue2.sum_time = 0;
    queue2.cur_len = 0;
    
    int out_queue2 = 0; // число отмененных заявок

    int req_in_1 = 0;
    int req_out_1 = 0;
    int req_in2 = 0;
    int req_out2 = 0;
    int req_show = 0;

    double time = 0;
    double time_req1 = 0; // поступление в 1 очередь
    double time_req2 = 0; // поступление во 2 очередь
    double time_req_obr = 0; // обработка
    double all_time_que1 = 0;
    double all_time_que2 = 0;

    time_t time1 = clock();

    int type_queue = 0;

    while (req_out_1 < n + 1)
    {
        if ((queue1.p_in == queue1.p_out && *((char*)queue1.p_in) != '\0') ||
            (queue2.p_in == queue2.p_out && *((char*)queue2.p_in) != '\0'))
        {
            printf("Очередь заполнена.\n");
            break;
        }

        if (fabs(time_req1) < EPS)
            time_req1 = getime(t1);

        if (fabs(time_req2) < EPS)
            time_req2 = getime(t2);

        if (fabs(time_req_obr) < EPS)
        {
            if (!(queue1.p_in == queue1.p_out && *((char*)queue1.p_in) == '\0'))
            {
                time_req_obr = getime(t3);
                type_queue = 1;
                queuearray_pop(&queue1);//, quearr1);
                queue1.cur_len--;
                queue1.avg_len += queue1.cur_len;
                queue1.count_req++;
                queue1.out_req++;
                all_time_que1 += time_req_obr;
            }
            else if (!(queue2.p_in == queue2.p_out && *((char*)queue2.p_in) == '\0'))
            {
                time_req_obr = getime(t4);
                type_queue = 2;
                queuearray_pop(&queue2);//, quearr2);
                queue2.cur_len--;
                queue2.avg_len += queue2.cur_len;
                queue2.count_req++;
                queue2.out_req++;
                all_time_que2 += time_req_obr;
            }
        }
        else if (type_queue == 2 && !(queue2.p_in == queue2.p_out && *((char*)queue2.p_in) == '\0'))
        {
            queuearray_push(&queue2, '2');
            queue2.cur_len++;
            queue2.avg_len += queue2.cur_len;
            queue2.count_req++;
            queue2.in_req++;
            all_time_que2 -= time_req_obr;
            time_req_obr = 0;
            out_queue2++;
            continue;
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
                req_out2++;
        }

        if (req_out_1 == n)
            break;
        
        if (fabs(timemin - time_req1) < EPS)
        {
            queuearray_push(&queue1, '1');
            queue1.cur_len++;
            queue1.avg_len += queue1.cur_len;
            queue1.count_req++;
            queue1.in_req++;
            req_in_1++;
        }

        if (fabs(timemin - time_req2) < EPS)
        {
            queuearray_push(&queue2, '2');
            queue2.cur_len++;
            queue2.avg_len += queue2.cur_len;
            queue2.count_req++;
            queue2.in_req++;
            req_in2++;
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
            len_swow(&queue1);
            len_swow(&queue2);
            printf("\n");
        }
    }
    
    time_t rtime2 = clock();
    long timerealall = (rtime2 - time1) * 3;

    double avetime_in1 = (t1.max + t1.min) / 2;
    double avetime_out1 = (t3.max + t3.min) / 2;
    double avetime_in2 = (t2.max + t2.min) / 2;

    double total_avetime_in1 = n * avetime_in1;
    double total_avetime_out1 = n * avetime_out1;

    double totalwork = all_time_que1 + all_time_que2;
    double timewithoutwork = time - totalwork;

    double timemodel;
    if (total_avetime_in1 - total_avetime_out1 > EPS)
        timemodel = total_avetime_in1;
    else
        timemodel = total_avetime_out1;

    double wait_in1 = time / avetime_in1;
//    double wait_in2 = time / avetime_in2;
    
//    double wait_out1 = time / avetime_out1;

    printf("Общее время моделирования (в усл. ед. в.): %lf\n", time);

    if (fabs(timemodel) > EPS)
    {
        double per_out = fabs(100 * (time - timemodel) / timemodel);
        printf("Погрешность работы ОА: %lf%% \n\n", per_out);
    }
    else
    {
        printf("Погрешность моделирования: 0\n\n");
    }
    printf("Среднее время обработки заявки 1 очереди: %lf\n", avetime_in1);
    printf("Среднее время обработки заявки 2 очереди: %lf\n\n", avetime_in2);
    printf("Число вошедших в 1 очередь: %d\n", req_in_1);
    printf("Число вышедших из 1 очереди: %d\n", req_out_1);
    printf("Число вошедших во 2 очередь: %d\n", req_in2);
    printf("Число вышедших из 2 очереди: %d\n", req_out2);
    printf("Число отмененных заявок для 2 очереди: %d\n\n", out_queue2);
    printf("Время работы (реальное): %ld\n", timerealall);
    printf("Время НЕработы ОА (в усл. ед. в.): %lf\n\n", fabs(timewithoutwork));

    if (fabs(wait_in1) > EPS)
    {
        double per_in1 = fabs(100 * (req_in_1 - wait_in1) / wait_in1);
        printf("Погрешность входа в 1 очередь: %lf%%\n", per_in1);
    }
    else
    {
        printf("Погрешность входа в 1 очереди: 0\n");
    }

//    if (fabs(wait_in2) > EPS)
//    {
//        double per_in2 = fabs(100 * (reqin2 - wait_in2) / wait_in2);
//        printf("Погрешность входа во 2 очередь: %lf%%\n", per_in2);
//    }
//    else
//    {
//        printf("Погрешность входа во 2 очередь: 0\n");
//    }
    
//    if (fabs(wait_out1) > EPS)
//    {
//        double per_out1 = fabs(100 * (reqout1 - wait_out1) / wait_out1);
//        printf("Погрешность выхода из 1 очереди: %lf%%\n", per_out1);
//    }
//    else
//    {
//        printf("Погрешность выхода из 1 очереди: 0\n");
//    }
    
    free(quearr1);
    free(quearr2);
}
