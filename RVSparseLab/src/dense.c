#include <stdio.h>
#include <stdlib.h>
#include "../include/sparse.h"

double* dense_alloc(int rows, int cols)
{
    return (double*)calloc(
        (size_t)rows * cols,
        sizeof(double)
    );
}

void dense_free(double* A)
{
    free(A);
}

void dense_print(const double* A, int rows, int cols)
{
    printf("\nDense Matrix (%d x %d)\n", rows, cols);
    printf("=================================\n");

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            printf("%8.2f ", A[(size_t)i * cols + j]);
        }

        printf("\n");
    }

    printf("\n");
}