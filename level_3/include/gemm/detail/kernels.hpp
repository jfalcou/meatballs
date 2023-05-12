#ifndef GEMM_KERNELS_HPP
#define GEMM_KERNELS_HPP

#include <algorithm>
#include <array>
#include <utility>

#include "kernels_1xx.hpp"
#include "kernels_2xx.hpp"
#include "kernels_4xx.hpp"
#include "kernels_8xx.hpp"

namespace gemm::detail
{
    template<typename T>
    using kernel = void (*)(const T*, int, const T*, int, T*, int);

    template<typename T>
    constexpr kernel<T> get_kernel(const int M, const int N, const int K);

    /**
     * Maximum dimension of the kernels (handwritten and composed) generated
     * at compile time.
     */
    constexpr int kernel_max_dim = 16;

    constexpr bool is_handwritten_M(int M) {
        return M == 1 || M == 2 || M == 4 || M == 8;
    }

    constexpr bool is_handwritten_N(int N) {
        return N == 1 || N == 2 || N == 4 || N == 8;
    }

    constexpr bool is_handwritten_K(int K) {
        return K == 1 || K == 2 || K == 4 || K == 8;
    }

    /**
     * @brief Tells if a kernel has an handwritten version, given the matrices dimensions.
     */
    constexpr bool is_handwritten_kernel(int M, int N, int K) {
        return is_handwritten_M(M) && is_handwritten_N(N) && is_handwritten_K(K);
    }

    /**
     * @brief Get the highest value y such that y <= x && pred(y) == true.
     */
    template<typename Predicate>
    constexpr int get_previous_valid_value(int x, Predicate pred) {
        while (!pred(x)) {
            x--;
        }
        return x;
    }

    /**
     * @brief Creates a kernel which can multiply MxK and KxN matrices.
     * This function combines multiple handwritten kernels in order to handle other dimensions.
     */
    template<typename T, int M, int N, int K>
        requires(M > 0 && N > 0 && K > 0)
    constexpr void composed_kernel(const T* a, int lda, const T* b, int ldb, T* c, int ldc) {
        if constexpr (is_handwritten_kernel(M, N, K)) {
            get_kernel<T>(M, N, K)(a, lda, b, ldb, c, ldc);
        } else {
            constexpr auto split_dim = std::max({
                M * !is_handwritten_M(M),
                N * !is_handwritten_N(N),
                K * !is_handwritten_K(K)
            });

            if constexpr (split_dim == M) {
                constexpr auto split = get_previous_valid_value(M, is_handwritten_M);
                composed_kernel<T, split, N, K>(a, lda, b, ldb, c, ldc);
                composed_kernel<T, M - split, N, K>(a + split * lda, lda, b, ldb, c + split * ldc, ldc);
            } else if constexpr (split_dim == N) {
                constexpr auto split = get_previous_valid_value(N, is_handwritten_N);
                composed_kernel<T, M, split, K>(a, lda, b, ldb, c, ldc);
                composed_kernel<T, M, N - split, K>(a, lda, b + split, ldb, c + split, ldc);
            } else { // split_dim == K
                constexpr auto split = get_previous_valid_value(K, is_handwritten_K);
                composed_kernel<T, M, N, split>(a, lda, b, ldb, c, ldc);
                composed_kernel<T, M, N, K - split>(a + split, lda, b + split * ldb, ldb, c, ldc);
            }
        }
    }


    /**
     * @brief Gets the index of a specific kernel in the kernels table given the matrices dimensions
     */
    constexpr int kernel_index(int M, int N, int K) {
        return kernel_max_dim * kernel_max_dim * (M - 1) + kernel_max_dim * (N - 1) + K - 1;
    }

    /**
     * Total number of kernels
     */
    constexpr int nb_kernels = kernel_max_dim * kernel_max_dim * kernel_max_dim;

    /**
     * @brief Fills an array with pointers to the kernels for M,N,K <= kernel_max_dim
     */
    template<typename T>
    consteval std::array<kernel<T>, nb_kernels> generate_kernel_table() {
        std::array<kernel<T>, nb_kernels> kernels{};

        // set the handwritten kernels manually
        kernels[kernel_index(1, 1, 1)] = &kernel_111;
        kernels[kernel_index(1, 2, 1)] = &kernel_112;
        kernels[kernel_index(1, 4, 1)] = &kernel_114;
        kernels[kernel_index(1, 8, 1)] = &kernel_118;
        kernels[kernel_index(1, 1, 2)] = &kernel_121;
        kernels[kernel_index(1, 2, 2)] = &kernel_122;
        kernels[kernel_index(1, 4, 2)] = &kernel_124;
        kernels[kernel_index(1, 8, 2)] = &kernel_128;
        kernels[kernel_index(1, 1, 4)] = &kernel_141;
        kernels[kernel_index(1, 2, 4)] = &kernel_142;
        kernels[kernel_index(1, 4, 4)] = &kernel_144;
        kernels[kernel_index(1, 8, 4)] = &kernel_148;
        kernels[kernel_index(1, 1, 8)] = &kernel_181;
        kernels[kernel_index(1, 2, 8)] = &kernel_182;
        kernels[kernel_index(1, 4, 8)] = &kernel_184;
        kernels[kernel_index(1, 8, 8)] = &kernel_188;
        kernels[kernel_index(2, 1, 1)] = &kernel_211;
        kernels[kernel_index(2, 2, 1)] = &kernel_212;
        kernels[kernel_index(2, 4, 1)] = &kernel_214;
        kernels[kernel_index(2, 8, 1)] = &kernel_218;
        kernels[kernel_index(2, 1, 2)] = &kernel_221;
        kernels[kernel_index(2, 2, 2)] = &kernel_222;
        kernels[kernel_index(2, 4, 2)] = &kernel_224;
        kernels[kernel_index(2, 8, 2)] = &kernel_228;
        kernels[kernel_index(2, 1, 4)] = &kernel_241;
        kernels[kernel_index(2, 2, 4)] = &kernel_242;
        kernels[kernel_index(2, 4, 4)] = &kernel_244;
        kernels[kernel_index(2, 8, 4)] = &kernel_248;
        kernels[kernel_index(2, 1, 8)] = &kernel_281;
        kernels[kernel_index(2, 2, 8)] = &kernel_282;
        kernels[kernel_index(2, 4, 8)] = &kernel_284;
        kernels[kernel_index(2, 8, 8)] = &kernel_288;
        kernels[kernel_index(4, 1, 1)] = &kernel_411;
        kernels[kernel_index(4, 2, 1)] = &kernel_412;
        kernels[kernel_index(4, 4, 1)] = &kernel_414;
        kernels[kernel_index(4, 8, 1)] = &kernel_418;
        kernels[kernel_index(4, 1, 2)] = &kernel_421;
        kernels[kernel_index(4, 2, 2)] = &kernel_422;
        kernels[kernel_index(4, 4, 2)] = &kernel_424;
        kernels[kernel_index(4, 8, 2)] = &kernel_428;
        kernels[kernel_index(4, 1, 4)] = &kernel_441;
        kernels[kernel_index(4, 2, 4)] = &kernel_442;
        kernels[kernel_index(4, 4, 4)] = &kernel_444;
        kernels[kernel_index(4, 8, 4)] = &kernel_448;
        kernels[kernel_index(4, 1, 8)] = &kernel_481;
        kernels[kernel_index(4, 2, 8)] = &kernel_482;
        kernels[kernel_index(4, 4, 8)] = &kernel_484;
        kernels[kernel_index(4, 8, 8)] = &kernel_488;
        kernels[kernel_index(8, 1, 1)] = &kernel_811;
        kernels[kernel_index(8, 2, 1)] = &kernel_812;
        kernels[kernel_index(8, 4, 1)] = &kernel_814;
        kernels[kernel_index(8, 8, 1)] = &kernel_818;
        kernels[kernel_index(8, 1, 2)] = &kernel_821;
        kernels[kernel_index(8, 2, 2)] = &kernel_822;
        kernels[kernel_index(8, 4, 2)] = &kernel_824;
        kernels[kernel_index(8, 8, 2)] = &kernel_828;
        kernels[kernel_index(8, 1, 4)] = &kernel_841;
        kernels[kernel_index(8, 2, 4)] = &kernel_842;
        kernels[kernel_index(8, 4, 4)] = &kernel_844;
        kernels[kernel_index(8, 8, 4)] = &kernel_848;
        kernels[kernel_index(8, 1, 8)] = &kernel_881;
        kernels[kernel_index(8, 2, 8)] = &kernel_882;
        kernels[kernel_index(8, 4, 8)] = &kernel_884;
        kernels[kernel_index(8, 8, 8)] = &kernel_888;

        // add the composed kernels
        constexpr auto dimensions = std::integer_sequence<int, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16>{};

        auto set_kernel = [&]<int M, int N, int K>() {
            if (!is_handwritten_kernel(M, N, K)) {
                kernels[kernel_index(M, N, K)] = &composed_kernel<T, M, N, K>;
            }
        };

        auto K_loop = [&]<int M, int N, int... Ks>(std::integer_sequence<int, Ks...>) {
            (set_kernel.template operator()<M, N, Ks>(), ...);
        };

        auto N_loop = [&]<int M, int... Ns>(std::integer_sequence<int, Ns...>) {
            (K_loop.template operator()<M, Ns>(dimensions), ...);
        };

        auto M_loop = [&]<int... Ms>(std::integer_sequence<int, Ms...>) {
            (N_loop.template operator()<Ms>(dimensions), ...);
        };

        M_loop(dimensions);

        return kernels;
    }

    /**
     * @brief Table containing the kernels for small matrices multiplication.
     */
    template<typename T>
    constexpr auto kernels_table = generate_kernel_table<T>();

    /**
     * @brief Returns the kernel for multiplying a MxK matrix with a KxN matrix.
     */
    template<typename T>
    constexpr kernel<T> get_kernel(const int M, const int N, const int K) {
        return kernels_table<T>[kernel_index(M, N, K)];
    }

} // namespace gemm::detail

#endif
