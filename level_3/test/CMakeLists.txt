set(BLA_VENDOR OpenBLAS)
find_package(BLAS)

CPMAddPackage(
  NAME catch2
  GITHUB_REPOSITORY catchorg/Catch2
  VERSION 3.3.2
  OPTIONS "CATCH_INSTALL_DOCS OFF" "CATCH_INSTALL_EXTRAS OFF"
)

set(TEST_SOURCES
  kernels.cpp
  square.cpp
  various_dimensions.cpp
  special_cases.cpp
)

add_executable(test ${TEST_SOURCES})
target_link_libraries(test PRIVATE gemm::gemm BLAS::BLAS Catch2::Catch2WithMain)
target_compile_options(test PRIVATE -march=native)
target_compile_definitions(test PRIVATE CATCH_FAST_COMPILE)

if (GEMM_USE_CTEST)
  list(APPEND CMAKE_MODULE_PATH "${catch2_SOURCE_DIR}/extras")
  include(CTest)
  include(Catch)
  catch_discover_tests(test)
endif()
