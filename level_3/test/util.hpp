#ifndef GEMM_TEST_UTIL_HPP
#define GEMM_TEST_UTIL_HPP

#include <catch2/catch_get_random_seed.hpp>
#include <cblas.h>

#include <random>
#include <vector>

#include <gemm/gemm.hpp>

namespace util
{
    // Precision for floating point relative comparisons
    template<typename T>
    constexpr T precision = 1e-5;

    template<>
    inline constexpr auto precision<float> = 1e-3f;

    template<>
    inline constexpr auto precision<double> = 1e-7;

    template<typename T>
    T random_float() {
        static std::mt19937 gen(Catch::getSeed());
        static std::uniform_real_distribution<T> dist(-10, 10);
        return dist(gen);
    }

    // Generates a vector of random floating point values
    template<typename T>
    std::vector<T> random_vector(int size) {
        std::vector<T> v(size);
        for (auto& e : v) {
            e = random_float<T>();
        }

        return v;
    }

    // Wrapper for the gemm function
    template<typename T>
    void gemm(const int M, const int N, const int K, const T alpha, const T* A, const int lda, const T* B, const int ldb, const T beta, T* C, const int ldc) {
        gemm::gemm<T>(gemm::transposition::none, gemm::transposition::none, M, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
    }

    // Wrapper for the openblas [s|d]gemm function
    template<typename T>
    void cblas_gemm(
      const int M, const int N, const int K, const T alpha, const T* A, const int lda, const T* B, const int ldb, const T beta, T* C, const int ldc) {
        if constexpr (std::is_same_v<T, float>) {
            cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, M, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
        } else {
            cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, M, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
        }
    }
} // namespace util

#endif
