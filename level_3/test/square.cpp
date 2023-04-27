#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <catch2/generators/catch_generators_range.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <gemm/gemm.hpp>

#include "util.hpp"

using Catch::Matchers::WithinRel;

TEMPLATE_TEST_CASE("dim < TILE_SIZE", "[square][small][alpha=1]", float, double) {
    const auto TILE_SIZE = gemm::detail::TILE_SIZE<TestType>;
    auto dim = GENERATE_COPY(range(1, TILE_SIZE));

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

TEMPLATE_TEST_CASE("dim = TILE_SIZE", "[square][small][alpha=1]", float, double) {
    const TestType dim = gemm::detail::TILE_SIZE<TestType>;

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

TEMPLATE_TEST_CASE("dim = B1", "[square][small][alpha=1]", float, double) {
    const TestType dim = gemm::detail::B1<TestType>;

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

TEMPLATE_TEST_CASE("dim = B2", "[square][small][alpha=1]", float, double) {
    const TestType dim = gemm::detail::B2<TestType>;

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

TEMPLATE_TEST_CASE("dim > B2", "[square][large][alpha=1]", float, double) {
    using gemm::detail::B2;
    auto dim = GENERATE(2 * B2<TestType>, 4 * B2<TestType>, 8 * B2<TestType>);

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
