#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "stack_list.h"
#include "stack_array.h"

#define MAX_CAPASITY_INPUT_ERROR 2
#define WORD_INPUT_ERROR 3
#define ADD_ELEMENT_ERROR 4
#define DELETE_ELEMENT_ERROR 5

void print_menu(void)
{
    printf(" 1 - Add word\n"
           " 2 - Delete word\n"
           " 3 - Print stack\n"
           " 4 - Show freed addresses\n"
           " 5 - Print all words in reverse order and form\n"
           " 0 - Program exit.\n"
           );
}

int main(void) {
    int max_capasity;
    printf("Input max capaсity of stack: ");
    if (scanf("%d", &max_capasity) != 1)
        return MAX_CAPASITY_INPUT_ERROR;
    
    stack_array_t array;
    stack_list_t list;
    word_t word;
    clock_t start, end;
    node_t *freed_addresses[1000];
    int freed_addresses_count = 0;
    create_stack_array(&array, max_capasity);
    create_stack_list(&list);
    print_menu();
    
    int choice;
    printf("YOUR CHOICE: ");
    if (scanf("%d", &choice) != 1)
        return EXIT_FAILURE;
    
    while (choice) {
        switch (choice) {
            case 1:
                if (array.cur_ind == array.max_capasity - 1)
                {
                    printf("STACK OVERFLOW");
                    break;
                }
                printf("Input word with max len %d\n", WORD_LEN_MAX - 1);
                if (input(word) != EXIT_SUCCESS)
                    return WORD_INPUT_ERROR;
                // добавление в массив
                start = clock();
                add_to_array(&array, word);
                end = clock();
                printf("TIME ARRAY: %ld\n", end - start);
                // добавление в список
                start = clock();
                if (add_to_list(&list, word) != EXIT_SUCCESS)
                    return ADD_ELEMENT_ERROR;
                end = clock();
                printf("TIME LIST: %ld\n", end - start);
                break;
            case 2:
                // удаление из массива
                start = clock();
                if (delete_from_array(&array, word) != EXIT_SUCCESS)
                {
                    printf("STACK IS EMPTY\n");
                    break;
                }
                end = clock();
                printf("TIME ARRAY: %ld\n", end - start);
                // удаление из списка
                start = clock();
                if (delete_from_list(&list, word, freed_addresses, &freed_addresses_count) != EXIT_SUCCESS)
                {
                    printf("STACK IS EMPTY\n");
                    break;
                }
                end = clock();
                printf("TIME LIST: %ld\n", end - start);
                // вывод удаленного элемента
                printf("DELETED ELEMENT: %s\n", word);
                break;
            case 3:
                // печать массива
                start = clock();
                output_stack_array(stdout, array);
                end = clock();
                // печать списка
                start = clock();
                output_stack_list(stdout, list);
                end = clock();
                break;
            case 4:
                // печать освобожденных адресов
                for (int i = 0; i < freed_addresses_count; i++)
                    printf("%p\n", freed_addresses[i]);
                break;
            case 5:
                // печать массива
                start = clock();
                output_stack_array_in_reverse(stdout, array);
                end = clock();
                printf("TIME ARRAY: %ld\n\n", end - start);
                // печать списка
                start = clock();
                output_stack_list_in_reverse(stdout, list);
                end = clock();
                printf("TIME LIST: %ld\n", end - start);
                break;
            default:
                printf("\nWRONG CHOICE!\n");
                print_menu();
                break;
        }
        printf("\nYOUR CHOICE: ");
        if (scanf("%d", &choice) != 1)
            return EXIT_FAILURE;
    }
    
    free_stack_array(array);
    free_stack_list(list);
    return EXIT_SUCCESS;
}
