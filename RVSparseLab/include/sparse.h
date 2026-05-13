#ifndef SPARSE_H
#define SPARSE_H

#include <stddef.h>


// CSR matrix format compressed sparse row

typedef struct {int rows; int cols; int nnz; double* values; int* col_indices; int* row_ptrs;} CSRMatrix;


// comprased sparse column format(csc)

typedef struct {int rows; int cols; int nnz; double* values; int* row_indices; int* col_ptrs;} CSCMatrix;


//allocation of dense matrix
double* dense_alloc(int rows, int cols);

// free dense matrix
void dense_free(double* A);

// print dense matrix
void dense_print(const double* A, int rows, int cols);


void generate_random_sparse_matrix(double* A, int rows, int cols, double density);

void generate_diagonal_matrix(double* A, int rows, int cols, double value);

void generate_banded_matrix(double* A, int rows, int cols, int bandwidth);



// dense matrix to csr
void dense_to_csr(const double* A, int rows, int cols, CSRMatrix* csr);

void csr_print(const CSRMatrix* csr);

void csr_free(CSRMatrix* csr);


// dense to csc 
void dense_to_csc(const double* A, int rows, int cols, CSCMatrix* csc);

void csc_print(const CSCMatrix* csc);

void csc_free(CSCMatrix* csc);

// sparse matrix multiply by vector
void csr_spmv(const CSRMatrix* csr, const double* x, double* y);

void csc_spmv(const CSCMatrix* csc, const double* x, double* y);



//benchmark of csr spmv
double benchmark_csr_spmv(const CSRMatrix* csr, const double* x, double* y, int iterations);

// benchmark of csc spmv
double benchmark_csc_spmv(const CSCMatrix* csc, const double* x, double* y, int iterations);

// future RVV kernel place holder
void csr_spmv_rvv_stub(const CSRMatrix* csr, const double* x, double* y);

#endif