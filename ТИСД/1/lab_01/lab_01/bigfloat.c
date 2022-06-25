#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "bigfloat.h"
#include "string_t.h"
#include "int.h"
#include "int_array.h"

#define INCORRECT_INPUT 2
#define RESULT_TOO_BIG 3
#define RESULT_TOO_SMALL 4
#define DIVISION_BY_ZERO 5
#define MANTISSA_TOO_LONG 6
#define NUMBER_TOO_BIG 7
#define NUMBER_TOO_SMALL 8


// MARK: - Вспомогательные функции

void push_begin(bigfloat_t *num)
{
    for (int i = num->digits_count; i > 0; i--)
        num->digits[i] = num->digits[i - 1];
    num->digits[0] = 0;
    num->digits_count++;
}

void push_back(bigfloat_t *num)
{
    num->digits[num->digits_count] = 0;
    num->digits_count++;
}

int get_sign(const char *str, int *sign)
{
    int i = 0;
    
    if (!isdigit(str[i]) && str[i] != '.')
    {
        if (str[i] == '+')
            *sign = 1;
        else if (str[i] == '-')
            *sign = 0;
        else
            return EXIT_FAILURE;
        i++;
    }
    else
        *sign = 1;
    
    return EXIT_SUCCESS;
}

int get_mantissa(const char *str, bigfloat_t *num)
{
    num->digits_count = 0;
    int i = 0;
    if (str[i] == '+' || str[i] == '-')
        i++;
    
    int dot_index = get_index(str, '.');
    
    while(str[i] && str[i] != 'E')
    {
        if (i < dot_index || dot_index < 0)
        {
            if (str[i] != '0' || num->digits_count)
            {
                int res = char_to_int(str[i]);
                if (res < 0)
                    return INCORRECT_INPUT;
                num->digits_count++;
                if (num->digits_count > MANTISSA_MAX)
                    return MANTISSA_TOO_LONG;
                num->digits[num->digits_count - 1] = res;
                num->exp++;
            }
        }
        else if (i > dot_index)
        {
            if (str[i] != '0' || num->digits_count)
            {
                int res = char_to_int(str[i]);
                if (res < 0)
                    return INCORRECT_INPUT;
                num->digits_count++;
                if (num->digits_count > MANTISSA_MAX)
                    return MANTISSA_TOO_LONG;
                num->digits[num->digits_count - 1] = res;
            }
            else
                num->exp--;
        }
        i++;
    }
    
    return EXIT_SUCCESS;
}

int get_exponent(const char *str, int start_ind, bigfloat_t *num)
{
    int sign = 1;
    int i = start_ind;
    int exp = 0;
    while (str[i])
    {
        if (!isdigit(str[i]) && i == start_ind)
        {
            if (str[i] == '-')
                sign = -1;
            else if (str[i] != '+')
                return INCORRECT_INPUT;
        }
        else
        {
            int res = char_to_int(str[i]);
            if (res < 0)
                return INCORRECT_INPUT;
            exp = exp * 10 + res;
            if (exp > EXP_MAX)
                return NUMBER_TOO_BIG;
        }
        i++;
    }
    
    exp *= sign;
    
    num->exp += exp;
    
//    if (num->exp > EXP_MAX)
//        return NUMBER_TOO_BIG;
//    if (num->exp < EXP_MIN)
//        return NUMBER_TOO_SMALL;
    
    return EXIT_SUCCESS;
}

void alignment(bigfloat_t *num1, bigfloat_t *num2)
{
    int exp = max(num1->exp, num2->exp); // определяем максимальную экспоненту, чтобы к ней привести числа
        
    // выравниваем экспоненты как при сложении (добавляя нули вначале числа)
    while (num1->exp != exp)
    {
        push_begin(num1);
        num1->exp++;
    }
    
    while (num2->exp != exp) {
        push_begin(num2);
        num2->exp++;
    }
    
    int size = max(num1->digits_count, num2->digits_count); // определяем максимальный размер
    
    // добавляем нули в конец векторов цифр
    while (num1->digits_count != size)
        push_back(num1);
    
    while (num2->digits_count != size)
        push_back(num2);
}

int mantisse_size(bigfloat_t *num) {
    for (int i = MANTISSA_MAX - 1; i >= 0; i--)
        if (num->digits[i] != 0)
            return i + 1;
    return 0;
}

int is_zero(bigfloat_t *num)
{
    for (int i = 0; i < num->digits_count; i++)
        if (num->digits[i] != 0)
            return 0;
    return 1;
}

void remove_zeroes(bigfloat_t *num) {
    if (is_zero(num))
        return;
    
    while (num->digits[0] == 0)
    {
        num->digits_count--;
        num->exp--;
        for (int j = 0; j < num->digits_count; j++)
            num->digits[j] = num->digits[j + 1];
    }
    
    int i = num->digits_count - 1;
    while (num->digits[i] == 0)
    {
        num->digits_count--;
        i--;
    }
}

// MARK: - Ввод/вывод

int input(bigfloat_t *num)
{
    string_t s;
    if (!my_fgets(s, stdin))
        return EXIT_FAILURE;
        
    fill_with_zeroes(num->digits, MANTISSA_MAX); // Обнуляем массив значащих цифр
    
    num->exp = 0;
    
    if (get_sign(s, &(num->is_positive)) != 0)  // Определяем знак числа
        return INCORRECT_INPUT;
    
    if (get_mantissa(s, num) != 0) // Вычленяем значащие цифры
        return INCORRECT_INPUT;
        
    int i = get_index(s, 'E');
    
    if (i < 0)
    {
        remove_zeroes(num);
        return EXIT_SUCCESS;
    }
    
    if (get_exponent(s, i + 1, num) != 0) // Вычленяем экспоненту
        return INCORRECT_INPUT;
    
    remove_zeroes(num);
            
    return EXIT_SUCCESS;
}

void print(bigfloat_t *num)
{
    if (num->is_positive)
        printf("+");
    else
        printf("-");
    printf("0.");
    for (int i = 0; i < num->digits_count; i++)
        printf("%d", num->digits[i]);
    if (num->digits_count == 0)
        printf("0");
    printf(" E ");
    printf("%d\n", num->exp);
}

// MARK: - Копирование

void copy(bigfloat_t *src, bigfloat_t *dst)
{
    arr_copy(src->digits, dst->digits, src->digits_count);
    dst->digits_count = src->digits_count;
    dst->exp = src->exp;
    dst->is_positive = src->is_positive;
}

// MARK: - Арифметические операции

int addition(bigfloat_t *num1, bigfloat_t *num2, bigfloat_t *res)
{
    bigfloat_t num1_copy;
    bigfloat_t num2_copy;
    
    copy(num1, &num1_copy);
    copy(num2, &num2_copy);
    
    alignment(&num1_copy, &num2_copy);
    
    int exp = max(num1->exp, num2->exp); // определяем максимальную экспоненту, чтобы к ней привести числа
    
    size_t size = max(num1_copy.digits_count, num2_copy.digits_count); // определяем максимальный размер векторов
            
    res->is_positive = num1_copy.is_positive; // знак результата совпадает со знаком чисел
    
    fill_with_zeroes(res->digits, MANTISSA_MAX + 1);
    
    // записываем в каждый элемент массива сумму двух соответствующих цифр
    for (size_t i = 0; i < size; i++)
        res->digits[i] = num1_copy.digits[i] + num2_copy.digits[i];
    
    // проверяем переполнения
    for (size_t i = size; i > 0; i--) {
        res->digits[i - 1] += res->digits[i] / 10; // прибавляем к более старшему разряду десятки текущего
        res->digits[i] %= 10; // оставляем у текущего разряда только единицы
    }
    
    res->digits_count = mantisse_size(res);
    res->exp = exp;
    return EXIT_SUCCESS;
}

int subtraction(bigfloat_t *num1, bigfloat_t *num2, bigfloat_t *res)
{
    bigfloat_t num1_copy;
    bigfloat_t num2_copy;
    
    copy(num1, &num1_copy);
    copy(num2, &num2_copy);
    
    alignment(&num1_copy, &num2_copy);
    
    int exp = max(num1->exp, num2->exp); // определяем максимальную экспоненту, чтобы к ней привести числа
    
    int size = max(num1_copy.digits_count, num2_copy.digits_count); // определяем максимальный размер
            
    res->is_positive = 1; // знак будет 1, если первое больше второго, и -1, если первое меньше второго
    
    fill_with_zeroes(res->digits, MANTISSA_MAX);
    
    for (int i = 0; i < size; i++)
        res->digits[i] = num1_copy.digits[i] - num2_copy.digits[i]; // вычитаем соответствующие разряды
    
    // обрабатываем переполнения
    for (size_t i = size; i > 0; i--) {
        if (res->digits[i] < 0) { // если текущий разряд стал меньше нуля
            res->digits[i] += 10; // занимаем у предыдущего, прибавляя 10 к текущему
            res->digits[i - 1]--; // уменьшаем на 1 предыдущий разряд
        }
    }
    
    res->digits_count = mantisse_size(res);
    if (is_zero(res))// устанавливаем экспоненту
        res->exp = 0;
    else
        res->exp = exp; //+ 1;
    remove_zeroes(res); // удаляем лишнии нули
    return EXIT_SUCCESS;
}

void bf_round(bigfloat_t *num)
{
    bigfloat_t one = { .is_positive = 1, .digits = { 1 }, .digits_count = 1, .exp = 1 - num->digits_count + num->exp };
    
    bigfloat_t res;
    
    addition(num, &one, &res);
    copy(&res, num);
}

int division(bigfloat_t *num1, bigfloat_t *num2, bigfloat_t *res)
{
    if (is_zero(num2)) // делить на ноль нельзя, поэтому бросим исключение
        return DIVISION_BY_ZERO;
    
    if (is_zero(num1))
    {
        fill_with_zeroes(res->digits, MANTISSA_MAX);
        res->digits_count = 0;
        res->exp = 0;
        return EXIT_SUCCESS;
    }
    
    res->is_positive = (num1->is_positive == num2->is_positive);
    res->digits_count = 0;
    res->exp = 1;
    
    num1->is_positive = num2->is_positive = 1;

    while (cmp(num2, num1) <= 0) // пока num2 меньше num1
    {
        num2->exp++; // будем увеличивать его экспоненту (умножать на 10)
        res->exp++; // также с экспонентой результата
    }

    while (cmp(num1, num2) < 0)
    {
        num1->exp++;
        res->exp--;
    }
    
    if (res->exp > EXP_MAX || res->exp < EXP_MIN)
        return RESULT_TOO_BIG;
        
    do {
        int div = 0; // будущая цифра
        
        // считаем, сколько раз нужно вычесть num2 из num1
        while (cmp(num2, num1) <= 0) {
            div++;
            bigfloat_t curr_res;
            if (subtraction(num1, num2, &curr_res))
                return EXIT_FAILURE;
            copy(&curr_res, num1);
        }

        num1->exp++; // увеличиваем остаток в 10 раз
        remove_zeroes(num1); // нормализуем результат, убирая незначащие нули
        res->digits[res->digits_count] = div; // записываем сформированную цифру
        res->digits_count++; // увеличиваем количество значащих цифр
    } while (!is_zero(num1) && res->digits_count < MANTISSA_MAX); // считаем до тех пор, пока не дойдём до нулевого остатка или пока не превысим точность
    
    if (res->digits_count == MANTISSA_MAX)
    {
        res->digits_count--;
        if (res->digits[MANTISSA_MAX - 1] >= 5)
            bf_round(res);
    }
    
    return EXIT_SUCCESS;
}

// MARK: - Сравнение

int cmp(bigfloat_t *num1, bigfloat_t *num2)
{
    if (!num1->is_positive && num2->is_positive)
        return -1;
    if (num1->is_positive && !num2->is_positive)
        return 1;
    if (num1->exp < num2->exp && !is_zero(num2))
        return -1;
    if (num1->exp > num2->exp && !is_zero(num1))
        return 1;
    return matisse_cmp(num1, num2);
}


int matisse_cmp(bigfloat_t *num1, bigfloat_t *num2)
{
    if (num1->digits_count == 0 && num2->digits_count > 0)
        return -1;
    
    if (num2->digits_count == 0 && num1->digits_count > 0)
        return 1;
        
    int digits_count = max(num1->digits_count, num2->digits_count);
    
    for (int i = 0; i < digits_count; i++)
    {
        if (num1->digits[i] > num2->digits[i])
            return 1;
        if (num1->digits[i] < num2->digits[i])
            return -1;
    }
    
    return 0;
}
