#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "graph.h"

int min(int a, int b)
{
    return a < b ? a : b;
}

void print_matrix(int matrix[][MATRIX_MAX], int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if(matrix[i][j] == INF)
                printf("INF ");
            else
                printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

 
int main()
{
    int size;
    printf("Введите количество вершин: ");
    scanf("%d", &size);
    
    FILE *f = fopen("/Users/daria/Documents/ИУ7/семестр3/ТИСД/7/lab_07/lab_07/text", "r");
    
    
    int matrix[MATRIX_MAX][MATRIX_MAX];
    
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            fscanf(f, "%d", &matrix[i][j]);
            if (matrix[i][j] == 0)
                matrix[i][j] = INF;
            else
                matrix[i][j] *= (-1);
        }
    }
    
    FILE *f_out = fopen("/Users/daria/Documents/ИУ7/семестр3/ТИСД/7/lab_07/lab_07/graph", "w");
    export_to_dot(f_out, matrix, size);
    fclose(f_out);
    fclose(f);
    
    if (size == 2)
    {
        int value, start, end;
        find_min_in_matrix(matrix, size, &value, &start, &end);
        
        printf("%d --> %d : %d\n", start, end, value * (-1));
        return EXIT_SUCCESS;
    }
    
    for(int k = 0; k < size; k++)
    {
        for(int i = 0; i < size; i++)
        {
            for(int j = 0; j < size; j++)
            {
                matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j]);
            }
        }
    }

    int value, start, end;
    find_min_in_matrix(matrix, size, &value, &start, &end);
    
    printf("%d --> %d : %d\n", start, end, value * (-1));
    
    
    return EXIT_SUCCESS;
}
