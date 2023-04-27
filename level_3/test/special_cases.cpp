#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <catch2/generators/catch_generators_range.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <gemm/gemm.hpp>

#include "util.hpp"

using Catch::Matchers::WithinRel;

using gemm::detail::B1;
using gemm::detail::B2;
using gemm::detail::TILE_SIZE;

TEMPLATE_TEST_CASE("worst case", "[square][large][special]", float, double) {
    constexpr auto dim = B2<TestType> + B1<TestType> + TILE_SIZE<TestType> + 1;

    const auto A = util::random_vector<TestType>(dim * dim);
    const auto B = util::random_vector<TestType>(dim * dim);
    auto C = util::random_vector<TestType>(dim * dim);
    auto C2 = C;

    const TestType alpha = util::random_float<TestType>();
    const TestType beta = util::random_float<TestType>();

    util::gemm(dim, dim, dim, alpha, A.data(), dim, B.data(), dim, beta, C.data(), dim);
    util::cblas_gemm(dim, dim, dim, alpha, A.data(), dim, B.data(), dim, beta, C2.data(), dim);

    for (std::size_t i = 0; i < C.size(); i++) {
        CAPTURE(i);
        REQUIRE_THAT(C[i], WithinRel(C2[i], util::precision<TestType>));
    }
}

TEMPLATE_TEST_CASE("dot product", "[large][special]", float, double) {
    constexpr int M = 1;
    constexpr int N = 1;
    constexpr int K = B2<TestType> + B1<TestType> + TILE_SIZE<TestType> + 1;

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
    constexpr int M = B2<TestType> + B1<TestType> + TILE_SIZE<TestType> + 1;
    ;
    constexpr int N = B2<TestType> + B1<TestType> + TILE_SIZE<TestType> + 1;
    ;
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
    constexpr int M = B2<TestType> + B1<TestType> + TILE_SIZE<TestType> + 1;
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
