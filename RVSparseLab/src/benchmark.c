#define _POSIX_C_SOURCE 199309L

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/sparse.h"

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

double benchmark_csr_spmv(
    const CSRMatrix* csr,
    const double* x,
    double* y,
    int iterations
)
{
    double start =
        current_time_seconds();

    for (int i = 0; i < iterations; ++i) {

        csr_spmv(csr, x, y);
    }

    double end =
        current_time_seconds();

    double elapsed_ms =
        (end - start) * 1000.0;

    return elapsed_ms / iterations;
}

double benchmark_csc_spmv(
    const CSCMatrix* csc,
    const double* x,
    double* y,
    int iterations
)
{
    double start =
        current_time_seconds();

    for (int i = 0; i < iterations; ++i) {

        csc_spmv(csc, x, y);
    }

    double end =
        current_time_seconds();

    double elapsed_ms =
        (end - start) * 1000.0;

    return elapsed_ms / iterations;
}

