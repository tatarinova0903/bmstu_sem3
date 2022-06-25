#include "stack_array.h"

int create_stack_array(stack_array_t *stack, int size)
{
    stack->arr = calloc(size, sizeof(word_t));
    if (stack->arr == NULL)
        return EXIT_FAILURE;
    stack->cur_ind = -1;
    stack->max_capasity = size;
    return EXIT_SUCCESS;
}

void free_stack_array(stack_array_t stack)
{
    free(stack.arr);
}

int add_to_array(stack_array_t *stack, word_t value)
{
    stack->cur_ind++;
    if (stack->cur_ind >= stack->max_capasity)
        return ADD_TO_ARRAY_IS_IMPOSSIBLE;
    strcpy(stack->arr[stack->cur_ind], value);
    return EXIT_SUCCESS;
}

int delete_from_array(stack_array_t *stack, word_t deleted_value)
{
    strcpy(stack->arr[stack->cur_ind], deleted_value);
    if (stack->cur_ind < 0)
        return EXIT_FAILURE;
    stack->cur_ind--;
    return EXIT_SUCCESS;
}

void output_stack_array(FILE *f, stack_array_t stack)
{
    fprintf(f, "--------ARRAY-------\n");
    for (int i = stack.cur_ind; i >= 0; i--)
    {
        output(f, stack.arr[i]);
        fprintf(f, "\n");
    }
    fprintf(f, "--------------------\n");
}

void output_stack_array_in_reverse(FILE *f, stack_array_t stack)
{
    fprintf(f, "--------ARRAY-------\n");
    for (int i = stack.cur_ind; i >= 0; i--)
    {
        word_t reverse_res;
        reverse(stack.arr[i], reverse_res);
        output(f, reverse_res);
        fprintf(f, "\n");
    }
    fprintf(f, "--------------------\n");
}
