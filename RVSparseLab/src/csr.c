#include <stdio.h>
#include <stdlib.h>
#include "../include/sparse.h"

void dense_to_csr(const double* A, int rows, int cols, CSRMatrix* csr)
{
    int nnz = 0;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (A[(size_t)i * cols + j] != 0.0) {
                nnz++;
            }
        }
    }
    csr->rows = rows;
    csr->cols = cols;
    csr->nnz  = nnz;

    csr->values = (double*)malloc(nnz * sizeof(double));
    csr->col_indices = (int*)malloc(nnz * sizeof(int));
    csr->row_ptrs = (int*)malloc((rows + 1) * sizeof(int));

    int index = 0;
    csr->row_ptrs[0] = 0;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            double val =
                A[(size_t)i * cols + j];
            if (val != 0.0) {
                csr->values[index] = val;
                csr->col_indices[index] = j;
                index++;
            }
        }
        csr->row_ptrs[i + 1] = index;
    }
}

void csr_print(const CSRMatrix* csr)
{
    printf("\nCSR Matrix\n");
    printf("=================================\n");

    printf("Rows : %d\n", csr->rows);
    printf("Cols : %d\n", csr->cols);
    printf("NNZ  : %d\n\n", csr->nnz);

    printf("values:\n");

    for (int i = 0; i < csr->nnz; ++i) {
        printf("%8.2f ", csr->values[i]);
    }

    printf("\n\n");

    printf("col_indices:\n");

    for (int i = 0; i < csr->nnz; ++i) {
        printf("%8d ", csr->col_indices[i]);
    }
    printf("\n\n");
    printf("row_ptrs:\n");

    for (int i = 0; i < csr->rows + 1; ++i) {
        printf("%8d ", csr->row_ptrs[i]);
    }

    printf("\n\n");
}

void csr_free(CSRMatrix* csr)
{
    free(csr->values);
    free(csr->col_indices);
    free(csr->row_ptrs);

    csr->values = NULL;
    csr->col_indices = NULL;
    csr->row_ptrs = NULL;

    csr->rows = 0;
    csr->cols = 0;
    csr->nnz  = 0;
}