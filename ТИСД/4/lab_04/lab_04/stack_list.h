#ifndef stack_list_h
#define stack_list_h

#include <stdio.h>
#include "word.h"

#define ADD_TO_LIST_IS_IMPOSSIBLE 2

// стек в виде списка
typedef struct node
{
    word_t value; // значение узла списка
    struct node *next; // указатель на следующий узел
} node_t;

typedef struct {
    node_t *head; // указатель наголову списка
} stack_list_t;

int create_stack_list(stack_list_t *stack);
void free_stack_list(stack_list_t stack);

void output_stack_list(FILE *f, stack_list_t stack);
void output_stack_list_in_reverse(FILE *f, stack_list_t stack);

int add_to_list(stack_list_t *stack, word_t value);
int delete_from_list(stack_list_t *stack, word_t deleted_value, node_t *freed_addresses[], int *freed_addresses_count);

unsigned long list_len(stack_list_t stack);

#endif
