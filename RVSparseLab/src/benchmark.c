#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/sparse.h"

/*
============================================================
High Resolution Timer Utility
============================================================

Returns current time in seconds.
Uses CLOCK_MONOTONIC for stable benchmarking.
*/
static double current_time_seconds()
{
    struct timespec ts;

    clock_gettime(
        CLOCK_MONOTONIC,
        &ts
    );

    return (double)ts.tv_sec +
           (double)ts.tv_nsec * 1e-9;
}

/*
============================================================
Benchmark CSR SpMV
============================================================

Measures average execution time of:

y = A * x

using CSR traversal.

Returns:
--------
Average execution time in milliseconds.
*/
double benchmark_csr_spmv(
    const CSRMatrix* csr,
    const double* x,
    double* y,
    int iterations
)
{
    double start =
        current_time_seconds();

    /*
    ========================================================
    Execute kernel multiple times
    ========================================================
    */
    for (int i = 0; i < iterations; ++i) {

        csr_spmv(csr, x, y);
    }

    double end =
        current_time_seconds();

    /*
    Convert seconds -> milliseconds
    */
    double elapsed_ms =
        (end - start) * 1000.0;

    return elapsed_ms / iterations;
}

/*
============================================================
Benchmark CSC SpMV
============================================================

Measures average execution time of:

y = A * x

using CSC traversal.

Returns:
--------
Average execution time in milliseconds.
*/
double benchmark_csc_spmv(
    const CSCMatrix* csc,
    const double* x,
    double* y,
    int iterations
)
{
    double start =
        current_time_seconds();

    /*
    ========================================================
    Execute kernel multiple times
    ========================================================
    */
    for (int i = 0; i < iterations; ++i) {

        csc_spmv(csc, x, y);
    }

    double end =
        current_time_seconds();

    /*
    Convert seconds -> milliseconds
    */
    double elapsed_ms =
        (end - start) * 1000.0;

    return elapsed_ms / iterations;
}

/*
============================================================
Sparse Benchmarking Notes
============================================================

Sparse benchmarking is challenging because:
--------------------------------------------
- Memory access dominates performance
- FLOPS alone are misleading
- Cache behavior matters heavily
- Irregular accesses reduce vector efficiency

Key Metrics:
-------------
1. NNZ (non-zero count)
2. Density
3. Memory bandwidth
4. Traversal efficiency
5. Cache locality

Sparse kernels are often:
--------------------------
Memory-bound rather than compute-bound.

This differs from dense BLAS kernels which
are usually compute-heavy.

Future Extensions:
------------------
- GFLOPS estimation
- Memory bandwidth estimation
- Cache miss analysis
- RVV benchmark kernels
- Multi-threaded sparse kernels
*/