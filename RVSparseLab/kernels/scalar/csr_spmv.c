#include "../../include/sparse.h"

/*
============================================================
CSR Sparse Matrix Vector Multiplication (SpMV)
============================================================

Computes:

y = A * x

where:
- A is stored in CSR format
- x is dense input vector
- y is dense output vector

CSR traversal:
---------------
values[]      -> non-zero values
col_indices[] -> column of each value
row_ptrs[]    -> row boundaries

This is the fundamental sparse kernel used in:
- scientific computing
- graph analytics
- ML inference
- iterative solvers
- HPC applications

Time Complexity:
----------------
O(nnz)

instead of:

O(rows * cols)

for dense multiplication.
*/
void csr_spmv(
    const CSRMatrix* csr,
    const double* x,
    double* y
)
{
    /*
    ========================================================
    Traverse rows
    ========================================================
    */
    for (int i = 0; i < csr->rows; ++i) {

        double sum = 0.0;

        /*
        Start and end positions of current row
        inside CSR arrays.
        */
        int row_start = csr->row_ptrs[i];
        int row_end   = csr->row_ptrs[i + 1];

        /*
        ====================================================
        Traverse non-zero values of current row
        ====================================================
        */
        for (int j = row_start; j < row_end; ++j) {

            double value =
                csr->values[j];

            int col =
                csr->col_indices[j];

            /*
            Sparse multiply accumulate:

            sum += A[i][col] * x[col]
            */
            sum += value * x[col];
        }

        /*
        Store output result
        */
        y[i] = sum;
    }
}

/*
============================================================
Future RVV Optimization Notes
============================================================

Potential RVV vectorization strategy:

1. Vector load CSR values
   vle64.v

2. Gather x[col_indices]
   vluxei64.v

3. Vector fused multiply accumulate
   vfmacc.vv

Challenges:
------------
- Irregular memory access
- Gather load latency
- Load imbalance
- Variable row lengths

Potential optimizations:
------------------------
- Row blocking
- Strip mining
- Segmented reductions
- Hybrid sparse formats
*/