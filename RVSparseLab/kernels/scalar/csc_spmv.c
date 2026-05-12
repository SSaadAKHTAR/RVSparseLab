#include "../../include/sparse.h"

/*
============================================================
CSC Sparse Matrix Vector Multiplication (SpMV)
============================================================

Computes:

y = A * x

where:
- A is stored in CSC format
- x is dense input vector
- y is dense output vector

CSC traversal:
---------------
values[]      -> non-zero values
row_indices[] -> row index of each value
col_ptrs[]    -> column boundaries

Unlike CSR:
- CSR computes row-wise
- CSC computes column-wise

This changes:
- traversal behavior
- cache locality
- write access patterns
- vectorization characteristics
*/
void csc_spmv(
    const CSCMatrix* csc,
    const double* x,
    double* y
)
{
    /*
    ========================================================
    Initialize output vector
    ========================================================
    */
    for (int i = 0; i < csc->rows; ++i) {

        y[i] = 0.0;
    }

    /*
    ========================================================
    Traverse columns
    ========================================================
    */
    for (int col = 0; col < csc->cols; ++col) {

        /*
        Current x value reused for entire column.
        */
        double x_val = x[col];

        /*
        Start and end positions of current column
        inside CSC arrays.
        */
        int col_start = csc->col_ptrs[col];
        int col_end   = csc->col_ptrs[col + 1];

        /*
        ====================================================
        Traverse non-zero values of current column
        ====================================================
        */
        for (int j = col_start; j < col_end; ++j) {

            double value =
                csc->values[j];

            int row =
                csc->row_indices[j];

            /*
            Sparse multiply accumulate:

            y[row] += A[row][col] * x[col]
            */
            y[row] += value * x_val;
        }
    }
}

/*
============================================================
CSR vs CSC Traversal Notes
============================================================

CSR:
-----
- Efficient row traversal
- Naturally computes y[i]
- Better for row-oriented SpMV
- Sequential writes to y[]

CSC:
-----
- Efficient column traversal
- Reuses x[col]
- Irregular writes into y[]
- Better for transpose-like operations

Memory Access Patterns:
-----------------------
CSR:
    values[]      -> sequential
    col_indices[] -> sequential
    x[col]        -> irregular gather
    y[i]          -> sequential write

CSC:
    values[]      -> sequential
    row_indices[] -> sequential
    x[col]        -> reused
    y[row]        -> irregular write

Sparse Vectorization Challenges:
--------------------------------
- Irregular gather/scatter
- Cache misses
- Variable sparsity patterns
- Load imbalance

Future RVV Opportunities:
-------------------------
- Gather loads
- Vector FMA
- Segmented reductions
- Sparse blocking techniques
*/