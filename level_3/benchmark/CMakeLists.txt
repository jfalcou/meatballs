set(BLA_VENDOR OpenBLAS)
find_package(BLAS)

CPMAddPackage(
  NAME nanobench
  GITHUB_REPOSITORY martinus/nanobench
  VERSION 4.3.11
)

CPMAddPackage(
  NAME fmt
  GITHUB_REPOSITORY fmtlib/fmt
  GIT_TAG 9.1.0
)

CPMAddPackage(
  NAME catch2
  GITHUB_REPOSITORY catchorg/Catch2
  VERSION 3.3.2
  OPTIONS "CATCH_INSTALL_DOCS OFF" "CATCH_INSTALL_EXTRAS OFF"
)

set(BENCHMARK_SOURCES
  main.cpp
  nanobench.cpp
  benchmark.cpp
  benchmark_reporter.cpp
)

add_executable(benchmark ${BENCHMARK_SOURCES})
target_link_libraries(benchmark PRIVATE gemm::gemm nanobench::nanobench fmt::fmt BLAS::BLAS Catch2::Catch2)
target_compile_options(benchmark PRIVATE -march=native)
target_compile_definitions(benchmark PRIVATE CATCH_FAST_COMPILE)
