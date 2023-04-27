#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <catch2/generators/catch_generators_range.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <gemm/gemm.hpp>

#include "util.hpp"

using Catch::Matchers::WithinRel;

TEMPLATE_TEST_CASE("various dimensions", "[rectangle]", float, double) {
    auto M = GENERATE(10, 72, 256, 329);
    auto N = GENERATE(8, 64, 257);
    auto K = GENERATE(1, 10, 100);

    CAPTURE(M, N, K);
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

TEMPLATE_TEST_CASE("various dimensions (large)", "[rectangle][very large]", float, double) {
    auto M = GENERATE(1024, 2513);
    auto N = GENERATE(1001, 1024);
    auto K = GENERATE(1024);

    CAPTURE(M, N, K);
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
