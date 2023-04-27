#ifndef GEMM_KERNELS_8XX_HPP
#define GEMM_KERNELS_8XX_HPP

#include <eve/eve.hpp>

namespace gemm::detail
{
    ///////////////////////////////////////
    //         8x1 * 1xX kernels         //
    ///////////////////////////////////////

    template<typename T>
    void kernel_811(const T* a, const int stride_a, const T* b, const int /* stride_b */, T* c, const int stride_c) {
        using wide_t = eve::wide<T, eve::fixed<4>>;
        const wide_t wb{*b};

        wide_t wa{[=](auto i, auto) { return a[i * stride_a]; }};
        wide_t wc = wa * wb;
        c[0] += wc.get(0);
        c[stride_c] += wc.get(1);
        c[2 * stride_c] += wc.get(2);
        c[3 * stride_c] += wc.get(3);

        wa = wide_t{[=](auto i, auto) { return a[(i + 4) * stride_a]; }};
        wc = wa * wb;
        c[4 * stride_c] += wc.get(0);
        c[5 * stride_c] += wc.get(1);
        c[6 * stride_c] += wc.get(2);
        c[7 * stride_c] += wc.get(3);
    }

    template<typename T>
    void kernel_812(const T* a, const int stride_a, const T* b, const int /* stride_b */, T* c, const int stride_c) {
        using wide_t = eve::wide<T, eve::fixed<4>>;
        const wide_t wb{b[0], b[1], b[0], b[1]};
        const wide_t wa0{a[0], a[0], a[stride_a], a[stride_a]};
        const wide_t wa1{a[2 * stride_a], a[2 * stride_a], a[3 * stride_a], a[3 * stride_a]};
        const wide_t wa2{a[4 * stride_a], a[4 * stride_a], a[5 * stride_a], a[5 * stride_a]};
        const wide_t wa3{a[6 * stride_a], a[6 * stride_a], a[7 * stride_a], a[7 * stride_a]};

        const auto wc0 = eve::fma(wa0, wb, wide_t{c[0], c[1], c[stride_c], c[stride_c + 1]});
        const auto wc1 = eve::fma(wa1, wb, wide_t{c[2 * stride_c], c[2 * stride_c + 1], c[3 * stride_c], c[3 * stride_c + 1]});
        const auto wc2 = eve::fma(wa2, wb, wide_t{c[4 * stride_c], c[4 * stride_c + 1], c[5 * stride_c], c[5 * stride_c + 1]});
        const auto wc3 = eve::fma(wa3, wb, wide_t{c[6 * stride_c], c[6 * stride_c + 1], c[7 * stride_c], c[7 * stride_c + 1]});

        c[0] = wc0.get(0);
        c[1] = wc0.get(1);
        c[stride_c] = wc0.get(2);
        c[stride_c + 1] = wc0.get(3);
        c[2 * stride_c] = wc1.get(0);
        c[2 * stride_c + 1] = wc1.get(1);
        c[3 * stride_c] = wc1.get(2);
        c[3 * stride_c + 1] = wc1.get(3);

        c[4 * stride_c] = wc2.get(0);
        c[4 * stride_c + 1] = wc2.get(1);
        c[5 * stride_c] = wc2.get(2);
        c[5 * stride_c + 1] = wc2.get(3);
        c[6 * stride_c] = wc3.get(0);
        c[6 * stride_c + 1] = wc3.get(1);
        c[7 * stride_c] = wc3.get(2);
        c[7 * stride_c + 1] = wc3.get(3);
    }

    template<typename T>
    void kernel_814(const T* a, const int stride_a, const T* b, const int /* stride_b */, T* c, const int stride_c) {
        using wide_t = eve::wide<T, eve::fixed<4>>;
        const wide_t wb{b};

        eve::store(eve::fma(a[0], wb, wide_t{c}), c);
        eve::store(eve::fma(a[stride_a], wb, wide_t{c + stride_c}), c + stride_c);
        eve::store(eve::fma(a[2 * stride_a], wb, wide_t{c + 2 * stride_c}), c + 2 * stride_c);
        eve::store(eve::fma(a[3 * stride_a], wb, wide_t{c + 3 * stride_c}), c + 3 * stride_c);
        eve::store(eve::fma(a[4 * stride_a], wb, wide_t{c + 4 * stride_c}), c + 4 * stride_c);
        eve::store(eve::fma(a[5 * stride_a], wb, wide_t{c + 5 * stride_c}), c + 5 * stride_c);
        eve::store(eve::fma(a[6 * stride_a], wb, wide_t{c + 6 * stride_c}), c + 6 * stride_c);
        eve::store(eve::fma(a[7 * stride_a], wb, wide_t{c + 7 * stride_c}), c + 7 * stride_c);
    }

    template<typename T>
    void kernel_818(const T* a, const int stride_a, const T* b, const int /* stride_b */, T* c, const int stride_c) {
        using wide_t = eve::wide<T, eve::fixed<8>>;
        const wide_t wb{b};

        eve::store(eve::fma(a[0], wb, wide_t{c}), c);
        eve::store(eve::fma(a[stride_a], wb, wide_t{c + stride_c}), c + stride_c);
        eve::store(eve::fma(a[2 * stride_a], wb, wide_t{c + 2 * stride_c}), c + 2 * stride_c);
        eve::store(eve::fma(a[3 * stride_a], wb, wide_t{c + 3 * stride_c}), c + 3 * stride_c);
        eve::store(eve::fma(a[4 * stride_a], wb, wide_t{c + 4 * stride_c}), c + 4 * stride_c);
        eve::store(eve::fma(a[5 * stride_a], wb, wide_t{c + 5 * stride_c}), c + 5 * stride_c);
        eve::store(eve::fma(a[6 * stride_a], wb, wide_t{c + 6 * stride_c}), c + 6 * stride_c);
        eve::store(eve::fma(a[7 * stride_a], wb, wide_t{c + 7 * stride_c}), c + 7 * stride_c);
    }

    ///////////////////////////////////////
    //         8x2 * 2xX kernels         //
    ///////////////////////////////////////

    template<typename T>
    void kernel_821(const T* a, const int stride_a, const T* b, const int stride_b, T* c, const int stride_c) {
        using wide_t = eve::wide<T, eve::fixed<8>>;
        const wide_t wa0{[=](auto i, auto) { return a[i * stride_a]; }};
        const wide_t wa1{[=](auto i, auto) { return a[i * stride_a + 1]; }};
        const auto wc = eve::fma(wa0, b[0], wa1 * b[stride_b]);

        c[0] += wc.get(0);
        c[stride_c] += wc.get(1);
        c[2 * stride_c] += wc.get(2);
        c[3 * stride_c] += wc.get(3);
        c[4 * stride_c] += wc.get(4);
        c[5 * stride_c] += wc.get(5);
        c[6 * stride_c] += wc.get(6);
        c[7 * stride_c] += wc.get(7);
    }

    template<typename T>
    void kernel_822(const T* a, const int stride_a, const T* b, const int stride_b, T* c, const int stride_c) {
        // TODO
        kernel_422(a, stride_a, b, stride_b, c, stride_c);
        kernel_422(a + 4 * stride_a, stride_a, b, stride_b, c + 4 * stride_c, stride_c);
    }

    template<typename T>
    void kernel_824(const T* a, const int stride_a, const T* b, const int stride_b, T* c, const int stride_c) {
        using wide_t = eve::wide<T, eve::fixed<4>>;
        const wide_t wb0{b};
        const wide_t wb1{b + stride_b};

        const auto wc0 = eve::fma(a[0], wb0, a[1] * wb1);
        const auto wc1 = eve::fma(a[stride_a], wb0, a[stride_a + 1] * wb1);
        const auto wc2 = eve::fma(a[2 * stride_a], wb0, a[2 * stride_a + 1] * wb1);
        const auto wc3 = eve::fma(a[3 * stride_a], wb0, a[3 * stride_a + 1] * wb1);
        const auto wc4 = eve::fma(a[4 * stride_a], wb0, a[4 * stride_a + 1] * wb1);
        const auto wc5 = eve::fma(a[5 * stride_a], wb0, a[5 * stride_a + 1] * wb1);
        const auto wc6 = eve::fma(a[6 * stride_a], wb0, a[6 * stride_a + 1] * wb1);
        const auto wc7 = eve::fma(a[7 * stride_a], wb0, a[7 * stride_a + 1] * wb1);

        eve::store(wide_t{c} + wc0, c);
        eve::store(wide_t{c + stride_c} + wc1, c + stride_c);
        eve::store(wide_t{c + 2 * stride_c} + wc2, c + 2 * stride_c);
        eve::store(wide_t{c + 3 * stride_c} + wc3, c + 3 * stride_c);
        eve::store(wide_t{c + 4 * stride_c} + wc4, c + 4 * stride_c);
        eve::store(wide_t{c + 5 * stride_c} + wc5, c + 5 * stride_c);
        eve::store(wide_t{c + 6 * stride_c} + wc6, c + 6 * stride_c);
        eve::store(wide_t{c + 7 * stride_c} + wc7, c + 7 * stride_c);
    }

    template<typename T>
    void kernel_828(const T* a, const int stride_a, const T* b, const int stride_b, T* c, const int stride_c) {
        using wide_t = eve::wide<T, eve::fixed<8>>;
        const wide_t wb0{b};
        const wide_t wb1{b + stride_b};

        const auto wc0 = eve::fma(a[0], wb0, a[1] * wb1);
        const auto wc1 = eve::fma(a[stride_a], wb0, a[stride_a + 1] * wb1);
        const auto wc2 = eve::fma(a[2 * stride_a], wb0, a[2 * stride_a + 1] * wb1);
        const auto wc3 = eve::fma(a[3 * stride_a], wb0, a[3 * stride_a + 1] * wb1);
        const auto wc4 = eve::fma(a[4 * stride_a], wb0, a[4 * stride_a + 1] * wb1);
        const auto wc5 = eve::fma(a[5 * stride_a], wb0, a[5 * stride_a + 1] * wb1);
        const auto wc6 = eve::fma(a[6 * stride_a], wb0, a[6 * stride_a + 1] * wb1);
        const auto wc7 = eve::fma(a[7 * stride_a], wb0, a[7 * stride_a + 1] * wb1);

        eve::store(wide_t{c} + wc0, c);
        eve::store(wide_t{c + stride_c} + wc1, c + stride_c);
        eve::store(wide_t{c + 2 * stride_c} + wc2, c + 2 * stride_c);
        eve::store(wide_t{c + 3 * stride_c} + wc3, c + 3 * stride_c);
        eve::store(wide_t{c + 4 * stride_c} + wc4, c + 4 * stride_c);
        eve::store(wide_t{c + 5 * stride_c} + wc5, c + 5 * stride_c);
        eve::store(wide_t{c + 6 * stride_c} + wc6, c + 6 * stride_c);
        eve::store(wide_t{c + 7 * stride_c} + wc7, c + 7 * stride_c);
    }

    ///////////////////////////////////////
    //         8x4 * 4xX kernels         //
    ///////////////////////////////////////


    template<typename T>
    void kernel_841(const T* a, const int stride_a, const T* b, const int stride_b, T* c, const int stride_c) {
        using wide_t = eve::wide<T, eve::fixed<4>>;
        const wide_t wb{[=](auto i, auto) { return b[i * stride_b]; }};

        c[0] += eve::reduce(wide_t{a} * wb);
        c[stride_c] += eve::reduce(wide_t{a + stride_a} * wb);
        c[2 * stride_c] += eve::reduce(wide_t{a + 2 * stride_a} * wb);
        c[3 * stride_c] += eve::reduce(wide_t{a + 3 * stride_a} * wb);
        c[4 * stride_c] += eve::reduce(wide_t{a + 4 * stride_a} * wb);
        c[5 * stride_c] += eve::reduce(wide_t{a + 5 * stride_a} * wb);
        c[6 * stride_c] += eve::reduce(wide_t{a + 6 * stride_a} * wb);
        c[7 * stride_c] += eve::reduce(wide_t{a + 7 * stride_a} * wb);
    }

    template<typename T>
    void kernel_842(const T* a, const int stride_a, const T* b, const int stride_b, T* c, const int stride_c) {
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
        c[4 * stride_c] += eve::reduce(wide_t{a + 4 * stride_a} * wb0);
        c[4 * stride_c + 1] += eve::reduce(wide_t{a + 4 * stride_a} * wb1);
        c[5 * stride_c] += eve::reduce(wide_t{a + 5 * stride_a} * wb0);
        c[5 * stride_c + 1] += eve::reduce(wide_t{a + 5 * stride_a} * wb1);
        c[6 * stride_c] += eve::reduce(wide_t{a + 6 * stride_a} * wb0);
        c[6 * stride_c + 1] += eve::reduce(wide_t{a + 6 * stride_a} * wb1);
        c[7 * stride_c] += eve::reduce(wide_t{a + 7 * stride_a} * wb0);
        c[7 * stride_c + 1] += eve::reduce(wide_t{a + 7 * stride_a} * wb1);
    }

    template<typename T>
    void kernel_844(const T* a, const int stride_a, const T* b, const int stride_b, T* c, const int stride_c) {
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

        wc0 = eve::fma(a[4 * stride_a], wb0, a[4 * stride_a + 1] * wb1);
        wc1 = eve::fma(a[4 * stride_a + 2], wb2, a[4 * stride_a + 3] * wb3);
        eve::store(wide_t{c + 4 * stride_c} + wc0 + wc1, c + 4 * stride_c);

        wc0 = eve::fma(a[5 * stride_a], wb0, a[5 * stride_a + 1] * wb1);
        wc1 = eve::fma(a[5 * stride_a + 2], wb2, a[5 * stride_a + 3] * wb3);
        eve::store(wide_t{c + 5 * stride_c} + wc0 + wc1, c + 5 * stride_c);

        wc0 = eve::fma(a[6 * stride_a], wb0, a[6 * stride_a + 1] * wb1);
        wc1 = eve::fma(a[6 * stride_a + 2], wb2, a[6 * stride_a + 3] * wb3);
        eve::store(wide_t{c + 6 * stride_c} + wc0 + wc1, c + 6 * stride_c);

        wc0 = eve::fma(a[7 * stride_a], wb0, a[7 * stride_a + 1] * wb1);
        wc1 = eve::fma(a[7 * stride_a + 2], wb2, a[7 * stride_a + 3] * wb3);
        eve::store(wide_t{c + 7 * stride_c} + wc0 + wc1, c + 7 * stride_c);
    }

    template<typename T>
    void kernel_848(const T* a, const int stride_a, const T* b, const int stride_b, T* c, const int stride_c) {
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

        wc0 = eve::fma(a[4 * stride_a], wb0, a[4 * stride_a + 1] * wb1);
        wc1 = eve::fma(a[4 * stride_a + 2], wb2, a[4 * stride_a + 3] * wb3);
        eve::store(wide_t{c + 4 * stride_c} + wc0 + wc1, c + 4 * stride_c);

        wc0 = eve::fma(a[5 * stride_a], wb0, a[5 * stride_a + 1] * wb1);
        wc1 = eve::fma(a[5 * stride_a + 2], wb2, a[5 * stride_a + 3] * wb3);
        eve::store(wide_t{c + 5 * stride_c} + wc0 + wc1, c + 5 * stride_c);

        wc0 = eve::fma(a[6 * stride_a], wb0, a[6 * stride_a + 1] * wb1);
        wc1 = eve::fma(a[6 * stride_a + 2], wb2, a[6 * stride_a + 3] * wb3);
        eve::store(wide_t{c + 6 * stride_c} + wc0 + wc1, c + 6 * stride_c);

        wc0 = eve::fma(a[7 * stride_a], wb0, a[7 * stride_a + 1] * wb1);
        wc1 = eve::fma(a[7 * stride_a + 2], wb2, a[7 * stride_a + 3] * wb3);
        eve::store(wide_t{c + 7 * stride_c} + wc0 + wc1, c + 7 * stride_c);
    }

    ///////////////////////////////////////
    //         8x8 * 8xX kernels         //
    ///////////////////////////////////////

    template<typename T>
    void kernel_881(const T* a, const int stride_a, const T* b, const int stride_b, T* c, const int stride_c) {
        using wide_t = eve::wide<T, eve::fixed<8>>;
        const wide_t wb{[=](auto i, auto) { return b[i * stride_b]; }};

        c[0] += eve::reduce(wide_t{a} * wb);
        c[stride_c] += eve::reduce(wide_t{a + stride_a} * wb);
        c[2 * stride_c] += eve::reduce(wide_t{a + 2 * stride_a} * wb);
        c[3 * stride_c] += eve::reduce(wide_t{a + 3 * stride_a} * wb);
        c[4 * stride_c] += eve::reduce(wide_t{a + 4 * stride_a} * wb);
        c[5 * stride_c] += eve::reduce(wide_t{a + 5 * stride_a} * wb);
        c[6 * stride_c] += eve::reduce(wide_t{a + 6 * stride_a} * wb);
        c[7 * stride_c] += eve::reduce(wide_t{a + 7 * stride_a} * wb);
    }

    template<typename T>
    void kernel_882(const T* a, const int stride_a, const T* b, const int stride_b, T* c, const int stride_c) {
        using wide_t = eve::wide<T, eve::fixed<8>>;
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
        c[4 * stride_c] += eve::reduce(wide_t{a + 4 * stride_a} * wb0);
        c[4 * stride_c + 1] += eve::reduce(wide_t{a + 4 * stride_a} * wb1);
        c[5 * stride_c] += eve::reduce(wide_t{a + 5 * stride_a} * wb0);
        c[5 * stride_c + 1] += eve::reduce(wide_t{a + 5 * stride_a} * wb1);
        c[6 * stride_c] += eve::reduce(wide_t{a + 6 * stride_a} * wb0);
        c[6 * stride_c + 1] += eve::reduce(wide_t{a + 6 * stride_a} * wb1);
        c[7 * stride_c] += eve::reduce(wide_t{a + 7 * stride_a} * wb0);
        c[7 * stride_c + 1] += eve::reduce(wide_t{a + 7 * stride_a} * wb1);
    }

    template<typename T>
    void kernel_884(const T* a, const int stride_a, const T* b, const int stride_b, T* c, const int stride_c) {
        kernel_484(a, stride_a, b, stride_b, c, stride_c);
        kernel_484(a + 4 * stride_a, stride_a, b, stride_b, c + 4 * stride_c, stride_c);
    }

    template<typename T>
    void kernel_888(const T* a, const int stride_a, const T* b, const int stride_b, T* c, const int stride_c) {
        kernel_488(a, stride_a, b, stride_b, c, stride_c);
        kernel_488(a + 4 * stride_a, stride_a, b, stride_b, c + 4 * stride_c, stride_c);
    }
} // namespace gemm::detail

#endif
