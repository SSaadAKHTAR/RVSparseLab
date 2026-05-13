#include "../../include/sparse.h"

void csr_spmv(
    const CSRMatrix* csr,
    const double* x,
    double* y
)
{
    for (int i = 0; i < csr->rows; ++i) {

        double sum = 0.0;

        int row_start = csr->row_ptrs[i];
        int row_end   = csr->row_ptrs[i + 1];

        for (int j = row_start; j < row_end; ++j) {

            double value =
                csr->values[j];
            int col =
                csr->col_indices[j];

            sum += value * x[col];
        }
        y[i] = sum;
    }
}
