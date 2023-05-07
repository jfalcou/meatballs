cmake_minimum_required(VERSION 3.0.0)

project(meatballs VERSION 0.1.0)

add_compile_options(-march=native -O3)

# INCLUDES

include(cmake/CPM.cmake)

# eve
CPMAddPackage(
  NAME eve
  GITHUB_REPOSITORY jfalcou/eve
  VERSION 2023.02.15
  OPTIONS "EVE_BUILD_TEST OFF"
          "EVE_BUILD_BENCHMARKS OFF"
          "EVE_BUILD_DOCUMENTATION OFF"
)

# cblas
find_package(BLAS REQUIRED)

# meatballs
include_directories(include)

# TESTS

add_subdirectory(tests)

# BENCHMARKS

add_subdirectory(benchmarks)
