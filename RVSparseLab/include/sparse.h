#ifndef SPARSE_H
#define SPARSE_H

#include <stddef.h>

/*
============================================================
RVSparseLab
Lightweight Sparse Linear Algebra Playground for RISC-V
============================================================
*/

/*
============================================================
CSR MATRIX FORMAT
Compressed Sparse Row
============================================================
*/
typedef struct {
    int rows;
    int cols;
    int nnz;

    double* values;
    int* col_indices;
    int* row_ptrs;

} CSRMatrix;

/*
============================================================
CSC MATRIX FORMAT
Compressed Sparse Column
============================================================
*/
typedef struct {
    int rows;
    int cols;
    int nnz;

    double* values;
    int* row_indices;
    int* col_ptrs;

} CSCMatrix;

/*
============================================================
DENSE MATRIX UTILITIES
============================================================
*/

/* Allocate dense matrix */
double* dense_alloc(int rows, int cols);

/* Free dense matrix */
void dense_free(double* A);

/* Print dense matrix */
void dense_print(
    const double* A,
    int rows,
    int cols
);

/*
============================================================
MATRIX GENERATORS
============================================================
*/

/* Generate random sparse matrix */
void generate_random_sparse_matrix(
    double* A,
    int rows,
    int cols,
    double density
);

/* Generate diagonal matrix */
void generate_diagonal_matrix(
    double* A,
    int rows,
    int cols,
    double value
);

/* Generate banded matrix */
void generate_banded_matrix(
    double* A,
    int rows,
    int cols,
    int bandwidth
);

/*
============================================================
CSR OPERATIONS
============================================================
*/

/* Convert dense matrix to CSR */
void dense_to_csr(
    const double* A,
    int rows,
    int cols,
    CSRMatrix* csr
);

/* Print CSR matrix */
void csr_print(
    const CSRMatrix* csr
);

/* Free CSR matrix */
void csr_free(
    CSRMatrix* csr
);

/*
============================================================
CSC OPERATIONS
============================================================
*/

/* Convert dense matrix to CSC */
void dense_to_csc(
    const double* A,
    int rows,
    int cols,
    CSCMatrix* csc
);

/* Print CSC matrix */
void csc_print(
    const CSCMatrix* csc
);

/* Free CSC matrix */
void csc_free(
    CSCMatrix* csc
);

/*
============================================================
SPARSE MATRIX VECTOR MULTIPLICATION
============================================================
*/

/*
y = A * x
CSR implementation
*/
void csr_spmv(
    const CSRMatrix* csr,
    const double* x,
    double* y
);

/*
y = A * x
CSC implementation
*/
void csc_spmv(
    const CSCMatrix* csc,
    const double* x,
    double* y
);

/*
============================================================
BENCHMARKING
============================================================
*/

/* Benchmark CSR SpMV */
double benchmark_csr_spmv(
    const CSRMatrix* csr,
    const double* x,
    double* y,
    int iterations
);

/* Benchmark CSC SpMV */
double benchmark_csc_spmv(
    const CSCMatrix* csc,
    const double* x,
    double* y,
    int iterations
);

/*
============================================================
RVV FUTURE KERNEL STUBS
============================================================
*/

/*
Future RVV implementation placeholder.

Potential RVV instructions:
- vle64.v
- vluxei64.v
- vfmacc.vv
*/
void csr_spmv_rvv_stub(
    const CSRMatrix* csr,
    const double* x,
    double* y
);

#endif