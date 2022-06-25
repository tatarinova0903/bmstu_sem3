#include <stdlib.h>
#include <string.h>
#include "car_t.h"

#define FSCANF_ARGS_COUNT 1

// MARK: - Helping functions

void print_header_for_cars()
{
    printf("%s", "  №");
    printf("%20s", "BRAND");
    printf("%20s", "COUTRY");
    printf("%10s", "PRICE");
    printf("%15s", "COLOR");
    printf("%6s", "NEW");
    printf("%15s", "GARANTY");
    printf("%20s", "RELEASE YEAR");
    printf("%15s", "MILEAGE");
    printf("%15s", "REPAIR AMOUNT");
    printf("%15s", "OWNER AMOUNT");
    printf("\n");
}

void print_header_for_keys()
{
    printf("%s", "  №");
    printf("%10s", "INDEX");
    printf("%10s", "PRICE");
    printf("\n");
}

int is_equal(car_t car1, car_t car2)
{
    if (strcmp(car1.brand, car2.brand) != 0)
        return 0;
    if (strcmp(car1.country, car2.country) != 0)
        return 0;
    if (car1.price != car2.price)
        return 0;
    if (strcmp(car1.color, car2.color) != 0)
        return 0;
    if (car1.type != car2.type)
        return 0;
    if (car1.car_type.new_car.garanty != car2.car_type.new_car.garanty)
        return 0;
    return 1;
}

// MARK: - Input

int read_all_from_file(FILE *f, car_t cars[], car_key_t keys[], size_t count)
{
    for (size_t i = 0; i < count; i++)
    {
        keys[i].index = i;
        if (fscanf(f, "%s\n", cars[i].brand) != FSCANF_ARGS_COUNT)
            return CAR_BRAND_READING_ERROR;
        if (fscanf(f, "%s\n", cars[i].country) != FSCANF_ARGS_COUNT)
            return CAR_COUNTRY_READING_ERROR;
        if (fscanf(f, "%ud\n", &(cars[i].price)) != FSCANF_ARGS_COUNT)
            return CAR_PRICE_READING_ERROR;
        else
            keys[i].price = cars[i].price;
        if (fscanf(f, "%s\n", cars[i].color) != FSCANF_ARGS_COUNT)
            return CAR_COLOR_READING_ERROR;
        int car_type; // 0 - new car, !0 - old car
        if (fscanf(f, "%d\n", &car_type) != FSCANF_ARGS_COUNT)
            return CAR_TYPE_READING_ERROR;
        if (car_type == 0)
        {
            cars[i].type = NEW;
            if (fscanf(f, "%ud", &cars[i].car_type.new_car.garanty) != FSCANF_ARGS_COUNT)
                return CAR_TYPE_READING_ERROR;
        }
        else
        {
            cars[i].type = OLD;
            if (fscanf(f, "%ud", &cars[i].car_type.old_car.release_year) != FSCANF_ARGS_COUNT)
                return CAR_TYPE_READING_ERROR;
            if (fscanf(f, "%ud", &cars[i].car_type.old_car.mileage) != FSCANF_ARGS_COUNT)
                return CAR_TYPE_READING_ERROR;
            if (fscanf(f, "%ud", &cars[i].car_type.old_car.repair_amount) != FSCANF_ARGS_COUNT)
                return CAR_TYPE_READING_ERROR;
            if (fscanf(f, "%ud", &cars[i].car_type.old_car.owner_amount) != FSCANF_ARGS_COUNT)
                return CAR_TYPE_READING_ERROR;
        }
    }
    
    return EXIT_SUCCESS;
}

int input(FILE *f, car_t *car)
{
    printf("BRAND: ");
    if (fscanf(f, "%s", car->brand) != FSCANF_ARGS_COUNT)
        return CAR_BRAND_READING_ERROR;
    
    printf("COUNTRY: ");
    if (fscanf(f, "%s", car->country) != FSCANF_ARGS_COUNT)
        return CAR_COUNTRY_READING_ERROR;
    
    printf("PRICE: ");
    if (fscanf(f, "%ud", &(car->price)) != FSCANF_ARGS_COUNT)
        return CAR_PRICE_READING_ERROR;
    
    printf("COLOR: ");
    if (fscanf(f, "%s", car->color) != FSCANF_ARGS_COUNT)
        return CAR_COLOR_READING_ERROR;
    
    printf("INPUT 0 IF CAR IS NEW, !0 IF IT IS OLD: ");
    int car_type; // 0 - new car, !0 - old car
    if (fscanf(f, "%d", &car_type) != FSCANF_ARGS_COUNT)
        return CAR_TYPE_READING_ERROR;
    
    if (car_type == 0)
    {
        car->type = NEW;
        printf("GARANTY: ");
        if (fscanf(f, "%ud", &car->car_type.new_car.garanty) != FSCANF_ARGS_COUNT)
            return CAR_TYPE_READING_ERROR;
    }
    else
    {
        car->type = OLD;
        printf("RELEASE YEAR: ");
        if (fscanf(f, "%ud", &car->car_type.old_car.release_year) != FSCANF_ARGS_COUNT)
            return CAR_TYPE_READING_ERROR;
        printf("MILEAGE: ");
        if (fscanf(f, "%ud", &car->car_type.old_car.mileage) != FSCANF_ARGS_COUNT)
            return CAR_TYPE_READING_ERROR;
        printf("REPAIR AMOUNT: ");
        if (fscanf(f, "%ud", &car->car_type.old_car.repair_amount) != FSCANF_ARGS_COUNT)
            return CAR_TYPE_READING_ERROR;
        printf("OWNER AMOUNT: ");
        if (fscanf(f, "%ud", &car->car_type.old_car.owner_amount) != FSCANF_ARGS_COUNT)
            return CAR_TYPE_READING_ERROR;
    }
    printf("\n");
    return EXIT_SUCCESS;
}

// MARK:- Output

void print_all_cars(car_t cars[], size_t size)
{
    printf("\n");
    print_header_for_cars();
    for (size_t i = 0; i < size; i++)
    {
        printf("%3zu", i);
        print_car(cars[i]);
        printf("\n");
    }
}

void print_all_keys(car_key_t keys[], size_t size)
{
    printf("\n");
    print_header_for_keys();
    for (size_t i = 0; i < size; i++)
    {
        printf("%3zu", i);
        print_key(keys[i]);
        printf("\n");
    }
}

void print_car(car_t car)
{
    printf("%20s", car.brand);
    printf("%20s", car.country);
    printf("%10u", car.price);
    printf("%15s", car.color);
    if (car.type == NEW)
    {
        printf("%6s", "+");
        printf("%15d", car.car_type.new_car.garanty);
        printf("%20s", "-");
        printf("%15s", "-");
        printf("%15s", "-");
        printf("%15s", "-");
    }
    else
    {
        printf("%6s", "-");
        printf("%15s", "-");
        printf("%20u", car.car_type.old_car.release_year);
        printf("%15u", car.car_type.old_car.mileage);
        printf("%15u", car.car_type.old_car.repair_amount);
        printf("%15u", car.car_type.old_car.owner_amount);
    }
}

void print_key(car_key_t key)
{
    printf("%10zu", key.index);
    printf("%10u", key.price);
}

void print_all_cars_by_keys(car_t cars[], car_key_t keys[], size_t size)
{
    printf("\n");
    print_header_for_cars();
    for (size_t i = 0; i < size; i++)
    {
        printf("%3zu", i);
        print_car(cars[keys[i].index]);
        printf("\n");
    }
}

// MARK: - Sort

void swap_cars(car_t cars[], size_t ind1, size_t ind2)
{
    car_t temp = cars[ind1];
    cars[ind1] = cars[ind2];
    cars[ind2] = temp;
}

void swap_keys(car_key_t keys[], size_t ind1, size_t ind2)
{
    car_key_t temp = keys[ind1];
    keys[ind1] = keys[ind2];
    keys[ind2] = temp;
}

void bubble_sort_for_table(car_t cars[], size_t size)
{
    for (size_t i = 0; i < size - 1; i++)
        for (size_t j = 0; j < size - 1 - i; j++)
            if (cars[j].price > cars[j + 1].price)
                swap_cars(cars, j, j + 1);
}

void bubble_sort_for_array_of_keys(car_key_t keys[], size_t size)
{
    for (size_t i = 0; i < size - 1; i++)
        for (size_t j = 0; j < size - 1 - i; j++)
            if (keys[j].price > keys[j + 1].price)
                swap_keys(keys, j, j + 1);
}

void shaker_sort_for_table(car_t cars[], size_t size)
{
    size_t left = 0;
    size_t right = size - 1;
    while (left < right)
    {
        size_t new_right = left;
        for (size_t j = left; j < right; j++)
            if (cars[j].price > cars[j + 1].price)
            {
                swap_cars(cars, j, j + 1);
                new_right = j;
            }
        right = new_right;

        size_t new_left = right;
        for (size_t j = right; j > left; j--)
            if (cars[j].price < cars[j - 1].price)
            {
                swap_cars(cars, j, j - 1);
                new_left = j;
            }
        left = new_left;
    }
}

void shaker_sort_for_array_of_keys(car_key_t keys[], size_t size)
{
    size_t left = 0;
    size_t right = size - 1;
    while (left < right)
    {
        size_t new_right = left;
        for (size_t j = left; j < right; j++)
            if (keys[j].price > keys[j + 1].price)
            {
                swap_keys(keys, j, j + 1);
                new_right = j;
            }
        right = new_right;

        size_t new_left = right;
        for (size_t j = right; j > left; j--)
            if (keys[j].price < keys[j - 1].price)
            {
                swap_keys(keys, j, j - 1);
                new_left = j;
            }
        left = new_left;
    }
}

// MARK: - Add

int add_item(car_t cars[], size_t *size, car_t car)
{
    if (*size >= CARS_AMOUNT_MAX)
        return EXIT_FAILURE;
    cars[*size] = car;
    (*size)++;
    return EXIT_SUCCESS;
}

// MARK: - Delete

int delete_item(car_t cars[], car_key_t keys[], size_t *size, size_t index)
{
    if (index >= *size)
        return EXIT_FAILURE;
    // удаление из таблицы
    for (size_t j = index; j < *size - 1; j++)
        cars[j] = cars[j + 1];
    (*size)--;
    // удаление из массива ключей
    for (size_t i = 0; i < *size; i++)
        if (keys[i].index == index)
        {
            for (size_t j = i; j < *size - 1; j++)
                keys[j] = keys[j + 1];
            (*size)--;
            break;
        }
    return EXIT_SUCCESS;
}


//int delete_item(car_t cars[], size_t *size, car_t car)
//{
//    for (size_t i = 0; i < *size; i++)
//    if (is_equal(cars[i], car))
//    {
//        for (size_t j = i; j < *size - 1; j++)
//            cars[j] = cars[j + 1];
//        (*size)--;
//        return EXIT_SUCCESS;
//    }
//    return EXIT_FAILURE;
//}

// MARK: - Filter

void filter_cars(car_t cars[], size_t size, char brand[], unsigned int price_start, unsigned int price_end)
{
    printf("\n");
    print_header_for_cars();
    size_t count = 0;
    for (size_t i = 0; i < size; i++)
    {
        if (cars[i].type == OLD && \
            cars[i].car_type.old_car.owner_amount == 1 && \
            cars[i].car_type.old_car.repair_amount == 0 && \
            strcmp(cars[i].brand, brand) == 0 && \
            cars[i].price > price_start && \
            cars[i].price < price_end)
        {
            printf("%3zu", count);
            print_car(cars[i]);
            printf("\n");
            count++;
        }
    }
}
