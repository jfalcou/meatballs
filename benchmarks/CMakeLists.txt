# INCLUDES

# nanobench
CPMAddPackage(
  NAME nanobench
  GITHUB_REPOSITORY martinus/nanobench
  VERSION 4.3.11 
)

# cblas
find_package(BLAS REQUIRED)

# BENCHMARKS

add_executable(benchmark_level_1 level_1.cpp)
target_link_libraries(benchmark_level_1 eve::eve BLAS::BLAS nanobench::nanobench)

add_executable(benchmark_level_2 level_2.cpp)
target_link_libraries(benchmark_level_2 eve::eve BLAS::BLAS nanobench::nanobench)
