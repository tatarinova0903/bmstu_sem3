#ifndef graph_h
#define graph_h

#include <stdio.h>
#include <limits.h>

#define MATRIX_MAX 200
#define INF 100000

void export_to_dot(FILE *f, int matrix[][MATRIX_MAX], int size);
void find_min_in_matrix(int matrix[][MATRIX_MAX], int size, int *value, int *start , int *end);

#endif
