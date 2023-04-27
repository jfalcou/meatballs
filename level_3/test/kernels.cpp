#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators_range.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "util.hpp"
#include <gemm/detail/kernels.hpp>

using Catch::Matchers::WithinRel;

TEMPLATE_TEST_CASE("Microkernels", "[kernels][small]", float, double) {
    Catch::StringMaker<TestType>::precision = 15;

    constexpr TestType alpha = 1.0f;
    constexpr TestType beta = 1.0f;

    const auto M = GENERATE(range(1, 9));
    const auto K = GENERATE(range(1, 9));

    const auto A = util::random_vector<TestType>(M * K);

    const auto N = GENERATE(range(1, 9));

    CAPTURE(M, N, K);

    const auto B = util::random_vector<TestType>(K * N);
    auto C = util::random_vector<TestType>(M * N);
    auto C2 = C;

    gemm::detail::get_kernel<TestType>(M, N, K)(A.data(), K, B.data(), N, C.data(), N);
    util::cblas_gemm(M, N, K, alpha, A.data(), K, B.data(), N, beta, C2.data(), N);

    for (std::size_t i = 0; i < C.size(); i++) {
        CAPTURE(i);
        REQUIRE_THAT(C[i], WithinRel(C2[i], util::precision<TestType>));
    }
}
