#ifndef car_t_h
#define car_t_h

#include <stdio.h>

#define READING_CAR_ERROR 2
#define CAR_BRAND_READING_ERROR 3
#define CAR_COUNTRY_READING_ERROR 4
#define CAR_PRICE_READING_ERROR 5
#define CAR_COLOR_READING_ERROR 6
#define CAR_TYPE_READING_ERROR 7

#define STR_LEN_MAX 26
#define CARS_AMOUNT_MAX 50


typedef enum {
    NEW, // новая машина
    OLD // старая машина
} car_type_t;

typedef struct {
    unsigned int garanty; // гарантия
} new_car_t;

typedef struct {
    unsigned int release_year; // год выпуска
    unsigned int mileage; // пробег
    unsigned int repair_amount; // количество ремонтов
    unsigned int owner_amount; // количество собственников
} old_car_t;

typedef struct {
    char brand[STR_LEN_MAX]; // марка
    char country[STR_LEN_MAX]; // страна производитель
    unsigned int price; // цена
    char color[STR_LEN_MAX]; // цвет
    car_type_t type; // тип машины - новая или старая
    union {
        new_car_t new_car; // информация о машине, если она новая
        old_car_t old_car; // информация о машине, если она старая
    } car_type;
} car_t;

typedef struct {
    size_t index; // индекс машины в изначальной таблице
    unsigned int price; // цена машины
} car_key_t;

int read_all_from_file(FILE *f, car_t cars[], car_key_t keys[], size_t count);
int input(FILE *f, car_t *car);

void print_all_cars(car_t cars[], size_t size);
void print_all_keys(car_key_t keys[], size_t size);
void print_car(car_t car);
void print_key(car_key_t key);
void print_all_cars_by_keys(car_t cars[], car_key_t keys[], size_t size);

void bubble_sort_for_table(car_t cars[], size_t size);
void bubble_sort_for_array_of_keys(car_key_t keys[], size_t size);

void shaker_sort_for_table(car_t cars[], size_t size);
void shaker_sort_for_array_of_keys(car_key_t keys[], size_t size);

int add_item(car_t cars[], size_t *size, car_t car);

int delete_item(car_t cars[], car_key_t keys[], size_t *size, size_t index);

void filter_cars(car_t cars[], size_t size, char brand[], unsigned int price_start, unsigned int price_end);

int is_equal(car_t car1, car_t car2);

#endif
