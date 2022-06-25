#ifndef bigfloat_h
#define bigfloat_h

#include <stdlib.h>

#define MANTISSA_MAX 31
#define EXP_MAX 99999
#define EXP_MIN -99999

typedef struct {
    int is_positive; // знак мантиссы
    int digits[MANTISSA_MAX]; // значащие цифры
    int digits_count; // количество значащих цифр
    int exp;
} bigfloat_t;

void print(bigfloat_t *num);
int input(bigfloat_t *num);

int division(bigfloat_t *num1, bigfloat_t *num2, bigfloat_t *res);
int is_zero(bigfloat_t *num);
int cmp(bigfloat_t *num1, bigfloat_t *num2);
int subtraction(bigfloat_t *num1, bigfloat_t *num2, bigfloat_t *res);
int addition(bigfloat_t *num1, bigfloat_t *num2, bigfloat_t *res);
void copy(bigfloat_t *src, bigfloat_t *dst);
void remove_zeroes(bigfloat_t *num);
int matisse_cmp(bigfloat_t *num1, bigfloat_t *num2);
int mantisse_size(bigfloat_t *num);
void bf_round(bigfloat_t *num);

#endif
