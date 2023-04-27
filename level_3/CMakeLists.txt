cmake_minimum_required(VERSION 3.14)

project(gemm)

option(GEMM_BUILD_TEST "Build the test executable" OFF)
option(GEMM_USE_CTEST "Use CTest" OFF)
option(GEMM_BUILD_BENCHMARK "Build the benchmark executable" OFF)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")

include(CPM)

CPMAddPackage(
  NAME eve
  GITHUB_REPOSITORY jfalcou/eve
  VERSION 2023.02.15
  OPTIONS "EVE_BUILD_TEST OFF" 
	  "EVE_BUILD_BENCHMARKS OFF"
	  "EVE_BUILD_DOCUMENTATION OFF"
)

add_library(gemm INTERFACE)
target_include_directories(gemm INTERFACE include)
target_link_libraries(gemm INTERFACE eve::eve)
target_compile_features(gemm INTERFACE cxx_std_20)
add_library(gemm::gemm ALIAS gemm)

if(GEMM_BUILD_TEST)
  add_subdirectory(test)
endif()

if(GEMM_BUILD_BENCHMARK)
  add_subdirectory(benchmark)
endif()
