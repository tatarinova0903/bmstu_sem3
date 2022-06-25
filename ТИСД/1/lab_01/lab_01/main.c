#include <stdio.h>
#include "bigfloat.h"

#define INPUT_ERR 2

int main() {
    
    printf("Input floating number in exponential form with big E:\n");
    printf("%12s______________________________E_____\n", " ");
    
    bigfloat_t num1;

    printf("Input num1: ");
    if (input(&num1))
    {
        printf("Incorrect input\n");
        return INPUT_ERR;
    }
    
    bigfloat_t num2;
    
    printf("Input num2: ");
    if (input(&num2))
    {
        printf("Incorrect input\n");
        return INPUT_ERR;
    }
    
    bigfloat_t res;

    int rc = division(&num1, &num2, &res);
    if (rc != 0)
    {
        printf("It is impossible to get the result\n");
        return rc;
    }
    
    print(&res);
    
    return 0;
}

