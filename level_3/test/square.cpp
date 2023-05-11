#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <catch2/generators/catch_generators_range.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <gemm/gemm.hpp>

#include "util.hpp"

using Catch::Matchers::WithinRel;

TEMPLATE_TEST_CASE("dim < 8", "[square][small][alpha=1]", float, double) {
    auto dim = GENERATE(range(1, 8));

    CAPTURE(dim);
    const auto A = util::random_vector<TestType>(dim * dim);
    const auto B = util::random_vector<TestType>(dim * dim);
    auto C = util::random_vector<TestType>(dim * dim);
    auto C2 = C;

    constexpr TestType alpha = 1.0f;
    constexpr TestType beta = 1.0f;

    util::gemm(dim, dim, dim, alpha, A.data(), dim, B.data(), dim, beta, C.data(), dim);
    util::cblas_gemm(dim, dim, dim, alpha, A.data(), dim, B.data(), dim, beta, C2.data(), dim);

    for (std::size_t i = 0; i < C.size(); i++) {
        CAPTURE(i);
        REQUIRE_THAT(C[i], WithinRel(C2[i], util::precision<TestType>));
    }
}

TEMPLATE_TEST_CASE("dim = 8", "[square][small][alpha=1]", float, double) {
    const int dim = 8;

    const auto A = util::random_vector<TestType>(dim * dim);
    const auto B = util::random_vector<TestType>(dim * dim);
    auto C = util::random_vector<TestType>(dim * dim);
    auto C2 = C;

    constexpr TestType alpha = 1.0f;
    constexpr TestType beta = 1.0f;

    util::gemm(dim, dim, dim, alpha, A.data(), dim, B.data(), dim, beta, C.data(), dim);
    util::cblas_gemm(dim, dim, dim, alpha, A.data(), dim, B.data(), dim, beta, C2.data(), dim);

    for (std::size_t i = 0; i < C.size(); i++) {
        CAPTURE(i);
        REQUIRE_THAT(C[i], WithinRel(C2[i], util::precision<TestType>));
    }
}

TEMPLATE_TEST_CASE("single block", "[square][small][alpha=1]", float, double) {
    constexpr int M = gemm::detail::BM<TestType>;
    constexpr int N = gemm::detail::BN<TestType>;
    constexpr int K = gemm::detail::BK<TestType>;

    const auto A = util::random_vector<TestType>(M * K);
    const auto B = util::random_vector<TestType>(K * N);
    auto C = util::random_vector<TestType>(M * N);
    auto C2 = C;

    constexpr TestType alpha = 1.0f;
    constexpr TestType beta = 1.0f;

    util::gemm(M, N, K, alpha, A.data(), K, B.data(), N, beta, C.data(), N);
    util::cblas_gemm(M, N, K, alpha, A.data(), K, B.data(), N, beta, C2.data(), N);

    for (std::size_t i = 0; i < C.size(); i++) {
        CAPTURE(i);
        REQUIRE_THAT(C[i], WithinRel(C2[i], util::precision<TestType>));
    }
}

TEMPLATE_TEST_CASE("dim > B2", "[square][large][alpha=1]", float, double) {
    constexpr auto BM = gemm::detail::BM<TestType>;
    constexpr auto BN = gemm::detail::BN<TestType>;
    constexpr auto BK = gemm::detail::BK<TestType>;

    const int M = GENERATE(2 * BM, 4 * BM);
    const int N = GENERATE(2 * BN, 4 * BN);
    const int K = GENERATE(2 * BK, 4 * BK);

    const auto A = util::random_vector<TestType>(M * K);
    const auto B = util::random_vector<TestType>(K * N);
    auto C = util::random_vector<TestType>(M * N);
    auto C2 = C;

    constexpr TestType alpha = 1.0f;
    constexpr TestType beta = 1.0f;

    util::gemm(M, N, K, alpha, A.data(), K, B.data(), N, beta, C.data(), N);
    util::cblas_gemm(M, N, K, alpha, A.data(), K, B.data(), N, beta, C2.data(), N);

    for (std::size_t i = 0; i < C.size(); i++) {
        CAPTURE(i);
        REQUIRE_THAT(C[i], WithinRel(C2[i], util::precision<TestType>));
    }
}
