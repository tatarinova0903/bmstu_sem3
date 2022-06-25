#include "time_mem.h"

double getime(times_t t)
{
    return (t.max - t.min) * (double)(rand()) / (double)RAND_MAX + t.min;
}

void check_memory_time()
{
    queue_t queue1;
    strcpy(queue1.name, "First Queue");
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

    node_t *queue2 = NULL;
    queue_t que2;
    strcpy(que2.name, "Second Queue");
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

    int64_t t1b = tick();
    queuearray_push(&queue1, '1');
    int64_t t1e = tick();
    int64_t t2b = tick();
    node_t *item = createelem('1');
    queue2 = pushfront(queue2, item);
    int64_t t2e = tick();
    printf("ДОБАВЛЕНИЕ\n");
    printf("Очередь-массив %d\n", (int)(t1e - t1b));
    printf("Очередь-список %d\n\n", (int)(t2e - t2b));

    t1b = tick();
    queuearray_pop(&queue1);
    t1e = tick();
    t2b = tick();
    node_t * res = queuelist_pop(&queue2);
    free(res);
    t2e = tick();

    printf("УДАЛЕНИЕ\n");
    printf("Очередь-массив %d\n", (int)(t1e - t1b));
    printf("Очередь-список %d\n\n", (int)(t2e - t2b));

    int n = 10;
    printf("ПАМЯТЬ\n");
    for (int i = 0; i < 4; i++)
    {
        printf("Колчество элементов = %d\n", n);
        printf("Очередь-массив %d\n", (int)(sizeof(char) * n));
        printf("Очередь-список %d\n\n", (int)((sizeof(node_t*) + sizeof(char)) * n));
        n *= 10;
    }
}



int64_t tick(void)
{
    uint32_t high, low;
    __asm__ __volatile__(
        "rdtsc\n"
        "movl %%edx, %0\n"
        "movl %%eax, %1\n"
        : "=r"(high), "=r"(low)::"%rax", "%rbx", "%rcx", "%rdx");

    uint64_t ticks = ((uint64_t)high << 32) | low;

    return ticks;
}
