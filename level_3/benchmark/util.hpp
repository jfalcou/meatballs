#ifndef GEMM_BENCHMARK_UTIL_HPP
#define GEMM_BENCHMARK_UTIL_HPP

#include <catch2/catch_config.hpp>
#include <catch2/catch_get_random_seed.hpp>
#include <nanobench.h>

#include <algorithm>
#include <random>
#include <sstream>
#include <vector>

#include <gemm/gemm.hpp>

namespace util
{
    // transposition setting
    constexpr auto no_trans = gemm::transposition::none;

    // Current Catch2 session config data
    inline Catch::ConfigData config_data;

    // output stream used by the reporter
    inline std::ostringstream bench_output;

    // Benchmark runner
    inline auto bench = ankerl::nanobench::Bench().warmup(10).relative(true);

    // Returns a random floating point value
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

    // Naive matrix multiplication
    template<typename T>
    void naive_gemm(int M, int N, int K, T alpha, const T* A, int lda, const T* B, int ldb, T beta, T* C, int ldc) {
        for (int i = 0; i < M; i++) {
            std::transform(&C[i * ldc], &C[(i + 1) * ldc], &C[i * ldc], [&](auto x) { return beta * x; });
            for (int k = 0; k < K; k++) {
                for (int j = 0; j < N; j++) {
                    C[j + i * ldc] += alpha * A[k + i * lda] * B[j + k * ldb];
                }
            }
        }
    }
} // namespace util

#endif
