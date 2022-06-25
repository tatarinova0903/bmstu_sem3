#ifndef queue_h
#define queue_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <math.h>

#define MAXLENQUEUE 1000
#define EPS 1e-6

#define TRUE 1
#define FALSE 0

#define INPUT_ERR 1
#define FILE_OPEN_ERR 2
#define FILE_READ_ERR 3
#define DONT_INT_NUM_CHOICE 4
#define INV_NUM_CHOICE 5

typedef char queue_type;
typedef struct queue
{
    char name[30]; // Имя очереди
    void* low; // Адрес нижней границы
    void* up; // Адрес верхней границы
    void* p_in; // Указатель на "хвост"
    void* p_out; // Указатель на "голову"
    int len; // Число элементов
    size_t size; // Размер типа данных
    int count_req; // Число запросов
    int avg_len; // Средняя длина
    int cur_len; // Текущая длина
    int sum_time; // Общее время
    int out_req; // Число запросов на выход
    int in_req; // Число запросов на вход
} queue_t;

typedef struct node
{
    queue_type type; // тип очереди
    struct node *next; // указатель на следующий узел
} node_t;

typedef struct
{
    double min; // нижняя граница
    double max; // верхняя граница
} times_t;



#endif /* queue_h */
