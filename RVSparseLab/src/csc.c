#include <stdio.h>
#include <stdlib.h>
#include "../include/sparse.h"

void dense_to_csc(
    const double* A,
    int rows,
    int cols,
    CSCMatrix* csc
)
{
    int nnz = 0;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (A[(size_t)i * cols + j] != 0.0) {
                nnz++;
            }
        }
    }

    csc->rows = rows;
    csc->cols = cols;
    csc->nnz  = nnz;

    csc->values = (double*)malloc(
        nnz * sizeof(double));
    csc->row_indices = (int*)malloc(
        nnz * sizeof(int));
    csc->col_ptrs = (int*)malloc(
        (cols + 1) * sizeof(int));

    int index = 0;
    csc->col_ptrs[0] = 0;

    for (int j = 0; j < cols; ++j) {
        for (int i = 0; i < rows; ++i) {
            double val =
                A[(size_t)i * cols + j];
            if (val != 0.0) {
                csc->values[index] = val;
                csc->row_indices[index] = i;
                index++;
            }
        }
        csc->col_ptrs[j + 1] = index;
    }
}

void csc_print(
    const CSCMatrix* csc
)
{
    printf("\nCSC Matrix\n");
    printf("=================================\n");

    printf("Rows : %d\n", csc->rows);
    printf("Cols : %d\n", csc->cols);
    printf("NNZ  : %d\n\n", csc->nnz);

    printf("values:\n");

    for (int i = 0; i < csc->nnz; ++i) {
        printf("%8.2f ",
            csc->values[i]);
    }

    printf("\n\n");
    printf("row_indices:\n");

    for (int i = 0; i < csc->nnz; ++i) {
        printf("%8d ",
            csc->row_indices[i]);
    }

    printf("\n\n");
    printf("col_ptrs:\n");

    for (int i = 0; i < csc->cols + 1; ++i) {
        printf("%8d ",
            csc->col_ptrs[i]);
    }

    printf("\n\n");
}

void csc_free(
    CSCMatrix* csc
)
{
    free(csc->values);
    free(csc->row_indices);
    free(csc->col_ptrs);

    csc->values = NULL;
    csc->row_indices = NULL;
    csc->col_ptrs = NULL;

    csc->rows = 0;
    csc->cols = 0;
    csc->nnz  = 0;
}