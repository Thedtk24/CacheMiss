# CacheMiss — Row-Major vs Column-Major Array Traversal in C

> **Experimental analysis of cache miss impact on CPU performance**  
> Thed Arthur

---

## Overview

This repository contains all the materials for the study:

**"Row-Major vs Column-Major Array Traversal in C: An Experimental Analysis of Cache Miss Impact on CPU Performance"**

The goal is to demonstrate, concretely and with hardware evidence, why iterating a 2D array as `tab[j][i]` with `j` as the outer loop is significantly slower than `tab[i][j]` — and to explain exactly what happens inside the CPU.

**Key results (AMD Ryzen 7 3700U, N=4096, -O2):**
- Column-major generates **20× more cache misses** than row-major
- **3.7× execution time slowdown**
- Vectorization drops from **100% to 33%** (MAQAO)
- Array Access Efficiency: **100% vs 51.1%** (MAQAO)

---

## Reproducing the Benchmark

### Requirements

```bash
sudo apt install gcc make linux-perf valgrind hwloc
# MAQAO: https://maqao.org
```

### Compile

```bash
# -O0
gcc -O0 -o bench_O0 src/benchmark.c -lm

# -O2
gcc -O2 -o bench_O2 src/benchmark.c -lm
```

### Run the full campaign

```bash
echo "size,row_ms,col_ms" > reports/raw/results_O2.csv
for size in 64 128 256 512 1024 2048 4096; do
    for run in 1 2 3 4 5; do
        ./bench_O2 $size row >> reports/raw/results_O2.csv
    done
done
```

> Repeat with `bench_O0` for the `-O0` dataset.

### perf stat (hardware counters)

```bash
perf stat -e cache-misses,cache-references,L1-dcache-load-misses \
    ./bench_O2 4096 row

perf stat -e cache-misses,cache-references,L1-dcache-load-misses \
    ./bench_O2 4096 col
```

### MAQAO OneView

```bash
maqao oneview -R1 -- ./bench 4096 row
maqao oneview -R1 -- ./bench 4096 col
```

---

## Generate Figures

```bash
python3 reports/graphs.py
```

Outputs `comparison_O0_O2.png` and `ratio_col_over_row.png` in `reports/figures/`.

---

## Hardware Environment

| Component | Spec |
|---|---|
| CPU | AMD Ryzen 7 3700U (Zen+, 4C/8T) |
| L1d / L1i | 32 KB / 64 KB per core |
| L2 | 512 KB per core |
| L3 (LLC) | 4 MB shared |
| Cache line | 64 bytes |
| RAM | 5795 MB |
| OS | Ubuntu Linux |