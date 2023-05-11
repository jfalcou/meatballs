#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators_range.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <cblas.h>
#include <fmt/core.h>
#include <nanobench.h>

#include "util.hpp"
#include <gemm/gemm.hpp>

using namespace std::chrono_literals;

TEST_CASE("M,N,K <= 8", "[small]") {
    using util::bench;
    bench.minEpochTime(20ms);

    const float alpha = util::random_float<float>();
    const float beta = util::random_float<float>();

    const auto M = GENERATE(1, 2, 4, 8);
    const auto K = GENERATE(1, 2, 4, 8);

    const auto A = util::random_vector<float>(M * K);

    const auto N = GENERATE(1, 2, 4, 8);

    CAPTURE(M, N, K);
    DYNAMIC_SECTION("" << M << "x" << K << " * " << K << "x" << N) {
        const auto B = util::random_vector<float>(K * N);
        auto C = util::random_vector<float>(M * N);
        auto oldC = C;

        const auto* ptr_A = A.data();
        const auto* ptr_B = B.data();
        auto* ptr_C = C.data();

        bench.title(fmt::format("{}x{} * {}x{}", M, K, K, N));
        bench.batch(M * N);

        bench.run("blas", [=] { cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, M, N, K, alpha, ptr_A, K, ptr_B, N, beta, ptr_C, N); });
        std::copy(oldC.begin(), oldC.end(), C.begin());

        bench.run("gemm", [=] { gemm::sgemm(util::no_trans, util::no_trans, M, N, K, alpha, ptr_A, K, ptr_B, N, beta, ptr_C, N); });
        std::copy(oldC.begin(), oldC.end(), C.begin());

        bench.run("naive", [=] { util::naive_gemm(M, N, K, alpha, ptr_A, K, ptr_B, N, beta, ptr_C, N); });
    }
}

TEST_CASE("1 <= dim <= 512", "[square][small]") {
    using util::bench;

    bench.warmup(0);
    bench.minEpochTime(30ms);

    const float alpha = util::random_float<float>();
    const float beta = util::random_float<float>();

    const auto dim = GENERATE(1, 2, 3, 4, 5, 6, 7, 8, 9, 12, 16, 21, 32, 64, 128, 256, 512);

    CAPTURE(dim);
    DYNAMIC_SECTION("" << dim << "x" << dim << " * " << dim << "x" << dim) {
        const auto A = util::random_vector<float>(dim * dim);
        const auto B = util::random_vector<float>(dim * dim);
        auto C = util::random_vector<float>(dim * dim);
        auto oldC = C;

        const auto* ptr_A = A.data();
        const auto* ptr_B = B.data();
        auto* ptr_C = C.data();

        bench.title(fmt::format("{0}x{0}", dim));
        bench.batch(dim * dim);

        bench.run("blas", [=] { cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, dim, dim, dim, alpha, ptr_A, dim, ptr_B, dim, beta, ptr_C, dim); });
        std::copy(oldC.begin(), oldC.end(), C.begin());

        bench.run("gemm", [=] { gemm::sgemm(util::no_trans, util::no_trans, dim, dim, dim, alpha, ptr_A, dim, ptr_B, dim, beta, ptr_C, dim); });
        std::copy(oldC.begin(), oldC.end(), C.begin());

        bench.run("naive", [=] { util::naive_gemm(dim, dim, dim, alpha, ptr_A, dim, ptr_B, dim, beta, ptr_C, dim); });

        if (util::collect_metrics) {
            const auto& results = bench.results();
            util::openblas_metrics.push_back(util::average_cycles_per_op(results[0]));
            util::gemm_metrics.push_back(util::average_cycles_per_op(results[1]));
            util::dimensions.push_back(dim);
        }
    }
}

TEST_CASE("Non square", "[large]") {
    using util::bench;

    bench.warmup(0);
    bench.minEpochTime(30ms);

    const float alpha = util::random_float<float>();
    const float beta = util::random_float<float>();


    const auto M = GENERATE(64, 128, 512);
    const auto K = GENERATE(128, 256);

    const auto A = util::random_vector<float>(M * K);

    const auto N = GENERATE(64, 512);

    CAPTURE(M, N, K);
    DYNAMIC_SECTION("" << M << "x" << K << " * " << K << "x" << N) {
        const auto B = util::random_vector<float>(K * N);
        auto C = util::random_vector<float>(M * N);
        auto oldC = C;

        const auto* ptr_A = A.data();
        const auto* ptr_B = B.data();
        auto* ptr_C = C.data();

        bench.title(fmt::format("{}x{} * {}x{}", M, K, K, N));
        bench.batch(M * N);

        bench.run("blas", [=] { cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, M, N, K, alpha, ptr_A, K, ptr_B, N, beta, ptr_C, N); });
        std::copy(oldC.begin(), oldC.end(), C.begin());

        bench.run("gemm", [=] { gemm::sgemm(util::no_trans, util::no_trans, M, N, K, alpha, ptr_A, K, ptr_B, N, beta, ptr_C, N); });
        std::copy(oldC.begin(), oldC.end(), C.begin());

        bench.run("naive", [=] { util::naive_gemm(M, N, K, alpha, ptr_A, K, ptr_B, N, beta, ptr_C, N); });
    }
}

TEST_CASE(">= 1024", "[square][large]") {
    using util::bench;

    bench.warmup(0);

    const float alpha = util::random_float<float>();
    const float beta = util::random_float<float>();

    // const auto dim = GENERATE(1024, 1327, 2000);
    const auto dim = GENERATE(1024, 2048);

    CAPTURE(dim);
    DYNAMIC_SECTION("" << dim << "x" << dim << " * " << dim << "x" << dim) {
        const auto A = util::random_vector<float>(dim * dim);
        const auto B = util::random_vector<float>(dim * dim);
        auto C = util::random_vector<float>(dim * dim);
        auto oldC = C;

        const auto* ptr_A = A.data();
        const auto* ptr_B = B.data();
        auto* ptr_C = C.data();

        bench.title(fmt::format("{0}x{0}", dim));
        bench.batch(dim * dim);

        bench.run("blas", [=] { cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, dim, dim, dim, alpha, ptr_A, dim, ptr_B, dim, beta, ptr_C, dim); });
        std::copy(oldC.begin(), oldC.end(), C.begin());

        bench.run("gemm", [=] { gemm::sgemm(util::no_trans, util::no_trans, dim, dim, dim, alpha, ptr_A, dim, ptr_B, dim, beta, ptr_C, dim); });

        if (util::collect_metrics) {
            const auto& results = bench.results();
            util::openblas_metrics.push_back(util::average_cycles_per_op(results[0]));
            util::gemm_metrics.push_back(util::average_cycles_per_op(results[1]));
            util::dimensions.push_back(dim);
        }
    }
}

TEST_CASE(">= 4096", "[square][very large]") {
    using util::bench;

    bench.warmup(0);

    const float alpha = util::random_float<float>();
    const float beta = util::random_float<float>();

    const auto dim = GENERATE(4096, 8000);

    CAPTURE(dim);
    DYNAMIC_SECTION("" << dim << "x" << dim << " * " << dim << "x" << dim) {
        const auto A = util::random_vector<float>(dim * dim);
        const auto B = util::random_vector<float>(dim * dim);
        auto C = util::random_vector<float>(dim * dim);
        auto oldC = C;

        const auto* ptr_A = A.data();
        const auto* ptr_B = B.data();
        auto* ptr_C = C.data();

        bench.title(fmt::format("{0}x{0}", dim));
        bench.batch(dim * dim);

        bench.run("blas", [=] { cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, dim, dim, dim, alpha, ptr_A, dim, ptr_B, dim, beta, ptr_C, dim); });
        std::copy(oldC.begin(), oldC.end(), C.begin());

        bench.run("gemm", [=] { gemm::sgemm(util::no_trans, util::no_trans, dim, dim, dim, alpha, ptr_A, dim, ptr_B, dim, beta, ptr_C, dim); });

        if (util::collect_metrics) {
            const auto& results = bench.results();
            util::openblas_metrics.push_back(util::average_cycles_per_op(results[0]));
            util::gemm_metrics.push_back(util::average_cycles_per_op(results[1]));
            util::dimensions.push_back(dim);
        }
    }
}
