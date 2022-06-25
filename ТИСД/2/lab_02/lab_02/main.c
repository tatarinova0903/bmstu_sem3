#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "car_t.h"

#define IN_FILE_OPENING_ERROR 2
#define CARS_AMOUNT_READING_ERROR 3

int main(void) {
    
    FILE *in_file = fopen("data.txt", "r");
    
    if (in_file == NULL)
        return IN_FILE_OPENING_ERROR;
    
    car_t cars[CARS_AMOUNT_MAX];
    car_key_t keys[CARS_AMOUNT_MAX];
    
    size_t cars_count;
    if (fscanf(in_file, "%zu", &cars_count) != 1)
        return CARS_AMOUNT_READING_ERROR;
    
    read_all_from_file(in_file, cars, keys, cars_count);
    
    printf("\
           1 - Bubble sort with key - price, using table\n\
           2 - Bubble sort with key - price, using array of keys\n\
           3 - Shaker sort with key - price, using table\n\
           4 - Shaker sort with key - price, using array of keys\n\
           5 - Add item\n\
           6 - Delete item\n\
           7 - Show all old cars with selected brand with only 1 owner without repair in selected range of prices\n\
           8 - Print table of cars\n\
           9 - Print array of keys\n\
           10 - Print table according to array of keys\n\
           0 - EXIT\n");
    
    int choice;
    printf("YOUR CHOICE: ");
    scanf("%d", &choice);
    
    car_t car;
    char brand[STR_LEN_MAX];
    unsigned int price_start, price_end;
    
    size_t index_to_delete;
    
    clock_t start, end;
    
    while (choice)
    {
        switch (choice) {
            case 1:
                start = clock();
                bubble_sort_for_table(cars, cars_count);
                end = clock();
                printf("Sort ended in %f\n", (double)(end - start) / CLOCKS_PER_SEC);
                break;
            case 2:
                start = clock();
                bubble_sort_for_array_of_keys(keys, cars_count);
                end = clock();
                printf("Sort ended in %f\n", (double)(end - start) / CLOCKS_PER_SEC);
                break;
            case 3:
                start = clock();
                shaker_sort_for_table(cars, cars_count);
                end = clock();
                printf("Sort ended in %f\n", (double)(end - start) / CLOCKS_PER_SEC);
                break;
            case 4:
                start = clock();
                shaker_sort_for_array_of_keys(keys, cars_count);
                end = clock();
                printf("Sort ended in %f\n", (double)(end - start) / CLOCKS_PER_SEC);
                break;
            case 5:
                if (input(stdin, &car) != EXIT_SUCCESS)
                    printf("Incorrect input\n");
                else if (add_item(cars, &cars_count, car) != EXIT_SUCCESS)
                    printf("It is impossible to add 1 more item\n");
                else
                    printf("ADDED\n");
                break;
            case 6:
                printf("INDEX OF CAR TO DELETE: ");
                if (scanf("%zu", &index_to_delete) != 1)
                    printf("Incorrect input\n");
                else if (delete_item(cars, keys, &cars_count, index_to_delete) != EXIT_SUCCESS)
                    printf("There was no such car\n");
                else
                    printf("DELETED\n");
                break;
            case 7:
                printf("BRAND: ");
                if (scanf("%s", brand) != 1)
                    printf("Incorrect input\n");
                printf("START PRICE: ");
                if (scanf("%ud", &price_start) != 1)
                    printf("Incorrect input\n");
                printf("END PRICE: ");
                if (scanf("%ud", &price_end) != 1)
                    printf("Incorrect input\n");
                filter_cars(cars, cars_count, brand, price_start, price_end);
                break;
            case 8:
                print_all_cars(cars, cars_count);
                break;
            case 9:
                print_all_keys(keys, cars_count);
                break;
            case 10:
                print_all_cars_by_keys(cars, keys, cars_count);
                break;
            default:
                printf("Wrong choice\n");
                break;
        }
        printf("YOUR CHOICE: ");
        scanf("%d", &choice);
    }
        
    return 0;
}
