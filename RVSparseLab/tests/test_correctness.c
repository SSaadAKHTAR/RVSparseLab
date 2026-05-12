#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "../include/sparse.h"

/*
============================================================
Dense Matrix Vector Multiplication Reference
============================================================

Used to validate CSR/CSC sparse kernels.
*/
static void dense_spmv(
    const double* A,
    int rows,
    int cols,
    const double* x,
    double* y
)
{
    for (int i = 0; i < rows; ++i) {

        double sum = 0.0;

        for (int j = 0; j < cols; ++j) {

            sum +=
                A[(size_t)i * cols + j] * x[j];
        }

        y[i] = sum;
    }
}

/*
============================================================
Vector Comparison Utility
============================================================

Returns:
--------
1 -> PASS
0 -> FAIL
*/
static int compare_vectors(
    const double* a,
    const double* b,
    int size,
    double tolerance
)
{
    for (int i = 0; i < size; ++i) {

        double diff =
            fabs(a[i] - b[i]);

        if (diff > tolerance) {

            printf(
                "Mismatch at index %d\n",
                i
            );

            printf(
                "Expected : %f\n",
                a[i]
            );

            printf(
                "Got      : %f\n",
                b[i]
            );

            return 0;
        }
    }

    return 1;
}

/*
============================================================
Compute Matrix Density
============================================================
*/
static double compute_density(
    int nnz,
    int rows,
    int cols
)
{
    return
        (double)nnz /
        ((double)rows * cols);
}

/*
============================================================
Memory Usage Estimation
============================================================
*/
static void print_memory_statistics(
    int rows,
    int cols,
    int nnz
)
{
    /*
    Dense storage:
    rows * cols * sizeof(double)
    */
    size_t dense_bytes =
        (size_t)rows *
        cols *
        sizeof(double);

    /*
    CSR storage:
    values[]
    + col_indices[]
    + row_ptrs[]
    */
    size_t csr_bytes =
        nnz * sizeof(double) +
        nnz * sizeof(int) +
        (rows + 1) * sizeof(int);

    double compression_ratio =
        (double)dense_bytes / csr_bytes;

    printf("\n");
    printf("Memory Statistics\n");
    printf("=================================\n");

    printf(
        "Dense Storage : %.2f KB\n",
        dense_bytes / 1024.0
    );

    printf(
        "CSR Storage   : %.2f KB\n",
        csr_bytes / 1024.0
    );

    printf(
        "Compression Ratio : %.2fx\n",
        compression_ratio
    );

    printf("\n");
}

/*
============================================================
Main Test Driver
============================================================
*/
int main()
{
    srand((unsigned int)time(NULL));

    /*
    ========================================================
    Matrix configuration
    ========================================================
    */
    int rows = 1024;
    int cols = 1024;

    /*
    Sparse density:
    5% non-zero values
    */
    double density = 0.05;

    /*
    ========================================================
    Allocate dense matrix
    ========================================================
    */
    double* A =
        dense_alloc(rows, cols);

    /*
    ========================================================
    Generate random sparse matrix
    ========================================================
    */
    generate_random_sparse_matrix(
        A,
        rows,
        cols,
        density
    );

    /*
    ========================================================
    Allocate dense vectors
    ========================================================
    */
    double* x =
        (double*)malloc(
            cols * sizeof(double)
        );

    double* y_dense =
        (double*)malloc(
            rows * sizeof(double)
        );

    double* y_csr =
        (double*)malloc(
            rows * sizeof(double)
        );

    double* y_csc =
        (double*)malloc(
            rows * sizeof(double)
        );

    /*
    ========================================================
    Initialize input vector
    ========================================================
    */
    for (int i = 0; i < cols; ++i) {

        x[i] =
            ((double)rand() / RAND_MAX) * 10.0;
    }

    /*
    ========================================================
    Convert matrix formats
    ========================================================
    */
    CSRMatrix csr;
    CSCMatrix csc;

    dense_to_csr(
        A,
        rows,
        cols,
        &csr
    );

    dense_to_csc(
        A,
        rows,
        cols,
        &csc
    );

    /*
    ========================================================
    Compute reference dense result
    ========================================================
    */
    dense_spmv(
        A,
        rows,
        cols,
        x,
        y_dense
    );

    /*
    ========================================================
    Run sparse kernels
    ========================================================
    */
    csr_spmv(
        &csr,
        x,
        y_csr
    );

    csc_spmv(
        &csc,
        x,
        y_csc
    );

    /*
    ========================================================
    Validate correctness
    ========================================================
    */
    int csr_pass =
        compare_vectors(
            y_dense,
            y_csr,
            rows,
            1e-6
        );

    int csc_pass =
        compare_vectors(
            y_dense,
            y_csc,
            rows,
            1e-6
        );

    /*
    ========================================================
    Benchmark sparse kernels
    ========================================================
    */
    int iterations = 100;

    double csr_time =
        benchmark_csr_spmv(
            &csr,
            x,
            y_csr,
            iterations
        );

    double csc_time =
        benchmark_csc_spmv(
            &csc,
            x,
            y_csc,
            iterations
        );

    /*
    ========================================================
    Print benchmark summary
    ========================================================
    */
    printf("\n");
    printf("RVSparseLab Benchmark\n");
    printf("=================================\n");

    printf(
        "Matrix Size : %d x %d\n",
        rows,
        cols
    );

    printf(
        "NNZ         : %d\n",
        csr.nnz
    );

    printf(
        "Density     : %.2f%%\n",
        compute_density(
            csr.nnz,
            rows,
            cols
        ) * 100.0
    );

    printf("\n");

    printf(
        "CSR Correctness : %s\n",
        csr_pass ? "PASS" : "FAIL"
    );

    printf(
        "CSC Correctness : %s\n",
        csc_pass ? "PASS" : "FAIL"
    );

    printf("\n");

    printf(
        "CSR SpMV Time : %.6f ms\n",
        csr_time
    );

    printf(
        "CSC SpMV Time : %.6f ms\n",
        csc_time
    );

    /*
    ========================================================
    Memory statistics
    ========================================================
    */
    print_memory_statistics(
        rows,
        cols,
        csr.nnz
    );

    /*
    ========================================================
    Cleanup
    ========================================================
    */
    dense_free(A);

    csr_free(&csr);
    csc_free(&csc);

    free(x);
    free(y_dense);
    free(y_csr);
    free(y_csc);

    return 0;
}