# RVSparseLab

> A Lightweight Sparse Linear Algebra Playground for RISC-V

---

## Overview

**RVSparseLab** is a lightweight sparse linear algebra framework written in C that explores sparse matrix storage formats, sparse matrix-vector multiplication (SpMV), benchmarking, and RISC-V Vector (RVV) oriented sparse kernel design.

This project was built as related work for the **RV-Sparse LFX mentorship project** focused on sparse linear algebra acceleration using the RISC-V Vector Extension.

The project demonstrates:

- Dense → CSR conversion
- Dense → CSC conversion
- CSR Sparse Matrix-Vector Multiplication (SpMV)
- CSC Sparse Matrix-Vector Multiplication (SpMV)
- Sparse benchmarking infrastructure
- Matrix generation utilities
- Memory compression analysis
- RVV-oriented architecture planning

The implementation focuses on:

- Memory-efficient traversal
- Sparse storage techniques
- Sparse computation patterns
- Vectorization awareness
- HPC-style benchmarking

---

## Why Sparse Linear Algebra Matters

Sparse matrices appear in many important domains:

| Domain | Example Use |
|---|---|
| Scientific Computing | PDE/FEM Solvers |
| Machine Learning | Sparse Neural Networks |
| Graph Analytics | Adjacency matrices |
| Recommendation Systems | User-item interaction matrices |
| HPC Simulations | Large-scale physics models |

In sparse matrices, most values are zero. Instead of storing every element, sparse formats store only non-zero values, reducing:

- Memory usage
- Memory bandwidth
- Computation cost

---

## Sparse Storage Formats

### CSR — Compressed Sparse Row

CSR stores sparse matrices **row-by-row**.

**Structure:**

```
values[]
col_indices[]
row_ptrs[]
```

**Example — Dense Matrix:**

```
1 0 2
0 0 3
4 0 0
```

**CSR Representation:**

```
values      = [1, 2, 3, 4]
col_indices = [0, 2, 2, 0]
row_ptrs    = [0, 2, 3, 4]
```

**Advantages:**

- Efficient row traversal
- Ideal for matrix-vector multiplication
- Good sequential output writes
- Standard sparse HPC format

Matrix-vector multiplication:

$$y = A \times x$$

---

### CSC — Compressed Sparse Column

CSC stores sparse matrices **column-by-column**.

**Structure:**

```
values[]
row_indices[]
col_ptrs[]
```

**Example — Dense Matrix:**

```
1 0 2
0 0 3
4 0 0
```

**CSC Representation:**

```
values      = [1, 4, 2, 3]
row_indices = [0, 2, 0, 1]
col_ptrs    = [0, 2, 2, 4]
```

**Advantages:**

- Efficient column traversal
- Useful for transpose operations
- Better for some sparse solvers
- Good column reuse patterns

---

## Project Features

### Dense → CSR Conversion

Converts dense matrices into CSR format.

**File:** `src/csr.c`

---

### Dense → CSC Conversion

Converts dense matrices into CSC format.

**File:** `src/csc.c`

---

### CSR Sparse Matrix-Vector Multiplication

Implements SpMV using CSR traversal.

**File:** `kernels/scalar/csr_spmv.c`

Time complexity: **O(nnz)** instead of **O(rows × cols)**

---

### CSC Sparse Matrix-Vector Multiplication

Implements SpMV using CSC traversal.

**File:** `kernels/scalar/csc_spmv.c`

---

### Benchmarking Framework

Includes benchmarking infrastructure for:

- CSR kernels
- CSC kernels
- Traversal comparison
- Sparse performance analysis

**File:** `src/benchmark.c`

Uses `clock_gettime(CLOCK_MONOTONIC)` for stable high-resolution timing.

---

### Matrix Generators

Supports generation of:

- Random sparse matrices
- Diagonal matrices
- Banded matrices

**File:** `src/matrix_generator.c`

---

### Memory Compression Analysis

Reports dense vs. sparse storage usage and compression ratio.

**Example output:**

```
Dense Storage     : 8192 KB
CSR Storage       : 632 KB
Compression Ratio : 12.9x
```

---

## Project Structure

```
RVSparseLab/
├── README.md
├── Makefile
├── include/
│   └── sparse.h
├── src/
│   ├── dense.c
│   ├── csr.c
│   ├── csc.c
│   ├── benchmark.c
│   └── matrix_generator.c
├── kernels/
│   ├── scalar/
│   │   ├── csr_spmv.c
│   │   └── csc_spmv.c
│   └── rvv/
│       └── csr_spmv_rvv_stub.c
├── tests/
│   └── test_correctness.c
└── benchmarks/
    └── benchmark_results.md
```

---

## Build Instructions

### Clone the Repository

```bash
git clone https://github.com/SSaadAKHTAR/RVSparseLab.git
cd RVSparseLab
```

### Build

```bash
make
```

### Run Benchmark

```bash
make run
```

### Debug Build

```bash
make debug
```

### Clean Build Files

```bash
make clean
```

---

## Example Output

```
RVSparseLab Benchmark
=================================
Matrix Size : 1024 x 1024
NNZ         : 52341
Density     : 5.00%

CSR Correctness : PASS
CSC Correctness : PASS

CSR SpMV Time : 0.412331 ms
CSC SpMV Time : 0.598121 ms

Memory Statistics
=================================
Dense Storage     : 8192.00 KB
CSR Storage       : 632.00 KB
Compression Ratio : 12.95x
```

---

## Sparse Performance Discussion

Sparse matrix kernels differ significantly from dense linear algebra kernels.

| Property | Dense Kernels | Sparse Kernels |
|---|---|---|
| Bound by | Compute | Memory bandwidth |
| Vectorizability | High | Difficult |
| Cache behavior | Friendly | Irregular |
| Access pattern | Contiguous | Gather/scatter |

---

## Sparse Vectorization Challenges

### Irregular Memory Access

```c
x[col_indices[j]]
```

This creates **gather-style** access patterns. Unlike dense kernels:

- Memory accesses are not contiguous
- Cache efficiency decreases
- Vectorization becomes difficult

### Variable Row Lengths

Sparse rows may contain very few or very many elements, causing:

- Load imbalance
- Vector underutilization

### Cache Misses

Sparse traversal often causes poor spatial locality, irregular access patterns, and memory bandwidth bottlenecks.

---

## RVV-Oriented Design

The project architecture was intentionally designed for future **RISC-V Vector (RVV)** integration.

The `kernels/rvv/` directory contains:

- RVV kernel stubs
- Vectorization notes
- Future optimization planning

### Planned RVV Optimizations

- RVV gather loads
- Vector fused multiply-accumulate (vfmacc)
- Strip mining
- Segmented reductions
- Row blocking
- Vector-friendly sparse traversal
- Hybrid sparse formats

**Target RVV instructions:**

```
vle64.v       # unit-stride load
vluxei64.v    # indexed (gather) load
vfmacc.vv     # fused multiply-accumulate
```

---

## Benchmarking Goals

The benchmarking framework compares:

- CSR vs CSC traversal performance
- Sparse vs dense computation behavior
- Memory efficiency across densities
- Density tradeoff analysis

**Planned experiments:**

- Varying sparsity densities
- Structured sparsity
- Block sparse matrices
- RVV kernel benchmarking

---

## Learning Outcomes

This project strengthened understanding of:

- Sparse matrix formats (CSR, CSC)
- Sparse traversal techniques
- Sparse matrix-vector multiplication
- Benchmarking methodology
- Cache-aware programming
- Systems programming in C
- HPC-oriented code structure
- RISC-V vectorization concepts

---

## Future Work

- Full RVV intrinsics implementation
- Vectorized CSR and CSC kernels
- Hybrid sparse formats
- Parallel sparse kernels with OpenMP
- Sparse matrix-matrix multiplication (SpGEMM)
- Block sparse kernels
- Real-world sparse dataset support (SuiteSparse Matrix Collection)
- Performance visualization

---

## Related LFX Project

This project was built as related work for the **RV-Sparse LFX mentorship project** focused on:

- Sparse linear algebra on RISC-V
- RISC-V Vector Extension (RVV)
- CSR/CSC sparse formats
- RVV vector kernels

Repository: [https://github.com/merledu/rv-sparse](https://github.com/merledu/rv-sparse)

---

## License

This project is licensed under the [MIT License](LICENSE).

---

## Author

**Syed Saad Akhtar**  
Computer Science Student — RISC-V | Hardware Verification | Sparse Linear Algebra | HPC | Vector Computing

- GitHub: [SSaadAKHTAR](https://github.com/SSaadAKHTAR)
- LinkedIn: [syed-saad-akhtar](https://linkedin.com/in/syed-saad-akhtar-a194a8295)