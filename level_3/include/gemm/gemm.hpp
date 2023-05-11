#ifndef GEMM_GEMM_HPP
#define GEMM_GEMM_HPP

#include <eve/eve.hpp>
#include <eve/module/algo.hpp>
#include <eve/module/core.hpp>

#include <array>
#include <span>
#include <vector>

#include "gemm/detail/kernels.hpp"

namespace gemm
{
    enum class transposition {
        none,
        transpose,
        conjugate_transpose
    };

    namespace detail
    {
        /**
         * @brief Matrix multiplication of small matrices (M,N,K <= 8)
         */
        template<typename T>
        void gemm_small(
          const int M, const int N, const int K, const T alpha, const T* A, const int lda, const T* B, const int ldb, const T beta, T* C, const int ldc) {
            std::vector<T> ab(M * N);
            detail::get_kernel<T>(M, N, K)(A, lda, B, ldb, ab.data(), N);
            for (int i = 0; i < M; i++) {
                for (int j = 0; j < N; j++) {
                    C[i * ldc + j] = alpha * ab[i * N + j] + beta * C[i * ldc + j];
                }
            }
        }

        // size constants
        template<typename T>
        constexpr int BM = 250; // rows of A

        template<typename T>
        constexpr int BN = 64; // columns of B

        template<typename T>
        constexpr int BK = 70; // columns of A/rows of B

        template<typename T>
        constexpr int TILE_HEIGHT = 10;

        template<typename T>
        constexpr int TILE_WIDTH = eve::wide<T>::size();

        /**
         * @brief Matrix multiplication of matrices of any dimensions
         */
        template<typename T>
        void gemm(
          const int M, const int N, const int K, const T alpha, const T* A, const int lda, const T* B, const int ldb, const T beta, T* C, const int ldc) {
            using wide_t = eve::wide<T>;

            constexpr auto BM = gemm::detail::BM<T>;
            constexpr auto BN = gemm::detail::BN<T>;
            constexpr auto BK = gemm::detail::BK<T>;
            constexpr auto TILE_HEIGHT = gemm::detail::TILE_HEIGHT<T>;
            constexpr auto TILE_WIDTH = gemm::detail::TILE_WIDTH<T>;

            static_assert(BM % TILE_HEIGHT == 0, "BM should be a multiple of the TILE_HEIGHT");
            static_assert(BN % TILE_WIDTH == 0, "BN should be a multiple of the TILE_WIDTH");
            static_assert(BK % TILE_HEIGHT == 0, "BK should be a multiple of the TILE_HEIGHT");

            const int padded_M = ((M + TILE_HEIGHT - 1) / TILE_HEIGHT) * TILE_HEIGHT;
            const int padded_N = ((N + TILE_WIDTH - 1) / TILE_WIDTH) * TILE_WIDTH;

            // work arrays
            std::vector<T> ab(padded_M * padded_N);
            T* AB = ab.data();
            const int ldab = padded_N;

            std::array<T, BM * BK> work_A;
            constexpr int ldwa = BK;
            std::array<T, BK * BN> work_B;
            constexpr int ldwb = BN;

            std::array<wide_t, TILE_HEIGHT> c_tile;

            // "true" dimensions of the current block
            int rem_M;
            int rem_N;
            int rem_K;

            for (int i = 0; i < M; i += BM) {
                rem_M = std::min(M - i, BM);
                for (int k = 0; k < K; k += BK) {
                    rem_K = std::min(K - k, BK);
                    /// Fill work_A
                    std::memset(work_A.data(), 0, work_A.size() * sizeof(T));
                    for (int row = 0; row < rem_M; row++) {
                        std::memcpy(work_A.data() + row * ldwa, A + (i + row) * lda + k, rem_K * sizeof(T));
                    }

                    for (int j = 0; j < N; j += BN) {
                        rem_N = std::min(N - j, BN);
                        /// Fill work_B
                        std::memset(work_B.data(), 0, work_B.size() * sizeof(T));
                        for (int row = 0; row < rem_K; row++) {
                            std::memcpy(work_B.data() + row * ldwb, B + (k + row) * ldb + j, rem_N * sizeof(T));
                        }

                        /// Block
                        for (int bi = 0; bi < rem_M; bi += TILE_HEIGHT) {
                            for (int bj = 0; bj < rem_N; bj += TILE_WIDTH) {
                                /// Kernel
                                // Load tile of C
                                for (int tile_i = 0; tile_i < TILE_HEIGHT; tile_i++) {
                                    c_tile[tile_i] = wide_t{AB + (i + bi + tile_i) * ldab + (j + bj)};
                                }

                                // Compute C <- A*B
                                for (int bk = 0; bk < rem_K; bk++) {
                                    const wide_t wb{work_B.data() + bk * ldwb + bj};
                                    for (int tile_i = 0; tile_i < TILE_HEIGHT; tile_i++) {
                                        c_tile[tile_i] = eve::fma(work_A[(bi + tile_i) * ldwa + bk], wb, c_tile[tile_i]);
                                    }
                                }

                                // Store tile of C
                                for (int tile_i = 0; tile_i < TILE_HEIGHT; tile_i++) {
                                    eve::store(c_tile[tile_i], AB + (i + bi + tile_i) * ldab + (j + bj));
                                }
                                /// End of kernel
                            }
                        }
                        /// End of block
                    }
                }
            }

            for (int line = 0; line < M; line++) {
                auto c = std::span(C + line * ldc, N);
                auto ab = std::span(AB + line * ldab, N);
                eve::algo::transform_to(eve::views::zip(ab, c), c, [alpha, beta](auto x) { return eve::fma(alpha, eve::get<0>(x), beta * eve::get<1>(x)); });
            }
        }
    } // namespace detail

    /**
     * @brief Performs the operation `C = alpha * AB  + beta * C`.
     *
     * @note This function only chooses the appropriate function to call depending on the matrices' dimensions:
     * - If the matrices are small enough, we call `gemm_small` which directly calls the corresponding
     *   microkernel. Doing so allows to avoid the overhead of blocking/padding in the other version.
     * - Otherwise, we call `gemm`.
     *
     * @param M the number of rows of `A` and `C`
     * @param N the number of columns of `B` and `C`
     * @param K the number of columns of `A` / rows of `B`
     * @param alpha The multiplier of `AB`
     * @param A An array of size `M * lda`
     * @param lda The "true" first dimension of `A`, that is the number of elements between two rows of `A`
     *            as declared in the calling program. Note that `lda` >= `K` should hold true, otherwise the
     *            behaviour is undefined.
     * @param B An array of size `K * ldb`
     * @param ldb The "true" first dimension of `B`, that is the number of elements between two rows of `B`
     *            as declared in the calling program. Note that `ldb` >= `N` should hold true, otherwise the
     *            behaviour is undefined.
     * @param beta The multiplier of `C`
     * @param C An array of size `M * ldc`
     * @param ldc The "true" first dimension of `C`, that is the number of elements between two rows of `C`
     *            as declared in the calling program. Note that `ldc` >= `N` should hold true, otherwise the
     *            behaviour is undefined.
     */
    template<typename T>
    void gemm(transposition, transposition, const int M, const int N, const int K, const T alpha, const T* A, const int lda, const T* B, const int ldb,
      const T beta, T* C, const int ldc) {
        // no transposition for the moment
        if (M <= 8 && N <= 8 && K <= 8) {
            detail::gemm_small(M, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
        } else {
            detail::gemm(M, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
        }
    }

    /**
     * @brief Performs simple precision matrix-matrix multiplication.
     */
    inline auto sgemm = gemm<float>;

    /**
     * @brief Performs double precision matrix-matrix multiplication.
     */
    inline auto dgemm = gemm<double>;

} // namespace gemm

#endif
