# gemm

A C++ implementation of blas general matrix-matrix multiplication routines (xgemm).

## Build

The library is header only, you just have to copy the files located in the
`include` folder to use it.

In order to build the tests/benchmarks, you will need openblas installed on
your system.

The tests and benchmarks can then be built and ran with [CMake](https://cmake.org/):

```bash
$ cmake -S . -B build -DGEMM_BUILD_TEST=ON -DGEMM_BUILD_BENCHMARK=ON # -DGEMM_USE_CTEST=ON
$ cmake --build build --target test --target benchmark
$ ./build/test/test
$ ./build/benchmark/benchmark --reporter=benchmark
```

or with [xmake](https://xmake.io):

```bash
$ xmake
$ xmake build
$ xmake run test
$ xmake run benchmark --reporter=benchmark
```

## Benchmark

Some benchmark results are available [here](./benchmark/results.md), they were
ran on a AMD Ryzen 5 3500u cpu, locked at 2100MHz. The program was compiled
with `GCC 12.2.1` and the `-O3 -march=native` options.

In the benchmarks, the floating point version `gemm<float>` is run against
openblas' `sgemm` and, for small enough matrices, a naive algorithm (with the
loop swapping optimization).

## TODO

- [x] Integrate the kernels to the main matrix multiplication function
	- [x] Have a working implementation
	- [x] Fix performance issues
- [x] Microkernels
	- [x] Kernel composition function
	- [x] 1x(1, 2, 4, 8)x(1, 2, 4, 8) kernels
	- [x] 2x(1, 2, 4, 8)x(1, 2, 4, 8) kernels
	- [x] 4x(1, 2, 4, 8)x(1, 2, 4, 8) kernels
	- [x] 8x(1, 2, 4, 8)x(1, 2, 4, 8) kernels
- [ ] Tests
	- [x] Kernels
	- [x] Big matrices
	- [ ] Fix precision issues
	- [x] Double
- [ ] Benchmarks
	- [x] Small matrices
	- [x] Big matrices
	- [ ] Double

