#include "../../include/sparse.h"

void csc_spmv(
    const CSCMatrix* csc,
    const double* x,
    double* y
)
{
    for (int i = 0; i < csc->rows; ++i) {

        y[i] = 0.0;
    }
    for (int col = 0; col < csc->cols; ++col) {

        double x_val = x[col];

        int col_start = csc->col_ptrs[col];
        int col_end   = csc->col_ptrs[col + 1];

        for (int j = col_start; j < col_end; ++j) {

            double value =
                csc->values[j];
            int row =
                csc->row_indices[j];

            y[row] += value * x_val;
        }
    }
}

