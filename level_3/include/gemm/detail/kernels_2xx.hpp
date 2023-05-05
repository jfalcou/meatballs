#ifndef GEMM_KERNELS_2XX_HPP
#define GEMM_KERNELS_2XX_HPP

#include <eve/eve.hpp>

namespace gemm::detail
{
    ///////////////////////////////////////
    //         2x1 * 1xX kernels         //
    ///////////////////////////////////////

    template<typename T>
    void kernel_211(const T* a, const int stride_a, const T* b, const int /* stride_b */, T* c, const int stride_c) {
        c[0] += a[0] * *b;
        c[stride_c] += a[stride_a] * *b;
    }

    template<typename T>
    void kernel_212(const T* a, const int stride_a, const T* b, const int /* stride_b */, T* c, const int stride_c) {
        // TODO ?
        c[0] += a[0] * b[0];
        c[1] += a[0] * b[1];
        c[stride_c] += a[stride_a] * b[0];
        c[stride_c + 1] += a[stride_a] * b[1];
    }

    template<typename T>
    void kernel_214(const T* a, const int stride_a, const T* b, const int /* stride_b */, T* c, const int stride_c) {
        using wide_t = eve::wide<T, eve::fixed<4>>;
        const wide_t wb{b};
        const wide_t wc0 = eve::fma(a[0], wb, wide_t{c});
        const wide_t wc1 = eve::fma(a[stride_a], wide_t{b}, wide_t{c + stride_c});
        eve::store(wc0, c);
        eve::store(wc1, c + stride_c);
    }

    template<typename T>
    void kernel_218(const T* a, const int stride_a, const T* b, const int /* stride_b */, T* c, const int stride_c) {
        using wide_t = eve::wide<T, eve::fixed<8>>;
        const wide_t wb{b};
        const wide_t wc0 = eve::fma(a[0], wb, wide_t{c});
        const wide_t wc1 = eve::fma(a[stride_a], wide_t{b}, wide_t{c + stride_c});
        eve::store(wc0, c);
        eve::store(wc1, c + stride_c);
    }

    ///////////////////////////////////////
    //         2x2 * 2xX kernels         //
    ///////////////////////////////////////

    template<typename T>
    void kernel_221(const T* a, const int stride_a, const T* b, const int stride_b, T* c, const int stride_c) {
        c[0] += a[0] * b[0] + a[1] * b[stride_b];
        c[stride_c] += a[stride_a] * b[0] + a[stride_a + 1] * b[stride_b];
    }

    template<typename T>
    void kernel_222(const T* a, const int stride_a, const T* b, const int stride_b, T* c, const int stride_c) {
        using wide_t = eve::wide<T, eve::fixed<4>>;
        const wide_t wa{a[0], a[1], a[stride_a], a[stride_a + 1]};
        const wide_t wb{b[0], b[1], b[stride_b], b[stride_b + 1]};

        const auto a0 = eve::shuffle(wa, eve::pattern<0, 0, 2, 2>);
        const auto b0 = eve::shuffle(wb, eve::pattern<0, 1, 0, 1>);
        const auto a1 = eve::shuffle(wa, eve::pattern<1, 1, 3, 3>);
        const auto b1 = eve::shuffle(wb, eve::pattern<2, 3, 2, 3>);
        const auto res = eve::fma(a0, b0, a1 * b1);

        c[0] += res.get(0);
        c[1] += res.get(1);
        c[stride_c] += res.get(2);
        c[stride_c + 1] += res.get(3);
    }

    template<typename T>
    void kernel_224(const T* a, const int stride_a, const T* b, const int stride_b, T* c, const int stride_c) {
        using wide_t = eve::wide<T, eve::fixed<4>>;
        const wide_t wb0{b};
        const wide_t wb1{b + stride_b};

        const auto wab0 = eve::fma(a[0], wb0, a[1] * wb1);
        const auto wab1 = eve::fma(a[stride_a], wb0, a[stride_a + 1] * wb1);

        eve::store(wab0 + wide_t{c}, c);
        eve::store(wab1 + wide_t{c + stride_c}, c + stride_c);
    }

    template<typename T>
    void kernel_228(const T* a, const int stride_a, const T* b, const int stride_b, T* c, const int stride_c) {
        using wide_t = eve::wide<T, eve::fixed<8>>;
        const wide_t wb0{b};
        const wide_t wb1{b + stride_b};

        const auto wab0 = eve::fma(a[0], wb0, a[1] * wb1);
        const auto wab1 = eve::fma(a[stride_a], wb0, a[stride_a + 1] * wb1);

        eve::store(wab0 + wide_t{c}, c);
        eve::store(wab1 + wide_t{c + stride_c}, c + stride_c);
    }

    ///////////////////////////////////////
    //         2x4 * 4xX kernels         //
    ///////////////////////////////////////

    template<typename T>
    void kernel_241(const T* a, const int stride_a, const T* b, const int stride_b, T* c, const int stride_c) {
        using wide_t = eve::wide<T, eve::fixed<4>>;
        const wide_t wa0{a};
        const wide_t wa1{a + stride_a};
        const wide_t wb{b[0], b[stride_b], b[2 * stride_b], b[3 * stride_b]};

        c[0] += eve::reduce(wa0 * wb);
        c[stride_c] += eve::reduce(wa1 * wb);
    }

    template<typename T>
    void kernel_242(const T* a, const int stride_a, const T* b, const int stride_b, T* c, const int stride_c) {
        using wide_t = eve::wide<T, eve::fixed<4>>;
        const wide_t wa0{a};
        const wide_t wa1{a + stride_a};
        const wide_t wb0{b[0], b[stride_b], b[2 * stride_b], b[3 * stride_b]};
        const wide_t wb1{b[1], b[stride_b + 1], b[2 * stride_b + 1], b[3 * stride_b + 1]};

        c[0] += eve::reduce(wa0 * wb0);
        c[1] += eve::reduce(wa0 * wb1);
        c[stride_c] += eve::reduce(wa1 * wb0);
        c[stride_c + 1] += eve::reduce(wa1 * wb1);
    }

    template<typename T>
    void kernel_244(const T* a, const int stride_a, const T* b, const int stride_b, T* c, const int stride_c) {
        using wide_t = eve::wide<T, eve::fixed<4>>;
        const wide_t wb0{b};
        const wide_t wb1{b + stride_b};
        const wide_t wb2{b + 2 * stride_b};
        const wide_t wb3{b + 3 * stride_b};

        const auto c11 = eve::fma(a[0], wb0, a[1] * wb1);
        const auto c12 = eve::fma(a[2], wb2, a[3] * wb3);
        eve::store(wide_t{c} + c11 + c12, c);

        const auto c21 = eve::fma(a[stride_a], wb0, a[stride_a + 1] * wb1);
        const auto c22 = eve::fma(a[stride_a + 2], wb2, a[stride_a + 3] * wb3);
        eve::store(wide_t{c + stride_c} + c21 + c22, c + stride_c);
    }

    template<typename T>
    void kernel_248(const T* a, const int stride_a, const T* b, const int stride_b, T* c, const int stride_c) {
        using wide_t = eve::wide<T, eve::fixed<8>>;
        const wide_t wb0{b};
        const wide_t wb1{b + stride_b};
        const wide_t wb2{b + 2 * stride_b};
        const wide_t wb3{b + 3 * stride_b};

        const auto c11 = eve::fma(a[0], wb0, a[1] * wb1);
        const auto c12 = eve::fma(a[2], wb2, a[3] * wb3);
        eve::store(wide_t{c} + c11 + c12, c);

        const auto c21 = eve::fma(a[stride_a], wb0, a[stride_a + 1] * wb1);
        const auto c22 = eve::fma(a[stride_a + 2], wb2, a[stride_a + 3] * wb3);
        eve::store(wide_t{c + stride_c} + c21 + c22, c + stride_c);
    }

    ///////////////////////////////////////
    //         2x8 * 8xX kernels         //
    ///////////////////////////////////////

    template<typename T>
    void kernel_281(const T* a, const int stride_a, const T* b, const int stride_b, T* c, const int stride_c) {
        using wide_t = eve::wide<T, eve::fixed<8>>;
        const wide_t wa1{a};
        const wide_t wa2{a + stride_a};
        const wide_t wb{[=](auto i, auto) { return b[i * stride_b]; }};

        c[0] += eve::reduce(wa1 * wb);
        c[stride_c] += eve::reduce(wa2 * wb);
    }

    template<typename T>
    void kernel_282(const T* a, const int stride_a, const T* b, const int stride_b, T* c, const int stride_c) {
        using wide_t = eve::wide<T, eve::fixed<4>>;

        const wide_t wa0 = wide_t{a[0], a[0], a[stride_a], a[stride_a]};
        const wide_t wb0 = wide_t{b[0], b[1], b[0], b[1]};
        const wide_t wa1 = wide_t{a[1], a[1], a[stride_a + 1], a[stride_a + 1]};
        const wide_t wb1 = wide_t{b[stride_b], b[stride_b + 1], b[stride_b], b[stride_b + 1]};
        const wide_t wc0 = eve::fma(wa0, wb0, wa1 * wb1);

        const wide_t wa2 = wide_t{a[2], a[2], a[stride_a + 2], a[stride_a + 2]};
        const wide_t wb2 = wide_t{b[2 * stride_b], b[2 * stride_b + 1], b[2 * stride_b], b[2 * stride_b + 1]};
        const wide_t wa3 = wide_t{a[3], a[3], a[stride_a + 3], a[stride_a + 3]};
        const wide_t wb3 = wide_t{b[3 * stride_b], b[3 * stride_b + 1], b[3 * stride_b], b[3 * stride_b + 1]};
        const wide_t wc1 = eve::fma(wa2, wb2, wa3 * wb3);

        const wide_t wa4 = wide_t{a[4], a[4], a[stride_a + 4], a[stride_a + 4]};
        const wide_t wb4 = wide_t{b[4 * stride_b], b[4 * stride_b + 1], b[4 * stride_b], b[4 * stride_b + 1]};
        const wide_t wa5 = wide_t{a[5], a[5], a[stride_a + 5], a[stride_a + 5]};
        const wide_t wb5 = wide_t{b[5 * stride_b], b[5 * stride_b + 1], b[5 * stride_b], b[5 * stride_b + 1]};
        const wide_t wc2 = eve::fma(wa4, wb4, wa5 * wb5);

        const wide_t wa6 = wide_t{a[6], a[6], a[stride_a + 6], a[stride_a + 6]};
        const wide_t wb6 = wide_t{b[6 * stride_b], b[6 * stride_b + 1], b[6 * stride_b], b[6 * stride_b + 1]};
        const wide_t wa7 = wide_t{a[7], a[7], a[stride_a + 7], a[stride_a + 7]};
        const wide_t wb7 = wide_t{b[7 * stride_b], b[7 * stride_b + 1], b[7 * stride_b], b[7 * stride_b + 1]};
        const wide_t wc3 = eve::fma(wa6, wb6, wa7 * wb7);

        const auto res = wc0 + wc1 + wc2 + wc3;
        c[0] += res.get(0);
        c[1] += res.get(1);
        c[stride_c] += res.get(2);
        c[stride_c + 1] += res.get(3);
    }

    template<typename T>
    void kernel_284(const T* a, const int stride_a, const T* b, const int stride_b, T* c, const int stride_c) {
        using wide_t = eve::wide<T, eve::fixed<4>>;

        const wide_t wb0{b};
        const wide_t wb1{b + stride_b};
        const wide_t wb2{b + 2 * stride_b};
        const wide_t wb3{b + 3 * stride_b};
        const wide_t wb4{b + 4 * stride_b};
        const wide_t wb5{b + 5 * stride_b};
        const wide_t wb6{b + 6 * stride_b};
        const wide_t wb7{b + 7 * stride_b};

        const auto wab00 = eve::fma(a[0], wb0, a[1] * wb1);
        const auto wab01 = eve::fma(a[2], wb2, a[3] * wb3);
        const auto wab02 = eve::fma(a[4], wb4, a[5] * wb5);
        const auto wab03 = eve::fma(a[6], wb6, a[7] * wb7);

        const auto wab10 = eve::fma(a[stride_a], wb0, a[stride_a + 1] * wb1);
        const auto wab11 = eve::fma(a[stride_a + 2], wb2, a[stride_a + 3] * wb3);
        const auto wab12 = eve::fma(a[stride_a + 4], wb4, a[stride_a + 5] * wb5);
        const auto wab13 = eve::fma(a[stride_a + 6], wb6, a[stride_a + 7] * wb7);

        eve::store(wide_t{c} + wab00 + wab01 + wab02 + wab03, c);
        eve::store(wide_t{c + stride_c} + wab10 + wab11 + wab12 + wab13, c + stride_c);
    }

    template<typename T>
    void kernel_288(const T* a, const int stride_a, const T* b, const int stride_b, T* c, const int stride_c) {
        using wide_t = eve::wide<T, eve::fixed<8>>;

        const wide_t wb0{b};
        const wide_t wb1{b + stride_b};
        const wide_t wb2{b + 2 * stride_b};
        const wide_t wb3{b + 3 * stride_b};
        const wide_t wb4{b + 4 * stride_b};
        const wide_t wb5{b + 5 * stride_b};
        const wide_t wb6{b + 6 * stride_b};
        const wide_t wb7{b + 7 * stride_b};

        const auto wab00 = eve::fma(a[0], wb0, a[1] * wb1);
        const auto wab01 = eve::fma(a[2], wb2, a[3] * wb3);
        const auto wab02 = eve::fma(a[4], wb4, a[5] * wb5);
        const auto wab03 = eve::fma(a[6], wb6, a[7] * wb7);

        const auto wab10 = eve::fma(a[stride_a], wb0, a[stride_a + 1] * wb1);
        const auto wab11 = eve::fma(a[stride_a + 2], wb2, a[stride_a + 3] * wb3);
        const auto wab12 = eve::fma(a[stride_a + 4], wb4, a[stride_a + 5] * wb5);
        const auto wab13 = eve::fma(a[stride_a + 6], wb6, a[stride_a + 7] * wb7);

        eve::store(wide_t{c} + wab00 + wab01 + wab02 + wab03, c);
        eve::store(wide_t{c + stride_c} + wab10 + wab11 + wab12 + wab13, c + stride_c);
    }
} // namespace gemm::detail

#endif
