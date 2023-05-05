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

        const wide_t wa0{[=](auto i, auto) { return a[i * stride_a]; }};
        const wide_t wab0 = wa0 * wb;
        const wide_t wa1 = wide_t{[=](auto i, auto) { return a[(i + 4) * stride_a]; }};
        const wide_t wab1 = wa1 * wb;

        c[0] += wab0.get(0);
        c[stride_c] += wab0.get(1);
        c[2 * stride_c] += wab0.get(2);
        c[3 * stride_c] += wab0.get(3);
        c[4 * stride_c] += wab1.get(0);
        c[5 * stride_c] += wab1.get(1);
        c[6 * stride_c] += wab1.get(2);
        c[7 * stride_c] += wab1.get(3);
    }

    template<typename T>
    void kernel_812(const T* a, const int stride_a, const T* b, const int /* stride_b */, T* c, const int stride_c) {
        using wide_t = eve::wide<T, eve::fixed<4>>;
        const wide_t wb{b[0], b[1], b[0], b[1]};
        const wide_t wa0{a[0], a[0], a[stride_a], a[stride_a]};
        const wide_t wa1{a[2 * stride_a], a[2 * stride_a], a[3 * stride_a], a[3 * stride_a]};
        const wide_t wa2{a[4 * stride_a], a[4 * stride_a], a[5 * stride_a], a[5 * stride_a]};
        const wide_t wa3{a[6 * stride_a], a[6 * stride_a], a[7 * stride_a], a[7 * stride_a]};

        const auto wab0 = wa0 * wb;
        const auto wab1 = wa1 * wb;
        const auto wab2 = wa2 * wb;
        const auto wab3 = wa3 * wb;

        c[0] += wab0.get(0);
        c[1] += wab0.get(1);
        c[stride_c] += wab0.get(2);
        c[stride_c + 1] += wab0.get(3);
        c[2 * stride_c] += wab1.get(0);
        c[2 * stride_c + 1] += wab1.get(1);
        c[3 * stride_c] += wab1.get(2);
        c[3 * stride_c + 1] += wab1.get(3);
        c[4 * stride_c] += wab2.get(0);
        c[4 * stride_c + 1] += wab2.get(1);
        c[5 * stride_c] += wab2.get(2);
        c[5 * stride_c + 1] += wab2.get(3);
        c[6 * stride_c] += wab3.get(0);
        c[6 * stride_c + 1] += wab3.get(1);
        c[7 * stride_c] += wab3.get(2);
        c[7 * stride_c + 1] += wab3.get(3);
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
        const auto wab = eve::fma(wa0, b[0], wa1 * b[stride_b]);

        c[0] += wab.get(0);
        c[stride_c] += wab.get(1);
        c[2 * stride_c] += wab.get(2);
        c[3 * stride_c] += wab.get(3);
        c[4 * stride_c] += wab.get(4);
        c[5 * stride_c] += wab.get(5);
        c[6 * stride_c] += wab.get(6);
        c[7 * stride_c] += wab.get(7);
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

        const auto wab0 = eve::fma(a[0], wb0, a[1] * wb1);
        const auto wab1 = eve::fma(a[stride_a], wb0, a[stride_a + 1] * wb1);
        const auto wab2 = eve::fma(a[2 * stride_a], wb0, a[2 * stride_a + 1] * wb1);
        const auto wab3 = eve::fma(a[3 * stride_a], wb0, a[3 * stride_a + 1] * wb1);
        const auto wab4 = eve::fma(a[4 * stride_a], wb0, a[4 * stride_a + 1] * wb1);
        const auto wab5 = eve::fma(a[5 * stride_a], wb0, a[5 * stride_a + 1] * wb1);
        const auto wab6 = eve::fma(a[6 * stride_a], wb0, a[6 * stride_a + 1] * wb1);
        const auto wab7 = eve::fma(a[7 * stride_a], wb0, a[7 * stride_a + 1] * wb1);

        eve::store(wide_t{c} + wab0, c);
        eve::store(wide_t{c + stride_c} + wab1, c + stride_c);
        eve::store(wide_t{c + 2 * stride_c} + wab2, c + 2 * stride_c);
        eve::store(wide_t{c + 3 * stride_c} + wab3, c + 3 * stride_c);
        eve::store(wide_t{c + 4 * stride_c} + wab4, c + 4 * stride_c);
        eve::store(wide_t{c + 5 * stride_c} + wab5, c + 5 * stride_c);
        eve::store(wide_t{c + 6 * stride_c} + wab6, c + 6 * stride_c);
        eve::store(wide_t{c + 7 * stride_c} + wab7, c + 7 * stride_c);
    }

    template<typename T>
    void kernel_828(const T* a, const int stride_a, const T* b, const int stride_b, T* c, const int stride_c) {
        using wide_t = eve::wide<T, eve::fixed<8>>;
        const wide_t wb0{b};
        const wide_t wb1{b + stride_b};

        const auto wab0 = eve::fma(a[0], wb0, a[1] * wb1);
        const auto wab1 = eve::fma(a[stride_a], wb0, a[stride_a + 1] * wb1);
        const auto wab2 = eve::fma(a[2 * stride_a], wb0, a[2 * stride_a + 1] * wb1);
        const auto wab3 = eve::fma(a[3 * stride_a], wb0, a[3 * stride_a + 1] * wb1);
        const auto wab4 = eve::fma(a[4 * stride_a], wb0, a[4 * stride_a + 1] * wb1);
        const auto wab5 = eve::fma(a[5 * stride_a], wb0, a[5 * stride_a + 1] * wb1);
        const auto wab6 = eve::fma(a[6 * stride_a], wb0, a[6 * stride_a + 1] * wb1);
        const auto wab7 = eve::fma(a[7 * stride_a], wb0, a[7 * stride_a + 1] * wb1);

        eve::store(wide_t{c} + wab0, c);
        eve::store(wide_t{c + stride_c} + wab1, c + stride_c);
        eve::store(wide_t{c + 2 * stride_c} + wab2, c + 2 * stride_c);
        eve::store(wide_t{c + 3 * stride_c} + wab3, c + 3 * stride_c);
        eve::store(wide_t{c + 4 * stride_c} + wab4, c + 4 * stride_c);
        eve::store(wide_t{c + 5 * stride_c} + wab5, c + 5 * stride_c);
        eve::store(wide_t{c + 6 * stride_c} + wab6, c + 6 * stride_c);
        eve::store(wide_t{c + 7 * stride_c} + wab7, c + 7 * stride_c);
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

        const auto wab0 = eve::fma(a[0], wb0, a[1] * wb1);
        const auto wab1 = eve::fma(a[2], wb2, a[3] * wb3);
        eve::store(wide_t{c} + wab0 + wab1, c);

        const auto wab2 = eve::fma(a[stride_a], wb0, a[stride_a + 1] * wb1);
        const auto wab3 = eve::fma(a[stride_a + 2], wb2, a[stride_a + 3] * wb3);
        eve::store(wide_t{c + stride_c} + wab2 + wab3, c + stride_c);

        const auto wab4 = eve::fma(a[2 * stride_a], wb0, a[2 * stride_a + 1] * wb1);
        const auto wab5 = eve::fma(a[2 * stride_a + 2], wb2, a[2 * stride_a + 3] * wb3);
        eve::store(wide_t{c + 2 * stride_c} + wab4 + wab5, c + 2 * stride_c);

        const auto wab6 = eve::fma(a[3 * stride_a], wb0, a[3 * stride_a + 1] * wb1);
        const auto wab7 = eve::fma(a[3 * stride_a + 2], wb2, a[3 * stride_a + 3] * wb3);
        eve::store(wide_t{c + 3 * stride_c} + wab6 + wab7, c + 3 * stride_c);

        const auto wab8 = eve::fma(a[4 * stride_a], wb0, a[4 * stride_a + 1] * wb1);
        const auto wab9 = eve::fma(a[4 * stride_a + 2], wb2, a[4 * stride_a + 3] * wb3);
        eve::store(wide_t{c + 4 * stride_c} + wab8 + wab9, c + 4 * stride_c);

        const auto wab10 = eve::fma(a[5 * stride_a], wb0, a[5 * stride_a + 1] * wb1);
        const auto wab11 = eve::fma(a[5 * stride_a + 2], wb2, a[5 * stride_a + 3] * wb3);
        eve::store(wide_t{c + 5 * stride_c} + wab10 + wab11, c + 5 * stride_c);

        const auto wab12 = eve::fma(a[6 * stride_a], wb0, a[6 * stride_a + 1] * wb1);
        const auto wab13 = eve::fma(a[6 * stride_a + 2], wb2, a[6 * stride_a + 3] * wb3);
        eve::store(wide_t{c + 6 * stride_c} + wab12 + wab13, c + 6 * stride_c);

        const auto wab14 = eve::fma(a[7 * stride_a], wb0, a[7 * stride_a + 1] * wb1);
        const auto wab15 = eve::fma(a[7 * stride_a + 2], wb2, a[7 * stride_a + 3] * wb3);
        eve::store(wide_t{c + 7 * stride_c} + wab14 + wab15, c + 7 * stride_c);
    }

    template<typename T>
    void kernel_848(const T* a, const int stride_a, const T* b, const int stride_b, T* c, const int stride_c) {
        using wide_t = eve::wide<T, eve::fixed<8>>;
        const wide_t wb0{b};
        const wide_t wb1{b + stride_b};
        const wide_t wb2{b + 2 * stride_b};
        const wide_t wb3{b + 3 * stride_b};

        const auto wab0 = eve::fma(a[0], wb0, a[1] * wb1);
        const auto wab1 = eve::fma(a[2], wb2, a[3] * wb3);
        eve::store(wide_t{c} + wab0 + wab1, c);

        const auto wab2 = eve::fma(a[stride_a], wb0, a[stride_a + 1] * wb1);
        const auto wab3 = eve::fma(a[stride_a + 2], wb2, a[stride_a + 3] * wb3);
        eve::store(wide_t{c + stride_c} + wab2 + wab3, c + stride_c);

        const auto wab4 = eve::fma(a[2 * stride_a], wb0, a[2 * stride_a + 1] * wb1);
        const auto wab5 = eve::fma(a[2 * stride_a + 2], wb2, a[2 * stride_a + 3] * wb3);
        eve::store(wide_t{c + 2 * stride_c} + wab4 + wab5, c + 2 * stride_c);

        const auto wab6 = eve::fma(a[3 * stride_a], wb0, a[3 * stride_a + 1] * wb1);
        const auto wab7 = eve::fma(a[3 * stride_a + 2], wb2, a[3 * stride_a + 3] * wb3);
        eve::store(wide_t{c + 3 * stride_c} + wab6 + wab7, c + 3 * stride_c);

        const auto wab8 = eve::fma(a[4 * stride_a], wb0, a[4 * stride_a + 1] * wb1);
        const auto wab9 = eve::fma(a[4 * stride_a + 2], wb2, a[4 * stride_a + 3] * wb3);
        eve::store(wide_t{c + 4 * stride_c} + wab8 + wab9, c + 4 * stride_c);

        const auto wab10 = eve::fma(a[5 * stride_a], wb0, a[5 * stride_a + 1] * wb1);
        const auto wab11 = eve::fma(a[5 * stride_a + 2], wb2, a[5 * stride_a + 3] * wb3);
        eve::store(wide_t{c + 5 * stride_c} + wab10 + wab11, c + 5 * stride_c);

        const auto wab12 = eve::fma(a[6 * stride_a], wb0, a[6 * stride_a + 1] * wb1);
        const auto wab13 = eve::fma(a[6 * stride_a + 2], wb2, a[6 * stride_a + 3] * wb3);
        eve::store(wide_t{c + 6 * stride_c} + wab12 + wab13, c + 6 * stride_c);

        const auto wab14 = eve::fma(a[7 * stride_a], wb0, a[7 * stride_a + 1] * wb1);
        const auto wab15 = eve::fma(a[7 * stride_a + 2], wb2, a[7 * stride_a + 3] * wb3);
        eve::store(wide_t{c + 7 * stride_c} + wab14 + wab15, c + 7 * stride_c);
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
