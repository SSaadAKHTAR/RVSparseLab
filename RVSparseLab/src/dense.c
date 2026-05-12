#include <stdio.h>
#include <stdlib.h>
#include "../include/sparse.h"

/*
============================================================
Allocate Dense Matrix
============================================================

Allocates a contiguous dense matrix of size:
rows x cols

Matrix is initialized to zero using calloc().
*/
double* dense_alloc(int rows, int cols)
{
    return (double*)calloc(
        (size_t)rows * cols,
        sizeof(double)
    );
}

/*
============================================================
Free Dense Matrix
============================================================
*/
void dense_free(double* A)
{
    free(A);
}

/*
============================================================
Print Dense Matrix
============================================================

Displays matrix in row-major format.
*/
void dense_print(
    const double* A,
    int rows,
    int cols
)
{
    printf("\nDense Matrix (%d x %d)\n", rows, cols);
    printf("=================================\n");

    for (int i = 0; i < rows; ++i) {

        for (int j = 0; j < cols; ++j) {

            printf("%8.2f ",
                A[(size_t)i * cols + j]
            );
        }

        printf("\n");
    }

    printf("\n");
}