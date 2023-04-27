#ifndef GEMM_KERNELS_4XX_HPP
#define GEMM_KERNELS_4XX_HPP

#include <eve/eve.hpp>

namespace gemm::detail
{
    ///////////////////////////////////////
    //         4x1 * 1xX kernels         //
    ///////////////////////////////////////

    template<typename T>
    void kernel_411(const T* a, const int stride_a, const T* b, const int /* stride_b */, T* c, const int stride_c) {
        using wide_t = eve::wide<T, eve::fixed<4>>;
        const wide_t wb{*b};
        const wide_t wa{[=](auto i, auto) { return a[i * stride_a]; }};
        const auto wc = wb * wa;
        c[0] += wc.get(0);
        c[stride_c] += wc.get(1);
        c[2 * stride_c] += wc.get(2);
        c[3 * stride_c] += wc.get(3);
    }

    template<typename T>
    void kernel_412(const T* a, const int stride_a, const T* b, const int /* stride_b */, T* c, const int stride_c) {
        using wide_t = eve::wide<T, eve::fixed<4>>;
        const wide_t wa{[=](auto i, auto) { return a[i * stride_a]; }};
        auto wc = wa * b[0];
        c[0] += wc.get(0);
        c[stride_c] += wc.get(1);
        c[2 * stride_c] += wc.get(2);
        c[3 * stride_c] += wc.get(3);

        wc = wa * b[1];
        c[1] += wc.get(0);
        c[stride_c + 1] += wc.get(1);
        c[2 * stride_c + 1] += wc.get(2);
        c[3 * stride_c + 1] += wc.get(3);
    }

    template<typename T>
    void kernel_414(const T* a, const int stride_a, const T* b, const int /* stride_b */, T* c, const int stride_c) {
        using wide_t = eve::wide<T, eve::fixed<4>>;
        const wide_t wb{b};
        eve::store(eve::fma(wide_t{a[0]}, wb, wide_t{c}), c);
        eve::store(eve::fma(wide_t{a[stride_a]}, wb, wide_t{c + stride_c}), c + stride_c);
        eve::store(eve::fma(wide_t{a[2 * stride_a]}, wb, wide_t{c + 2 * stride_c}), c + 2 * stride_c);
        eve::store(eve::fma(wide_t{a[3 * stride_a]}, wb, wide_t{c + 3 * stride_c}), c + 3 * stride_c);
    }

    template<typename T>
    void kernel_418(const T* a, const int stride_a, const T* b, const int /* stride_b */, T* c, const int stride_c) {
        using wide_t = eve::wide<T, eve::fixed<8>>;
        const wide_t wb{b};
        eve::store(eve::fma(wide_t{a[0]}, wb, wide_t{c}), c);
        eve::store(eve::fma(wide_t{a[stride_a]}, wb, wide_t{c + stride_c}), c + stride_c);
        eve::store(eve::fma(wide_t{a[2 * stride_a]}, wb, wide_t{c + 2 * stride_c}), c + 2 * stride_c);
        eve::store(eve::fma(wide_t{a[3 * stride_a]}, wb, wide_t{c + 3 * stride_c}), c + 3 * stride_c);
    }

    ///////////////////////////////////////
    //         4x2 * 2xX kernels         //
    ///////////////////////////////////////

    template<typename T>
    void kernel_421(const T* a, const int stride_a, const T* b, const int stride_b, T* c, const int stride_c) {
        using wide_t = eve::wide<T, eve::fixed<4>>;
        const wide_t wa0{[=](auto i, auto) { return a[i * stride_a]; }};
        const wide_t wa1{[=](auto i, auto) { return a[i * stride_a + 1]; }};
        const auto wc = eve::fma(wa0, b[0], wa1 * b[stride_b]);
        c[0] += wc.get(0);
        c[stride_c] += wc.get(1);
        c[2 * stride_c] += wc.get(2);
        c[3 * stride_c] += wc.get(3);
    }

    template<typename T>
    void kernel_422(const T* a, const int stride_a, const T* b, const int stride_b, T* c, const int stride_c) {
        c[0] += a[0] * b[0] + a[1] * b[stride_b];
        c[1] += a[0] * b[1] + a[1] * b[stride_b + 1];
        c[stride_c] += a[stride_a] * b[0] + a[stride_a + 1] * b[stride_b];
        c[stride_c + 1] += a[stride_a] * b[1] + a[stride_a + 1] * b[stride_b + 1];
        c[2 * stride_c] += a[2 * stride_a] * b[0] + a[2 * stride_a + 1] * b[stride_b];
        c[2 * stride_c + 1] += a[2 * stride_a] * b[1] + a[2 * stride_a + 1] * b[stride_b + 1];
        c[3 * stride_c] += a[3 * stride_a] * b[0] + a[3 * stride_a + 1] * b[stride_b];
        c[3 * stride_c + 1] += a[3 * stride_a] * b[1] + a[3 * stride_a + 1] * b[stride_b + 1];
    }

    template<typename T>
    void kernel_424(const T* a, const int stride_a, const T* b, const int stride_b, T* c, const int stride_c) {
        using wide_t = eve::wide<T, eve::fixed<4>>;
        const wide_t wb0{b};
        const wide_t wb1{b + stride_b};

        const auto wc0 = eve::fma(a[0], wb0, a[1] * wb1);
        const auto wc1 = eve::fma(a[stride_a], wb0, a[stride_a + 1] * wb1);
        const auto wc2 = eve::fma(a[2 * stride_a], wb0, a[2 * stride_a + 1] * wb1);
        const auto wc3 = eve::fma(a[3 * stride_a], wb0, a[3 * stride_a + 1] * wb1);

        eve::store(wide_t{c} + wc0, c);
        eve::store(wide_t{c + stride_c} + wc1, c + stride_c);
        eve::store(wide_t{c + 2 * stride_c} + wc2, c + 2 * stride_c);
        eve::store(wide_t{c + 3 * stride_c} + wc3, c + 3 * stride_c);
    }

    template<typename T>
    void kernel_428(const T* a, const int stride_a, const T* b, const int stride_b, T* c, const int stride_c) {
        using wide_t = eve::wide<T, eve::fixed<8>>;
        const wide_t wb0{b};
        const wide_t wb1{b + stride_b};

        const auto wc0 = eve::fma(a[0], wb0, a[1] * wb1);
        const auto wc1 = eve::fma(a[stride_a], wb0, a[stride_a + 1] * wb1);
        const auto wc2 = eve::fma(a[2 * stride_a], wb0, a[2 * stride_a + 1] * wb1);
        const auto wc3 = eve::fma(a[3 * stride_a], wb0, a[3 * stride_a + 1] * wb1);

        eve::store(wide_t{c} + wc0, c);
        eve::store(wide_t{c + stride_c} + wc1, c + stride_c);
        eve::store(wide_t{c + 2 * stride_c} + wc2, c + 2 * stride_c);
        eve::store(wide_t{c + 3 * stride_c} + wc3, c + 3 * stride_c);
    }

    ///////////////////////////////////////
    //         4x4 * 4xX kernels         //
    ///////////////////////////////////////

    template<typename T>
    void kernel_441(const T* a, const int stride_a, const T* b, const int stride_b, T* c, const int stride_c) {
        using wide_t = eve::wide<T, eve::fixed<4>>;
        const wide_t wb{[=](auto i, auto) { return b[i * stride_b]; }};

        c[0] += eve::reduce(wide_t{a} * wb);
        c[stride_c] += eve::reduce(wide_t{a + stride_a} * wb);
        c[2 * stride_c] += eve::reduce(wide_t{a + 2 * stride_a} * wb);
        c[3 * stride_c] += eve::reduce(wide_t{a + 3 * stride_a} * wb);
    }

    template<typename T>
    void kernel_442(const T* a, const int stride_a, const T* b, const int stride_b, T* c, const int stride_c) {
        using wide_t = eve::wide<T, eve::fixed<4>>;
        const wide_t wb0{[=](auto i, auto) { return b[i * stride_b]; }};
        const wide_t wb1{[=](auto i, auto) { return b[i * stride_b + 1]; }};

        c[0] += eve::reduce(wide_t{a} * wb0);
        c[1] += eve::reduce(wide_t{a} * wb1);
        c[stride_c] += eve::reduce(wide_t{a + stride_a} * wb0);
        c[stride_c + 1] += eve::reduce(wide_t{a + stride_a} * wb1);
        c[2 * stride_c] += eve::reduce(wide_t{a + 2 * stride_a} * wb0);
        c[2 * stride_c + 1] += eve::reduce(wide_t{a + 2 * stride_a} * wb1);
        c[3 * stride_c] += eve::reduce(wide_t{a + 3 * stride_a} * wb0);
        c[3 * stride_c + 1] += eve::reduce(wide_t{a + 3 * stride_a} * wb1);
    }

    template<typename T>
    void kernel_444(const T* a, const int stride_a, const T* b, const int stride_b, T* c, const int stride_c) {
        using wide_t = eve::wide<T, eve::fixed<4>>;
        const wide_t wb0{b};
        const wide_t wb1{b + stride_b};
        const wide_t wb2{b + 2 * stride_b};
        const wide_t wb3{b + 3 * stride_b};

        auto wc0 = eve::fma(a[0], wb0, a[1] * wb1);
        auto wc1 = eve::fma(a[2], wb2, a[3] * wb3);
        eve::store(wide_t{c} + wc0 + wc1, c);

        wc0 = eve::fma(a[stride_a], wb0, a[stride_a + 1] * wb1);
        wc1 = eve::fma(a[stride_a + 2], wb2, a[stride_a + 3] * wb3);
        eve::store(wide_t{c + stride_c} + wc0 + wc1, c + stride_c);

        wc0 = eve::fma(a[2 * stride_a], wb0, a[2 * stride_a + 1] * wb1);
        wc1 = eve::fma(a[2 * stride_a + 2], wb2, a[2 * stride_a + 3] * wb3);
        eve::store(wide_t{c + 2 * stride_c} + wc0 + wc1, c + 2 * stride_c);

        wc0 = eve::fma(a[3 * stride_a], wb0, a[3 * stride_a + 1] * wb1);
        wc1 = eve::fma(a[3 * stride_a + 2], wb2, a[3 * stride_a + 3] * wb3);
        eve::store(wide_t{c + 3 * stride_c} + wc0 + wc1, c + 3 * stride_c);
    }

    template<typename T>
    void kernel_448(const T* a, const int stride_a, const T* b, const int stride_b, T* c, const int stride_c) {
        using wide_t = eve::wide<T, eve::fixed<8>>;
        const wide_t wb0{b};
        const wide_t wb1{b + stride_b};
        const wide_t wb2{b + 2 * stride_b};
        const wide_t wb3{b + 3 * stride_b};

        auto wc0 = eve::fma(a[0], wb0, a[1] * wb1);
        auto wc1 = eve::fma(a[2], wb2, a[3] * wb3);
        eve::store(wide_t{c} + wc0 + wc1, c);

        wc0 = eve::fma(a[stride_a], wb0, a[stride_a + 1] * wb1);
        wc1 = eve::fma(a[stride_a + 2], wb2, a[stride_a + 3] * wb3);
        eve::store(wide_t{c + stride_c} + wc0 + wc1, c + stride_c);

        wc0 = eve::fma(a[2 * stride_a], wb0, a[2 * stride_a + 1] * wb1);
        wc1 = eve::fma(a[2 * stride_a + 2], wb2, a[2 * stride_a + 3] * wb3);
        eve::store(wide_t{c + 2 * stride_c} + wc0 + wc1, c + 2 * stride_c);

        wc0 = eve::fma(a[3 * stride_a], wb0, a[3 * stride_a + 1] * wb1);
        wc1 = eve::fma(a[3 * stride_a + 2], wb2, a[3 * stride_a + 3] * wb3);
        eve::store(wide_t{c + 3 * stride_c} + wc0 + wc1, c + 3 * stride_c);
    }

    ///////////////////////////////////////
    //         4x8 * 8xX kernels         //
    ///////////////////////////////////////

    template<typename T>
    void kernel_481(const T* a, const int stride_a, const T* b, const int stride_b, T* c, const int stride_c) {
        using wide_t = eve::wide<T, eve::fixed<8>>;
        const wide_t wb{[=](auto i, auto) { return b[i * stride_b]; }};

        c[0] += eve::reduce(wide_t{a} * wb);
        c[stride_c] += eve::reduce(wide_t{a + stride_a} * wb);
        c[2 * stride_c] += eve::reduce(wide_t{a + 2 * stride_a} * wb);
        c[3 * stride_c] += eve::reduce(wide_t{a + 3 * stride_a} * wb);
    }

    template<typename T>
    void kernel_482(const T* a, const int stride_a, const T* b, const int stride_b, T* c, const int stride_c) {
        kernel_282(a, stride_a, b, stride_b, c, stride_c);
        kernel_282(a + 2 * stride_a, stride_a, b, stride_b, c + 2 * stride_c, stride_c);
    }

    template<typename T>
    void kernel_484(const T* a, const int stride_a, const T* b, const int stride_b, T* c, const int stride_c) {
        using wide_t = eve::wide<T, eve::fixed<4>>;

        const wide_t wb0{b};
        const wide_t wb1{b + stride_b};
        const wide_t wb2{b + 2 * stride_b};
        const wide_t wb3{b + 3 * stride_b};
        const wide_t wb4{b + 4 * stride_b};
        const wide_t wb5{b + 5 * stride_b};
        const wide_t wb6{b + 6 * stride_b};
        const wide_t wb7{b + 7 * stride_b};

        auto wc0 = eve::fma(a[0], wb0, a[1] * wb1);
        auto wc1 = eve::fma(a[2], wb2, a[3] * wb3);
        auto wc2 = eve::fma(a[4], wb4, a[5] * wb5);
        auto wc3 = eve::fma(a[6], wb6, a[7] * wb7);
        eve::store(wide_t{c} + wc0 + wc1 + wc2 + wc3, c);

        wc0 = eve::fma(a[stride_a], wb0, a[stride_a + 1] * wb1);
        wc1 = eve::fma(a[stride_a + 2], wb2, a[stride_a + 3] * wb3);
        wc2 = eve::fma(a[stride_a + 4], wb4, a[stride_a + 5] * wb5);
        wc3 = eve::fma(a[stride_a + 6], wb6, a[stride_a + 7] * wb7);
        eve::store(wide_t{c + stride_c} + wc0 + wc1 + wc2 + wc3, c + stride_c);

        wc0 = eve::fma(a[2 * stride_a], wb0, a[2 * stride_a + 1] * wb1);
        wc1 = eve::fma(a[2 * stride_a + 2], wb2, a[2 * stride_a + 3] * wb3);
        wc2 = eve::fma(a[2 * stride_a + 4], wb4, a[2 * stride_a + 5] * wb5);
        wc3 = eve::fma(a[2 * stride_a + 6], wb6, a[2 * stride_a + 7] * wb7);
        eve::store(wide_t{c + 2 * stride_c} + wc0 + wc1 + wc2 + wc3, c + 2 * stride_c);

        wc0 = eve::fma(a[3 * stride_a], wb0, a[3 * stride_a + 1] * wb1);
        wc1 = eve::fma(a[3 * stride_a + 2], wb2, a[3 * stride_a + 3] * wb3);
        wc2 = eve::fma(a[3 * stride_a + 4], wb4, a[3 * stride_a + 5] * wb5);
        wc3 = eve::fma(a[3 * stride_a + 6], wb6, a[3 * stride_a + 7] * wb7);
        eve::store(wide_t{c + 3 * stride_c} + wc0 + wc1 + wc2 + wc3, c + 3 * stride_c);
    }

    template<typename T>
    void kernel_488(const T* a, const int stride_a, const T* b, const int stride_b, T* c, const int stride_c) {
        using wide_t = eve::wide<T, eve::fixed<8>>;

        const wide_t wb0{b};
        const wide_t wb1{b + stride_b};
        const wide_t wb2{b + 2 * stride_b};
        const wide_t wb3{b + 3 * stride_b};
        const wide_t wb4{b + 4 * stride_b};
        const wide_t wb5{b + 5 * stride_b};
        const wide_t wb6{b + 6 * stride_b};
        const wide_t wb7{b + 7 * stride_b};

        auto wc0 = eve::fma(a[0], wb0, a[1] * wb1);
        auto wc1 = eve::fma(a[2], wb2, a[3] * wb3);
        auto wc2 = eve::fma(a[4], wb4, a[5] * wb5);
        auto wc3 = eve::fma(a[6], wb6, a[7] * wb7);
        eve::store(wide_t{c} + wc0 + wc1 + wc2 + wc3, c);

        wc0 = eve::fma(a[stride_a], wb0, a[stride_a + 1] * wb1);
        wc1 = eve::fma(a[stride_a + 2], wb2, a[stride_a + 3] * wb3);
        wc2 = eve::fma(a[stride_a + 4], wb4, a[stride_a + 5] * wb5);
        wc3 = eve::fma(a[stride_a + 6], wb6, a[stride_a + 7] * wb7);
        eve::store(wide_t{c + stride_c} + wc0 + wc1 + wc2 + wc3, c + stride_c);

        wc0 = eve::fma(a[2 * stride_a], wb0, a[2 * stride_a + 1] * wb1);
        wc1 = eve::fma(a[2 * stride_a + 2], wb2, a[2 * stride_a + 3] * wb3);
        wc2 = eve::fma(a[2 * stride_a + 4], wb4, a[2 * stride_a + 5] * wb5);
        wc3 = eve::fma(a[2 * stride_a + 6], wb6, a[2 * stride_a + 7] * wb7);
        eve::store(wide_t{c + 2 * stride_c} + wc0 + wc1 + wc2 + wc3, c + 2 * stride_c);

        wc0 = eve::fma(a[3 * stride_a], wb0, a[3 * stride_a + 1] * wb1);
        wc1 = eve::fma(a[3 * stride_a + 2], wb2, a[3 * stride_a + 3] * wb3);
        wc2 = eve::fma(a[3 * stride_a + 4], wb4, a[3 * stride_a + 5] * wb5);
        wc3 = eve::fma(a[3 * stride_a + 6], wb6, a[3 * stride_a + 7] * wb7);
        eve::store(wide_t{c + 3 * stride_c} + wc0 + wc1 + wc2 + wc3, c + 3 * stride_c);
    }
} // namespace gemm::detail

#endif
