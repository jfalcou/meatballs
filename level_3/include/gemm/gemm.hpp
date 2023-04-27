#ifndef GEMM_GEMM_HPP
#define GEMM_GEMM_HPP

#include <eve/eve.hpp>
#include <eve/module/algo.hpp>
#include <eve/module/core.hpp>

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
         * @brief Gives the size of a B1 tile for a type T
         * @return a size B1 such that 3 blocs of B1xB1 elements of type
         *         T can fit in 64 KiB
         */
        template<typename T>
        constexpr int get_B1_size() {
            if constexpr (sizeof(T) == 1) {
                return 128;
            } else if constexpr (sizeof(T) == 2) {
                return 64;
            } else if constexpr (sizeof(T) == 4) {
                return 64;
            } else {
                return 32;
            }
        }

        // Size of a tile
        template<typename T>
        constexpr int TILE_SIZE = eve::wide<T>::size();

        // Size of a small (L1) block
        template<typename T>
        constexpr int B1 = get_B1_size<T>();

        // Size of a big (L2) block
        template<typename T>
        constexpr int B2 = 4 * B1<T>;

        // Function used to multiply two tiles
        template<typename T>
        constexpr kernel<T> tile_kernel = get_kernel<T>(TILE_SIZE<T>, TILE_SIZE<T>, TILE_SIZE<T>);


        // Multiplies two L1 blocks
        template<typename T>
        void kernel_B1_B1_B1(const T* A, const int lda, const T* B, const int ldb, T* C, const int ldc) {
            for (int i = 0; i < B1<T>; i += TILE_SIZE<T>) {
                T* base_C = C + i * ldc;
                for (int k = 0; k < B1<T>; k += TILE_SIZE<T>) {
                    const T* a = A + i * lda + k;
                    for (int j = 0; j < B1<T>; j += TILE_SIZE<T>) {
                        tile_kernel<T>(a, lda, B + k * ldb + j, ldb, base_C + j, ldc);
                    }
                }
            }
        }

        // Multiplies two L2 blocks
        template<typename T>
        void kernel_B2_B2_B2(const T* A, const int lda, const T* B, const int ldb, T* C, const int ldc) {
            for (int i = 0; i < B2<T>; i += B1<T>) {
                for (int k = 0; k < B2<T>; k += B1<T>) {
                    for (int j = 0; j < B2<T>; j += B1<T>) {
                        kernel_B1_B1_B1(A + i * lda + k, lda, B + k * ldb + j, ldb, C + i * ldc + j, ldc);
                    }
                }
            }
        }

        ///////////////////////////////////////////////////////////////////

        // Handles the multiplication of the last K columns of A with the last K lines of B (K < B1<T>)
        template<typename T>
        void kernel_B1_K_B1(const int K, const T* A, const int lda, const T* B, const int ldb, T* C, const int ldc) {
            const int remaining_K = K % TILE_SIZE<T>;
            const int k_lim = K - remaining_K;
            auto kernel = get_kernel<T>(TILE_SIZE<T>, TILE_SIZE<T>, remaining_K);

            for (int i = 0; i < B1<T>; i += TILE_SIZE<T>) {
                const T* base_A = A + i * lda;
                T* base_C = C + i * ldc;
                for (int k = 0; k < k_lim; k += TILE_SIZE<T>) {
                    const T* a = base_A + k;
                    for (int j = 0; j < B1<T>; j += TILE_SIZE<T>) {
                        tile_kernel<T>(a, lda, B + k * ldb + j, ldb, base_C + j, ldc);
                    }
                }

                if (remaining_K > 0) {
                    for (int j = 0; j < B1<T>; j += TILE_SIZE<T>) {
                        kernel(base_A + k_lim, lda, B + k_lim * ldb + j, ldb, base_C + j, ldc);
                    }
                }
            }
        }

        // Handles the multiplication of the last K columns of A with the last K lines of B (K < B2<T>)
        template<typename T>
        void kernel_B2_K_B2(const int K, const T* A, const int lda, const T* B, const int ldb, T* C, const int ldc) {
            const int remaining_K = K % B1<T>;
            const int k_lim = K - remaining_K;

            for (int i = 0; i < B2<T>; i += B1<T>) {
                const T* base_A = A + i * lda;
                T* base_C = C + i * ldc;
                for (int k = 0; k < k_lim; k += B1<T>) {
                    for (int j = 0; j < B2<T>; j += B1<T>) {
                        kernel_B1_B1_B1(base_A + k, lda, B + k * ldb + j, ldb, base_C + j, ldc);
                    }
                }

                if (remaining_K > 0) {
                    for (int j = 0; j < B2<T>; j += B1<T>) {
                        kernel_B1_K_B1(remaining_K, base_A + k_lim, lda, B + k_lim * ldb + j, ldb, base_C + j, ldc);
                    }
                }
            }
        }

        ///////////////////////////////////////////////////////////////////

        /**
         * @brief Multiplies a B1 block of A with the last (B1xN) part of a line of B
         * @note N < B1<T>
         */
        template<typename T>
        void kernel_B1_B1_N(const int N, const T* A, const int lda, const T* B, const int ldb, T* C, const int ldc) {
            const int remaining_N = N % TILE_SIZE<T>;
            const int j_lim = N - remaining_N;
            auto kernel = get_kernel<T>(TILE_SIZE<T>, remaining_N, TILE_SIZE<T>);

            for (int i = 0; i < B1<T>; i += TILE_SIZE<T>) {
                const T* base_A = A + i * lda;
                T* base_C = C + i * ldc;
                for (int k = 0; k < B1<T>; k += TILE_SIZE<T>) {
                    const T* a = base_A + k;
                    for (int j = 0; j < j_lim; j += TILE_SIZE<T>) {
                        tile_kernel<T>(a, lda, B + k * ldb + j, ldb, base_C + j, ldc);
                    }
                    if (remaining_N > 0) {
                        kernel(base_A + k, lda, B + k * ldb + j_lim, ldb, base_C + j_lim, ldc);
                    }
                }
            }
        }

        /**
         * @brief Multiplies a B2 block of A with the last (B2xN) part of a line of B
         * @note N < B1<T>
         */
        template<typename T>
        void kernel_B2_B2_N(const int N, const T* A, const int lda, const T* B, const int ldb, T* C, const int ldc) {
            const int remaining_N = N % B1<T>;
            const int j_lim = N - remaining_N;

            for (int i = 0; i < B2<T>; i += B1<T>) {
                for (int k = 0; k < B2<T>; k += B1<T>) {
                    for (int j = 0; j < j_lim; j += B1<T>) {
                        kernel_B1_B1_B1(A + i * lda + k, lda, B + k * ldb + j, ldb, C + i * ldc + j, ldc);
                    }
                    if (remaining_N > 0) {
                        kernel_B1_B1_N(remaining_N, A + i * lda + k, lda, B + k * ldb + j_lim, ldb, C + i * ldc + j_lim, ldc);
                    }
                }
            }
        }

        ///////////////////////////////////////////////////////////////////

        /**
         * @brief Multiplies the last (B1xK) part of a line of A with the lower right corner of B
         * @note K < B1, N < B1
         */
        template<typename T>
        void kernel_B1_K_N(const int N, const int K, const T* A, const int lda, const T* B, const int ldb, T* C, const int ldc) {
            const int remaining_N = N % TILE_SIZE<T>;
            const int j_lim = N - remaining_N;

            const int remaining_K = K % TILE_SIZE<T>;
            const int k_lim = K - remaining_K;

            auto kernel_BT_K_N = get_kernel<T>(TILE_SIZE<T>, remaining_N, remaining_K);
            auto kernel_BT_BT_N = get_kernel<T>(TILE_SIZE<T>, remaining_N, TILE_SIZE<T>);
            auto kernel_BT_K_BT = get_kernel<T>(TILE_SIZE<T>, TILE_SIZE<T>, remaining_K);

            for (int i = 0; i < B1<T>; i += TILE_SIZE<T>) {
                const T* base_A = A + i * lda;
                T* base_C = C + i * ldc;
                for (int k = 0; k < k_lim; k += TILE_SIZE<T>) {
                    const T* a = base_A + k;
                    for (int j = 0; j < j_lim; j += TILE_SIZE<T>) {
                        tile_kernel<T>(a, lda, B + k * ldb + j, ldb, base_C + j, ldc);
                    }
                    if (remaining_N > 0) {
                        kernel_BT_BT_N(base_A + k, lda, B + k * ldb + j_lim, ldb, base_C + j_lim, ldc);
                    }
                }

                if (remaining_K > 0) {
                    for (int j = 0; j < j_lim; j += TILE_SIZE<T>) {
                        kernel_BT_K_BT(base_A + k_lim, lda, B + k_lim * ldb + j, ldb, base_C + j, ldc);
                    }

                    if (remaining_N > 0) {
                        kernel_BT_K_N(base_A + k_lim, lda, B + k_lim * ldb + j_lim, ldb, base_C + j_lim, ldc);
                    }
                }
            }
        }

        /**
         * @brief Multiplies the last (B2xK) part of a line of A with the lower right corner of B
         * @note K < B2, N < B2
         */
        template<typename T>
        void kernel_B2_K_N(const int N, const int K, const T* A, const int lda, const T* B, const int ldb, T* C, const int ldc) {
            const int remaining_K = K % B1<T>;
            const int k_lim = K - remaining_K;

            const int remaining_N = N % B1<T>;
            const int j_lim = N - remaining_N;

            for (int i = 0; i < B2<T>; i += B1<T>) {
                const T* base_A = A + i * lda;
                T* base_C = C + i * ldc;
                for (int k = 0; k < k_lim; k += B1<T>) {
                    for (int j = 0; j < j_lim; j += B1<T>) {
                        kernel_B1_B1_B1(base_A + k, lda, B + k * ldb + j, ldb, base_C + j, ldc);
                    }
                    if (remaining_N > 0) {
                        kernel_B1_B1_N(remaining_N, base_A + k, lda, B + k * ldb + j_lim, ldb, base_C + j_lim, ldc);
                    }
                }
                if (remaining_K > 0) {
                    for (int j = 0; j < j_lim; j += B1<T>) {
                        kernel_B1_K_B1(remaining_K, base_A + k_lim, lda, B + k_lim * ldb + j, ldb, base_C + j, ldc);
                    }
                    if (remaining_N > 0) {
                        kernel_B1_K_N(remaining_N, remaining_K, base_A + k_lim, lda, B + k_lim * ldb + j_lim, ldb, base_C + j_lim, ldc);
                    }
                }
            }
        }

        /**
         * @brief Multiplies the last (MxB1) part of a column of A with a B1 block of B
         * @note M < B1
         */
        template<typename T>
        void kernel_M_B1_B1(const int M, const T* A, const int lda, const T* B, const int ldb, T* C, const int ldc) {
            const int remaining_M = M % TILE_SIZE<T>;
            const int i_lim = M - remaining_M;
            auto kernel = get_kernel<T>(remaining_M, TILE_SIZE<T>, TILE_SIZE<T>);

            for (int i = 0; i < i_lim; i += TILE_SIZE<T>) {
                const T* base_A = A + i * lda;
                T* base_C = C + i * ldc;
                for (int k = 0; k < B1<T>; k += TILE_SIZE<T>) {
                    const T* a = base_A + k;
                    for (int j = 0; j < B1<T>; j += TILE_SIZE<T>) {
                        tile_kernel<T>(a, lda, B + k * ldb + j, ldb, base_C + j, ldc);
                    }
                }
            }

            if (remaining_M > 0) {
                const T* base_A = A + i_lim * lda;
                T* base_C = C + i_lim * ldc;
                for (int k = 0; k < B1<T>; k += TILE_SIZE<T>) {
                    for (int j = 0; j < B1<T>; j += TILE_SIZE<T>) {
                        kernel(base_A + k, lda, B + k * ldb + j, ldb, base_C + j, ldb);
                    }
                }
            }
        }

        /**
         * @brief Multiplies the last (MxB2) part of a column of A with a B2 block of B
         * @note M < B2
         */
        template<typename T>
        void kernel_M_B2_B2(const int M, const T* A, const int lda, const T* B, const int ldb, T* C, const int ldc) {
            const int remaining_M = M % B1<T>;
            const int i_lim = M - remaining_M;

            for (int i = 0; i < i_lim; i += B1<T>) {
                const T* base_A = A + i * lda;
                T* base_C = C + i * ldc;
                for (int k = 0; k < B2<T>; k += B1<T>) {
                    for (int j = 0; j < B2<T>; j += B1<T>) {
                        kernel_B1_B1_B1(base_A + k, lda, B + k * ldb + j, ldb, base_C + j, ldc);
                    }
                }
            }

            if (remaining_M > 0) {
                const T* base_A = A + i_lim * lda;
                T* base_C = C + i_lim * ldc;
                for (int k = 0; k < B2<T>; k += B1<T>) {
                    for (int j = 0; j < B2<T>; j += B1<T>) {
                        kernel_M_B1_B1(remaining_M, base_A + k, lda, B + k * ldb + j, ldb, base_C + j, ldc);
                    }
                }
            }
        }

        /**
         * @brief Multiplies the last (MxB1) part of a column of A with the last (B1xN) part of a line of B
         * @note M < B1, N < B1
         */
        template<typename T>
        void kernel_M_B1_N(const int M, const int N, const T* A, const int lda, const T* B, const int ldb, T* C, const int ldc) {
            const int remaining_M = M % TILE_SIZE<T>;
            const int i_lim = M - remaining_M;

            const int remaining_N = N % TILE_SIZE<T>;
            const int j_lim = N - remaining_N;

            auto kernel_BT_BT_N = get_kernel<T>(TILE_SIZE<T>, remaining_N, TILE_SIZE<T>);
            auto kernel_M_BT_BT = get_kernel<T>(remaining_M, TILE_SIZE<T>, TILE_SIZE<T>);
            auto kernel_M_BT_N = get_kernel<T>(remaining_M, remaining_N, TILE_SIZE<T>);

            for (int i = 0; i < i_lim; i += TILE_SIZE<T>) {
                const T* base_A = A + i * lda;
                T* base_C = C + i * ldc;
                for (int k = 0; k < B1<T>; k += TILE_SIZE<T>) {
                    const T* a = base_A + k;
                    for (int j = 0; j < j_lim; j += TILE_SIZE<T>) {
                        tile_kernel<T>(a, lda, B + k * ldb + j, ldb, base_C + j, ldc);
                    }
                    if (remaining_N > 0) {
                        kernel_BT_BT_N(base_A + k, lda, B + k * ldb + j_lim, ldb, base_C + j_lim, ldc);
                    }
                }
            }

            if (remaining_M > 0) {
                const T* base_A = A + i_lim * lda;
                T* base_C = C + i_lim * ldc;
                for (int k = 0; k < B1<T>; k += TILE_SIZE<T>) {
                    for (int j = 0; j < j_lim; j += TILE_SIZE<T>) {
                        kernel_M_BT_BT(base_A + k, lda, B + k * ldb + j, ldb, base_C + j, ldc);
                    }
                    if (remaining_N > 0) {
                        kernel_M_BT_N(base_A + k, lda, B + k * ldb + j_lim, ldb, base_C + j_lim, ldc);
                    }
                }
            }
        }

        /**
         * @brief Multiplies the last (MxB2) part of a column of A with the last (B2xN) part of a line of B
         * @note M < B2, N < B2
         */
        template<typename T>
        void kernel_M_B2_N(const int M, const int N, const T* A, const int lda, const T* B, const int ldb, T* C, const int ldc) {
            const int remaining_M = M % B1<T>;
            const int i_lim = M - remaining_M;

            const int remaining_N = N % B1<T>;
            const int j_lim = N - remaining_N;

            for (int i = 0; i < i_lim; i += B1<T>) {
                const T* base_A = A + i * lda;
                T* base_C = C + i * ldc;
                for (int k = 0; k < B2<T>; k += B1<T>) {
                    for (int j = 0; j < j_lim; j += B1<T>) {
                        kernel_B1_B1_B1(base_A + k, lda, B + k * ldb + j, ldb, base_C + j, ldc);
                    }
                    if (remaining_N > 0) {
                        kernel_B1_B1_N(remaining_N, base_A + k, lda, B + k * ldb + j_lim, ldb, base_C + j_lim, ldc);
                    }
                }
            }

            if (remaining_M > 0) {
                const T* base_A = A + i_lim * lda;
                T* base_C = C + i_lim * ldc;
                for (int k = 0; k < B2<T>; k += B1<T>) {
                    for (int j = 0; j < j_lim; j += B1<T>) {
                        kernel_M_B1_B1(remaining_M, base_A + k, lda, B + k * ldb + j, ldb, base_C + j, ldc);
                    }
                    if (remaining_N > 0) {
                        kernel_M_B1_N(remaining_M, remaining_N, base_A + k, lda, B + k * ldb + j_lim, ldb, base_C + j_lim, ldc);
                    }
                }
            }
        }

        /**
         * @brief Multiplies the lower right part of A with the last (KxB1) part of a column of B
         * @note M < B1, K < B1
         */
        template<typename T>
        void kernel_M_K_B1(const int M, const int K, const T* A, const int lda, const T* B, const int ldb, T* C, const int ldc) {
            const int remaining_M = M % TILE_SIZE<T>;
            const int i_lim = M - remaining_M;

            const int remaining_K = K % TILE_SIZE<T>;
            const int k_lim = K - remaining_K;

            auto kernel_BT_K_BT = get_kernel<T>(TILE_SIZE<T>, TILE_SIZE<T>, remaining_K);
            auto kernel_M_BT_BT = get_kernel<T>(remaining_M, TILE_SIZE<T>, TILE_SIZE<T>);
            auto kernel_M_K_BT = get_kernel<T>(remaining_M, TILE_SIZE<T>, remaining_K);


            for (int i = 0; i < i_lim; i += TILE_SIZE<T>) {
                const T* base_A = A + i * lda;
                T* base_C = C + i * ldc;
                for (int k = 0; k < k_lim; k += TILE_SIZE<T>) {
                    const T* a = base_A + k;
                    for (int j = 0; j < B1<T>; j += TILE_SIZE<T>) {
                        tile_kernel<T>(a, lda, B + k * ldb + j, ldb, base_C + j, ldc);
                    }
                }
                if (remaining_K > 0) {
                    for (int j = 0; j < B1<T>; j += TILE_SIZE<T>) {
                        kernel_BT_K_BT(base_A + k_lim, lda, B + k_lim * ldb + j, ldb, base_C + j, ldc);
                    }
                }
            }

            if (remaining_M > 0) {
                const T* base_A = A + i_lim * lda;
                T* base_C = C + i_lim * ldc;
                for (int k = 0; k < k_lim; k += TILE_SIZE<T>) {
                    for (int j = 0; j < B1<T>; j += TILE_SIZE<T>) {
                        kernel_M_BT_BT(base_A + k, lda, B + k * ldb + j, ldb, base_C + j, ldc);
                    }
                }
                if (remaining_K > 0) {
                    for (int j = 0; j < B1<T>; j += TILE_SIZE<T>) {
                        kernel_M_K_BT(base_A + k_lim, lda, B + k_lim * ldb + j, ldb, base_C + j, ldc);
                    }
                }
            }
        }


        /**
         * @brief Multiplies the lower right part of A with the last (KxB2) part of a column of B
         * @note M < B2, K < B2
         */
        template<typename T>
        void kernel_M_K_B2(const int M, const int K, const T* A, const int lda, const T* B, const int ldb, T* C, const int ldc) {
            const int remaining_M = M % B1<T>;
            const int i_lim = M - remaining_M;

            const int remaining_K = K % B1<T>;
            const int k_lim = K - remaining_K;

            for (int i = 0; i < i_lim; i += B1<T>) {
                const T* base_A = A + i * lda;
                T* base_C = C + i * ldc;
                for (int k = 0; k < k_lim; k += B1<T>) {
                    for (int j = 0; j < B2<T>; j += B1<T>) {
                        kernel_B1_B1_B1(base_A + k, lda, B + k * ldb + j, ldb, base_C + j, ldc);
                    }
                }
                if (remaining_K > 0) {
                    for (int j = 0; j < B2<T>; j += B1<T>) {
                        kernel_B1_K_B1(remaining_K, base_A + k_lim, lda, B + k_lim * ldb + j, ldb, base_C + j, ldc);
                    }
                }
            }

            if (remaining_M > 0) {
                const T* base_A = A + i_lim * lda;
                T* base_C = C + i_lim * ldc;
                for (int k = 0; k < k_lim; k += B1<T>) {
                    for (int j = 0; j < B2<T>; j += B1<T>) {
                        kernel_M_B1_B1(remaining_M, base_A + k, lda, B + k * ldb + j, ldb, base_C + j, ldc);
                    }
                }
                if (remaining_K > 0) {
                    for (int j = 0; j < B2<T>; j += B1<T>) {
                        kernel_M_K_B1(remaining_M, remaining_K, base_A + k_lim, lda, B + k_lim * ldb + j, ldb, base_C + j, ldc);
                    }
                }
            }
        }

        /**
         * @brief Multiplies A and B with M, N, and K all being smaller B1
         */
        template<typename T>
        void kernel_M_K_N_subB1(const int M, const int N, const int K, const T* A, const int lda, const T* B, const int ldb, T* C, const int ldc) {
            const int remaining_M = M % TILE_SIZE<T>;
            const int i_lim = M - remaining_M;

            const int remaining_N = N % TILE_SIZE<T>;
            const int j_lim = N - remaining_N;

            const int remaining_K = K % TILE_SIZE<T>;
            const int k_lim = K - remaining_K;

            auto kernel_BT_BT_N = get_kernel<T>(TILE_SIZE<T>, remaining_N, TILE_SIZE<T>);
            auto kernel_BT_K_BT = get_kernel<T>(TILE_SIZE<T>, TILE_SIZE<T>, remaining_K);
            auto kernel_BT_K_N = get_kernel<T>(TILE_SIZE<T>, remaining_N, remaining_K);


            for (int i = 0; i < i_lim; i += TILE_SIZE<T>) {
                const T* base_A = A + i * lda;
                T* base_C = C + i * ldc;
                for (int k = 0; k < k_lim; k += TILE_SIZE<T>) {
                    const T* a = base_A + k;
                    for (int j = 0; j < j_lim; j += TILE_SIZE<T>) {
                        tile_kernel<T>(a, lda, B + k * ldb + j, ldb, base_C + j, ldc);
                    }
                    if (remaining_N > 0) {
                        kernel_BT_BT_N(base_A + k, lda, B + k * ldb + j_lim, ldb, base_C + j_lim, ldc);
                    }
                }
                if (remaining_K > 0) {
                    for (int j = 0; j < j_lim; j += TILE_SIZE<T>) {
                        kernel_BT_K_BT(base_A + k_lim, lda, B + k_lim * ldb + j, ldb, base_C + j, ldc);
                    }
                    if (remaining_N > 0) {
                        kernel_BT_K_N(base_A + k_lim, lda, B + k_lim * ldb + j_lim, ldb, base_C + j_lim, ldc);
                    }
                }
            }

            if (remaining_M > 0) {
                auto kernel_M_BT_BT = get_kernel<T>(remaining_M, TILE_SIZE<T>, TILE_SIZE<T>);
                auto kernel_M_BT_N = get_kernel<T>(remaining_M, remaining_N, TILE_SIZE<T>);
                auto kernel_M_K_BT = get_kernel<T>(remaining_M, TILE_SIZE<T>, remaining_K);
                auto kernel_M_K_N = get_kernel<T>(remaining_M, remaining_N, remaining_K);

                const T* base_A = A + i_lim * lda;
                T* base_C = C + i_lim * ldc;
                for (int k = 0; k < k_lim; k += TILE_SIZE<T>) {
                    for (int j = 0; j < j_lim; j += TILE_SIZE<T>) {
                        kernel_M_BT_BT(base_A + k, lda, B + k * ldb + j, ldb, base_C + j, ldc);
                    }
                    if (remaining_N > 0) {
                        kernel_M_BT_N(base_A + k, lda, B + k * ldb + j_lim, ldb, base_C + j_lim, ldc);
                    }
                }
                if (remaining_K > 0) {
                    for (int j = 0; j < j_lim; j += TILE_SIZE<T>) {
                        kernel_M_K_BT(base_A + k_lim, lda, B + k_lim * ldb + j, ldb, base_C + j, ldc);
                    }
                    if (remaining_N > 0) {
                        kernel_M_K_N(base_A + k_lim, lda, B + k_lim * ldb + j_lim, ldb, base_C + j_lim, ldc);
                    }
                }
            }
        }

        /**
         * @brief Multiplies A and B with M, N, and K all being smaller B2
         */
        template<typename T>
        void kernel_M_K_N_subB2(const int M, const int N, const int K, const T* A, const int lda, const T* B, const int ldb, T* C, const int ldc) {
            const int remaining_M = M % B1<T>;
            const int i_lim = M - remaining_M;

            const int remaining_N = N % B1<T>;
            const int j_lim = N - remaining_N;

            const int remaining_K = K % B1<T>;
            const int k_lim = K - remaining_K;

            for (int i = 0; i < i_lim; i += B1<T>) {
                const T* base_A = A + i * lda;
                T* base_C = C + i * ldc;
                for (int k = 0; k < k_lim; k += B1<T>) {
                    for (int j = 0; j < j_lim; j += B1<T>) {
                        kernel_B1_B1_B1(base_A + k, lda, B + k * ldb + j, ldb, base_C + j, ldc);
                    }
                    if (remaining_N > 0) {
                        kernel_B1_B1_N(remaining_N, base_A + k, lda, B + k * ldb + j_lim, ldb, base_C + j_lim, ldc);
                    }
                }
                if (remaining_K > 0) {
                    for (int j = 0; j < j_lim; j += B1<T>) {
                        kernel_B1_K_B1(remaining_K, base_A + k_lim, lda, B + k_lim * ldb + j, ldb, base_C + j, ldc);
                    }
                    if (remaining_N > 0) {
                        kernel_B1_K_N(remaining_N, remaining_K, base_A + k_lim, lda, B + k_lim * ldb + j_lim, ldb, base_C + j_lim, ldc);
                    }
                }
            }

            if (remaining_M > 0) {
                const T* base_A = A + i_lim * lda;
                T* base_C = C + i_lim * ldc;
                for (int k = 0; k < k_lim; k += B1<T>) {
                    for (int j = 0; j < j_lim; j += B1<T>) {
                        kernel_M_B1_B1(remaining_M, base_A + k, lda, B + k * ldb + j, ldb, base_C + j, ldc);
                    }
                    if (remaining_N > 0) {
                        kernel_M_B1_N(remaining_M, remaining_N, base_A + k, lda, B + k * ldb + j_lim, ldb, base_C + j_lim, ldc);
                    }
                }
                if (remaining_K) {
                    for (int j = 0; j < j_lim; j += B1<T>) {
                        kernel_M_K_B1(remaining_M, remaining_K, base_A + k_lim, lda, B + k_lim * ldb + j, ldb, base_C + j, ldc);
                    }
                    if (remaining_N > 0) {
                        kernel_M_K_N_subB1(remaining_M, remaining_N, remaining_K, base_A + k_lim, lda, B + k_lim * ldb + j_lim, ldb, base_C + j_lim, ldc);
                    }
                }
            }
        }

        /**
         * @brief Handles the multiplication of the last line of A (with M < B2) with B
         */
        template<typename T>
        void gemm_M_subB2(const int M, const int N, const int K, const T* A, const int lda, const T* B, const int ldb, T* C, const int ldc) {
            const int remaining_K = K % B2<T>;
            const int k_lim = K - remaining_K;

            const int remaining_N = N % B2<T>;
            const int j_lim = N - remaining_N;

            for (int k = 0; k < k_lim; k += B2<T>) {
                for (int j = 0; j < j_lim; j += B2<T>) {
                    kernel_M_B2_B2(M, A + k, lda, B + k * ldb + j, ldb, C + j, ldc);
                }
                if (remaining_N > 0) {
                    kernel_M_B2_N(M, remaining_N, A + k, lda, B + k * ldb + j_lim, ldb, C + j_lim, ldc);
                }
            }

            if (remaining_K > 0) {
                for (int j = 0; j < j_lim; j += B2<T>) {
                    kernel_M_K_B2(M, remaining_K, A + k_lim, lda, B + k_lim * ldb + j, ldb, C + j, ldc);
                }

                if (remaining_N > 0) {
                    kernel_M_K_N_subB2(M, remaining_N, remaining_K, A + k_lim, lda, B + k_lim * ldb + j_lim, ldb, C + j_lim, ldc);
                }
            }
        }

        /**
         * Matrix multiplication of small matrices (M,N,K <= TILE_SIZE<T>)
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

        /**
         * @brief Multiplication of medium matrices
         * @note the only difference with `gemm_large` is that the final alpha*AB + beta*C
         *       operation is computed at the end of the function for the whole matrix
         */
        template<typename T>
        void gemm_medium(
          const int M, const int N, const int K, const T alpha, const T* A, const int lda, const T* B, const int ldb, const T beta, T* C, const int ldc) {
            std::vector<T> ab(M * N);
            T* AB = ab.data();
            const int ldab = N;

            const int remaining_M = M % B2<T>;
            const int i_lim = M - remaining_M;

            const int remaining_N = N % B2<T>;
            const int j_lim = N - remaining_N;

            const int remaining_K = K % B2<T>;
            const int k_lim = K - remaining_K;

            for (int i = 0; i < i_lim; i += B2<T>) {
                const T* base_A = A + i * lda;
                T* base_AB = AB + i * ldab;
                for (int k = 0; k < k_lim; k += B2<T>) {
                    const T* A = base_A + k;
                    const T* base_B = B + k * ldb;
                    for (int j = 0; j < j_lim; j += B2<T>) {
                        detail::kernel_B2_B2_B2(A, lda, base_B + j, ldb, base_AB + j, ldab);
                    }
                    if (remaining_N != 0) {
                        detail::kernel_B2_B2_N(remaining_N, A, lda, B + k * ldb + j_lim, ldb, base_AB + j_lim, ldab);
                    }
                }
                if (remaining_K > 0) {
                    const T* A = base_A + k_lim;
                    const T* base_B = B + k_lim * ldb;
                    for (int j = 0; j < j_lim; j += B2<T>) {
                        detail::kernel_B2_K_B2(remaining_K, A, lda, base_B + j, ldb, base_AB + j, ldab);
                    }
                    if (remaining_N > 0) {
                        detail::kernel_B2_K_N(remaining_N, remaining_K, A, lda, base_B + j_lim, ldb, base_AB + j_lim, ldab);
                    }
                }
            }

            if (remaining_M > 0) {
                detail::gemm_M_subB2(remaining_M, N, K, A + i_lim * lda, lda, B, ldb, AB + i_lim * ldab, ldab);
            }

            for (int line = 0; line < M; line++) {
                auto c = std::span(C + line * ldc, N);
                auto ab = std::span(AB + line * ldab, N);
                eve::algo::transform_to(eve::views::zip(ab, c), c, [alpha, beta](auto x) { return eve::fma(alpha, eve::get<0>(x), beta * eve::get<1>(x)); });
            }
        }

        /**
         * @brief Multiplication of large matrices
         * @note The difference with `gemm_medium` is that the alpha*AB + beta*C operation
         *       is computed for each B2<T> line, it helps reducing memory usage for large
         *       matrices.
         */
        template<typename T>
        void gemm_large(
          const int M, const int N, const int K, const T alpha, const T* A, const int lda, const T* B, const int ldb, const T beta, T* C, const int ldc) {
            std::vector<T> ab(B2<T> * N);
            T* AB = ab.data();
            const int ldab = N;

            const int remaining_M = M % B2<T>;
            const int i_lim = M - remaining_M;

            const int remaining_N = N % B2<T>;
            const int j_lim = N - remaining_N;

            const int remaining_K = K % B2<T>;
            const int k_lim = K - remaining_K;

            for (int i = 0; i < i_lim; i += B2<T>) {
                eve::algo::fill(ab, T{});

                const T* base_A = A + i * lda;
                for (int k = 0; k < k_lim; k += B2<T>) {
                    const T* A = base_A + k;
                    const T* base_B = B + k * ldb;
                    for (int j = 0; j < j_lim; j += B2<T>) {
                        detail::kernel_B2_B2_B2(A, lda, base_B + j, ldb, AB + j, ldab);
                    }
                    if (remaining_N != 0) {
                        detail::kernel_B2_B2_N(remaining_N, A, lda, B + k * ldb + j_lim, ldb, AB + j_lim, ldab);
                    }
                }
                if (remaining_K > 0) {
                    const T* A = base_A + k_lim;
                    const T* base_B = B + k_lim * ldb;
                    for (int j = 0; j < j_lim; j += B2<T>) {
                        detail::kernel_B2_K_B2(remaining_K, A, lda, base_B + j, ldb, AB + j, ldab);
                    }
                    if (remaining_N > 0) {
                        detail::kernel_B2_K_N(remaining_N, remaining_K, A, lda, base_B + j_lim, ldb, AB + j_lim, ldab);
                    }
                }

                // compute the result in C
                for (int line = 0; line < B2<T>; line++) {
                    auto c = std::span(C + (i + line) * ldc, N);
                    auto ab = std::span(AB + line * ldab, N);
                    eve::algo::transform_to(
                      eve::views::zip(ab, c), c, [alpha, beta](auto x) { return eve::fma(alpha, eve::get<0>(x), beta * eve::get<1>(x)); });
                }
            }

            if (remaining_M > 0) {
                eve::algo::fill(ab, T{});
                detail::gemm_M_subB2(remaining_M, N, K, A + i_lim * lda, lda, B, ldb, AB, ldab);
                for (int line = 0; line < remaining_M; line++) {
                    auto c = std::span(C + (i_lim + line) * ldc, N);
                    auto ab = std::span(AB + line * ldab, N);
                    eve::algo::transform_to(
                      eve::views::zip(ab, c), c, [alpha, beta](auto x) { return eve::fma(alpha, eve::get<0>(x), beta * eve::get<1>(x)); });
                }
            }
        }
    } // namespace detail

    /**
     * @brief Performs the operation `C = alpha * AB  + beta * C`.
     *
     * @note This function only chooses the appropriate function to call depending on the matrices' dimensions:
     * - If the matrices are small enough, we call `gemm_small` which directly calls the appropriate
     *   microkernel. Doing so allows to avoid the overhead of the multiple function calls in the
     *   two other versions.
     * - If the matrices are too big, we call `gemm_large`, which uses less extra memory than `gemm_medium`
     *   (B2 * N * sizeof(T) bytes instead of M * N * sizeof(T) bytes).
     * - For the other cases, we call `gemm_medium`.
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
        if (M <= detail::TILE_SIZE<T> && N <= detail::TILE_SIZE<T> && K <= detail::TILE_SIZE<T>) {
            detail::gemm_small(M, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
        } else if (M * N * sizeof(T) <= 16000000) {
            detail::gemm_medium(M, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
        } else {
            detail::gemm_large(M, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
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
