#include "graph.h"

void export_to_dot(FILE *f, int matrix[][MATRIX_MAX], int size)
{
    fprintf(f, "digraph pic {\n");

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (matrix[i][j] != INF)
                fprintf(f, "%d -> %d [ label = ""%d"" ];\n", i, j, matrix[i][j] * (-1));
        }
    }

    fprintf(f, "}\n");
}

void find_min_in_matrix(int matrix[][MATRIX_MAX], int size, int *value, int *start , int *end)
{
    *value = INT_MAX;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (matrix[i][j] < *value)
            {
                *value = matrix[i][j];
                *start = i;
                *end = j;
            }
        }
    }
}
