#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <catch2/generators/catch_generators_range.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <gemm/gemm.hpp>

#include "util.hpp"

using Catch::Matchers::WithinRel;

using gemm::detail::BK;
using gemm::detail::BM;
using gemm::detail::BN;

TEMPLATE_TEST_CASE("block+1 case", "[square][large][special]", float, double) {
    constexpr int M = BM<TestType> + 1;
    constexpr int N = BN<TestType> + 1;
    constexpr int K = BK<TestType> + 1;

    const auto A = util::random_vector<TestType>(M * K);
    const auto B = util::random_vector<TestType>(K * N);
    auto C = util::random_vector<TestType>(M * N);
    auto C2 = C;

    const TestType alpha = util::random_float<TestType>();
    const TestType beta = util::random_float<TestType>();

    util::gemm(M, N, K, alpha, A.data(), K, B.data(), N, beta, C.data(), N);
    util::cblas_gemm(M, N, K, alpha, A.data(), K, B.data(), N, beta, C2.data(), N);

    for (std::size_t i = 0; i < C.size(); i++) {
        CAPTURE(i);
        REQUIRE_THAT(C[i], WithinRel(C2[i], util::precision<TestType>));
    }
}

TEMPLATE_TEST_CASE("dot product", "[large][special]", float, double) {
    constexpr int M = 1;
    constexpr int N = 1;
    constexpr int K = BK<TestType> + 1;

    const auto A = util::random_vector<TestType>(M * K);
    const auto B = util::random_vector<TestType>(K * N);
    auto C = util::random_vector<TestType>(M * N);
    auto C2 = C;

    const TestType alpha = util::random_float<TestType>();
    const TestType beta = util::random_float<TestType>();

    util::gemm(M, N, K, alpha, A.data(), K, B.data(), N, beta, C.data(), N);
    util::cblas_gemm(M, N, K, alpha, A.data(), K, B.data(), N, beta, C2.data(), N);

    for (std::size_t i = 0; i < C.size(); i++) {
        CAPTURE(i);
        REQUIRE_THAT(C[i], WithinRel(C2[i], util::precision<TestType>));
    }
}

TEMPLATE_TEST_CASE("outer product", "[large][special]", float, double) {
    constexpr int M = BM<TestType> + 1;
    constexpr int N = BN<TestType> + 1;
    constexpr int K = 1;

    const auto A = util::random_vector<TestType>(M * K);
    const auto B = util::random_vector<TestType>(K * N);
    auto C = util::random_vector<TestType>(M * N);
    auto C2 = C;

    const TestType alpha = util::random_float<TestType>();
    const TestType beta = util::random_float<TestType>();

    util::gemm(M, N, K, alpha, A.data(), K, B.data(), N, beta, C.data(), N);
    util::cblas_gemm(M, N, K, alpha, A.data(), K, B.data(), N, beta, C2.data(), N);

    for (std::size_t i = 0; i < C.size(); i++) {
        CAPTURE(i);
        REQUIRE_THAT(C[i], WithinRel(C2[i], util::precision<TestType>));
    }
}

TEMPLATE_TEST_CASE("column", "[large][special]", float, double) {
    constexpr int M = BM<TestType> + 1;
    constexpr int N = 1;
    constexpr int K = 1;

    const auto A = util::random_vector<TestType>(M * K);
    const auto B = util::random_vector<TestType>(K * N);
    auto C = util::random_vector<TestType>(M * N);
    auto C2 = C;

    const TestType alpha = util::random_float<TestType>();
    const TestType beta = util::random_float<TestType>();

    util::gemm(M, N, K, alpha, A.data(), K, B.data(), N, beta, C.data(), N);
    util::cblas_gemm(M, N, K, alpha, A.data(), K, B.data(), N, beta, C2.data(), N);

    for (std::size_t i = 0; i < C.size(); i++) {
        CAPTURE(i);
        REQUIRE_THAT(C[i], WithinRel(C2[i], util::precision<TestType>));
    }
}
