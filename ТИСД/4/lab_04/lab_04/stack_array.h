#ifndef stack_array_h
#define stack_array_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "word.h"

#define ADD_TO_ARRAY_IS_IMPOSSIBLE 2

// стек в виде массива
typedef struct {
    word_t *arr; // сам стек
    int cur_ind; // верхушка стека
    int max_capasity; // максимальный размер стека
} stack_array_t;

int create_stack_array(stack_array_t *stack, int size);
void free_stack_array(stack_array_t stack);

void output_stack_array(FILE *f, stack_array_t stack);
void output_stack_array_in_reverse(FILE *f, stack_array_t stack);

int add_to_array(stack_array_t *stack, word_t value);
int delete_from_array(stack_array_t *stack, word_t deleted_value);

#endif
