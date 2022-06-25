#include "int_array.h"

void fill_with_zeroes(int arr[], size_t size)
{
    for (size_t i = 0; i < size; i++)
        arr[i] = 0;
}

void arr_copy(int src[], int dst[], int size)
{
    for (int i = 0; i < size; i++)
        dst[i] = src[i];
}
