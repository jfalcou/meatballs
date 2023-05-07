# INCLUDES

# cblas
find_package(BLAS REQUIRED)

# TESTS

add_executable(test_level_1 level_1.cpp)
target_link_libraries(test_level_1 eve::eve BLAS::BLAS)

add_executable(test_level_2 level_2.cpp)
target_link_libraries(test_level_2 eve::eve BLAS::BLAS)
