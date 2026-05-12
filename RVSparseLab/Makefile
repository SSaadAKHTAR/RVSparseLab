# ============================================================
# RVSparseLab
# Lightweight Sparse Linear Algebra Playground for RISC-V
# ============================================================

CC = gcc

# ============================================================
# Compiler Flags
# ============================================================

CFLAGS = -O3 -Wall -Wextra -std=c11 -march=native

# ============================================================
# Include Paths
# ============================================================

INCLUDES = -Iinclude

# ============================================================
# Source Files
# ============================================================

SRC = \
	src/dense.c \
	src/matrix_generator.c \
	src/csr.c \
	src/csc.c \
	src/benchmark.c \
	kernels/scalar/csr_spmv.c \
	kernels/scalar/csc_spmv.c \
	kernels/rvv/csr_spmv_rvv_stub.c \
	tests/test_correctness.c

# ============================================================
# Output Binary
# ============================================================

TARGET = rvsparselab

# ============================================================
# Build Target
# ============================================================

all:
	$(CC) $(CFLAGS) $(INCLUDES) $(SRC) -o $(TARGET) -lm

# ============================================================
# Run Benchmark/Test
# ============================================================

run: all
	./$(TARGET)

# ============================================================
# Debug Build
# ============================================================

debug:
	$(CC) -g -O0 -Wall -Wextra -std=c11 \
	$(INCLUDES) $(SRC) -o $(TARGET)_debug -lm

# ============================================================
# Clean Build Files
# ============================================================

clean:
	rm -f $(TARGET)
	rm -f $(TARGET)_debug

# ============================================================
# Help
# ============================================================

help:
	@echo "Available targets:"
	@echo ""
	@echo "make        -> Build project"
	@echo "make run    -> Build and run benchmark"
	@echo "make debug  -> Debug build"
	@echo "make clean  -> Remove binaries"