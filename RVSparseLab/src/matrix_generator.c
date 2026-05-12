#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/sparse.h"

/*
============================================================
Generate Random Sparse Matrix
============================================================

density:
0.0 -> completely sparse
1.0 -> completely dense

Example:
density = 0.05
means ~5% non-zero elements.
*/
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

                /*
                Generate random value between:
                -10.0 and +10.0
                */
                A[(size_t)i * cols + j] =
                    ((double)rand() / RAND_MAX) * 20.0 - 10.0;
            }
            else {

                A[(size_t)i * cols + j] = 0.0;
            }
        }
    }
}

/*
============================================================
Generate Diagonal Matrix
============================================================

Example:

5 0 0
0 5 0
0 0 5
*/
void generate_diagonal_matrix(
    double* A,
    int rows,
    int cols,
    double value
)
{
    /*
    First initialize everything to zero.
    */
    for (int i = 0; i < rows; ++i) {

        for (int j = 0; j < cols; ++j) {

            A[(size_t)i * cols + j] = 0.0;
        }
    }

    /*
    Fill diagonal.
    */
    int limit = rows < cols ? rows : cols;

    for (int i = 0; i < limit; ++i) {

        A[(size_t)i * cols + i] = value;
    }
}

/*
============================================================
Generate Banded Matrix
============================================================

Example bandwidth = 1

x x 0 0
x x x 0
0 x x x
0 0 x x

Useful in:
- finite element methods
- PDE solvers
- scientific computing
*/
void generate_banded_matrix(
    double* A,
    int rows,
    int cols,
    int bandwidth
)
{
    /*
    Initialize matrix to zero.
    */
    for (int i = 0; i < rows; ++i) {

        for (int j = 0; j < cols; ++j) {

            A[(size_t)i * cols + j] = 0.0;
        }
    }

    /*
    Fill values near diagonal.
    */
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