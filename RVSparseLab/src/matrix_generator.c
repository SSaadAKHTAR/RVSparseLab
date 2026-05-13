#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/sparse.h"

void generate_random_sparse_matrix(
    double* A,
    int rows,
    int cols,
    double density
)
{
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            double r = (double)rand() / RAND_MAX;
            if (r < density) {
                A[(size_t)i * cols + j] =
                    ((double)rand() / RAND_MAX) * 20.0 - 10.0;
            }
            else {

                A[(size_t)i * cols + j] = 0.0;
            }
        }
    }
}

void generate_diagonal_matrix(
    double* A,
    int rows,
    int cols,
    double value
)
{

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            A[(size_t)i * cols + j] = 0.0;
        }
    }

    int limit = rows < cols ? rows : cols;

    for (int i = 0; i < limit; ++i) {
        A[(size_t)i * cols + i] = value;
    }
}

void generate_banded_matrix(
    double* A,
    int rows,
    int cols,
    int bandwidth
)
{

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            A[(size_t)i * cols + j] = 0.0;
        }
    }

    for (int i = 0; i < rows; ++i) {
        int start = i - bandwidth;
        int end   = i + bandwidth;
        if (start < 0)
            start = 0;
        if (end >= cols)
            end = cols - 1;
        for (int j = start; j <= end; ++j) {
            A[(size_t)i * cols + j] =
                ((double)rand() / RAND_MAX) * 20.0 - 10.0;
        }
    }
}