#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "stack_list.h"
#include "stack_array.h"
#include "word.h"

int main(void)
{
    stack_list_t list;
    stack_array_t array;
    int max_capasity;
    scanf("%d", &max_capasity);
    printf("FOR %d\n", max_capasity);
    create_stack_array(&array, max_capasity);
    create_stack_list(&list);
    word_t word;
    input(word);
    
    clock_t start, end;
    
    start = clock();
    add_to_array(&array, word);
    end = clock();
    printf("[TIME] ARRAY ADD %ld\n", end - start);
    
    start = clock();
    add_to_list(&list, word);
    end = clock();
    printf("[TIME] LIST ADD %ld\n", end - start);
    
    node_t *freed_ddresses[2];
    int freed_adresses_count = 0;
    start = clock();
    delete_from_array(&array, word);
    end = clock();
    printf("[TIME] ARRAY DELETE %ld\n", end - start);
    
    start = clock();
    delete_from_list(&list, word, freed_ddresses, &freed_adresses_count);
    end = clock();
    printf("[TIME] LIST DELETE %ld\n", end - start);
    
    for (int i = 1; i < max_capasity; i++)
    {
        input(word);
        add_to_list(&list, word);
        add_to_array(&array, word);
    }

    FILE *f = fopen("out.txt", "w");
    if (f == NULL)
        return EXIT_FAILURE;
    
    printf("[SIZE] ARRAY %ld\n", sizeof(array.arr) * array.max_capasity + sizeof(array.cur_ind) + sizeof(array.max_capasity));
    printf("[SIZE] LIST %ld\n\n", (sizeof(list.head->next) + sizeof(list.head->value)) * list_len(list));
    
    fclose(f);
    return EXIT_SUCCESS;
}
