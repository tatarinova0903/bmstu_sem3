#include "stack_list.h"

int create_stack_list(stack_list_t *stack)
{
    stack->head = NULL;
    return EXIT_SUCCESS;
}

void free_stack_list(stack_list_t stack)
{
    node_t *next;
    for ( ; stack.head; stack.head = next)
    {
        next = stack.head->next;
        free(stack.head);
    }
}

void output_stack_list(FILE *f, stack_list_t stack)
{
    fprintf(f, "--------LIST--------\n");
    for ( ; stack.head; stack.head = stack.head->next)
    {
        output(f, stack.head->value);
        
        fprintf(f, " --- %p\n", stack.head);
    }
    fprintf(f, "--------------------\n");
}

void output_stack_list_in_reverse(FILE *f, stack_list_t stack)
{
    fprintf(f, "--------LIST--------\n");
    for ( ; stack.head; stack.head = stack.head->next)
    {
        word_t reverse_res;
        reverse(stack.head->value, reverse_res);
        output(f, reverse_res);
        fprintf(f, "\n");
    }
    fprintf(f, "--------------------\n");
}

int add_to_list(stack_list_t *stack, word_t value)
{
    node_t *elem = malloc(1 * sizeof(node_t));
    if (elem == NULL)
        return ADD_TO_LIST_IS_IMPOSSIBLE;
    node_t *temp = stack->head;
    stack->head = elem;
    elem->next = temp;
    strcpy(elem->value, value);
    return EXIT_SUCCESS;
}

int delete_from_list(stack_list_t *stack, word_t deleted_value, node_t *freed_addresses[], int *freed_addresses_count)
{
    if (stack->head == NULL)
        return EXIT_FAILURE;
    freed_addresses[*freed_addresses_count] = stack->head;
    (*freed_addresses_count)++;
    strcpy(deleted_value, stack->head->value);
    node_t *temp = stack->head->next;
    free(stack->head);
    stack->head = temp;
    return EXIT_SUCCESS;
}

unsigned long list_len(stack_list_t stack)
{
    unsigned long res = 0;
    for ( ; stack.head; stack.head = stack.head->next)
        res++;
    return res;
}
