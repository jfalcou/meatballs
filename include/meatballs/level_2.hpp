#ifndef MEATBALLS_LEVEL_2_HPP
#define MEATBALLS_LEVEL_2_HPP

#include <span>

#include <eve/module/algo.hpp>

#include <meatballs/level_1.hpp>

#include <utilities.hpp>

// INFO: row major matrix

// INFO: no dimension parameters (m, n)
// INFO: no increment parameters (incx, incy)
// INFO: no first-dimension parameters (lda)

namespace meatballs {
// GENERAL

template <typename T>
void xgemv_n(T alpha, std::span<T> a, std::span<T> x, T beta, std::span<T> y) {
  auto m = a.size() / x.size();
  auto n = x.size();

  for (auto i = 0; i < m; i++) {
    auto ai = get_row(n, a, i);

    auto t = alpha * xdot(ai, x);

    y[i] = eve::fma(beta, y[i], t);
  }
};

template <typename T>
void xgemv_t(T alpha, std::span<T> a, std::span<T> x, T beta, std::span<T> y) {
  auto m = a.size() / x.size();
  auto n = x.size();

  auto aj = get_column(m, a, 0);

  auto t = alpha * x[0];

  eve::algo::transform_to(eve::views::zip(aj, y), y, [t, beta](auto aj_y) {
    auto [aj, y] = aj_y;

    return eve::fma(t, aj, eve::fma(beta, y, T(0)));
  });

  for (auto j = 1; j < n; j++) {
    aj = get_column(m, a, j);

    t = alpha * x[j];

    xaxpy(t, aj, y);
  }
};

template <typename T>
void xgemv_c(T alpha, std::span<T> a, std::span<T> x, T beta, std::span<T> y){
    // TODO
};

template <typename T>
void xgemv(char trans, T alpha, std::span<T> a, std::span<T> x, T beta,
           std::span<T> y) {
  if (trans == 'N' || trans == 'n')
    xgemv_n(alpha, a, x, beta, y);
  else if (trans == 'T' || trans == 't')
    xgemv_t(alpha, a, x, beta, y);
  else if (trans == 'C' || trans == 'c')
    xgemv_c(alpha, a, x, beta, y);
};

template <typename T>
void xgbmv(std::size_t kl, std::size_t ku, T alpha, std::span<T> a,
           std::span<T> x, T beta, std::span<T> y){
    // TODO: banded
};

// HERMITIAN

template <typename T>
void xhemv(T alpha, std::span<T> a, std::span<T> x, T beta, std::span<T> y){
    // TODO: complex
};

template <typename T>
void xhbmv(std::size_t k, T alpha, std::span<T> a, std::span<T> x, T beta,
           std::span<T> y){
    // TODO: complex
};

template <typename T>
void xhpmv(T alpha, std::span<T> ap, std::span<T> x, T beta, std::span<T> y){
    // TODO: complex
};

// SYMMETRIC

template <typename T>
void xsymv_u(T alpha, std::span<T> a, std::span<T> x, T beta, std::span<T> y) {
  // TODO
};

template <typename T>
void xsymv_l_kernel_4x4(std::size_t to,                 //
                        std::vector<eve::wide<T>> ai,   //
                        std::span<T> x, std::span<T> y, //
                        eve::wide<T> &w0, eve::wide<T> &w1) {
  for (auto j = 0; j < to; j++) {
    y[j] += eve::reduce(w0 * ai[j]);

    w1 += ai[j] * x[j];
  }
}

template <typename T>
void xsymv_l_kernel_1x4(std::size_t from, std::size_t to,   //
                        std::vector<eve::wide<T>> ai,       //
                        std::span<T> x, std::span<T> y,     //
                        eve::wide<T> &w0, eve::wide<T> &w1) {
  for (auto j = from; j < to; j++) {
    y[j] += eve::reduce(w0 * ai[j]);

    w1 += ai[j] * x[j];
  }
}

template <typename T>
void xsymv_l_kernel_8x1(std::size_t to,                 //
                        std::span<T> a0,                //
                        std::span<T> x, std::span<T> y, //
                        float* w0, float* w1) {
  constexpr auto s = eve::wide<T>::size();

  for (auto i = 0; i < (to / s) * s; i += s) {
    for (auto k = 0; k < s; k++) {
      y[i + k] += *w0 * a0[i + k];

      *w1 += a0[i] * x[i + k];
    }
  }
}

template <typename T>
void xsymv_l(T alpha, std::span<T> a, std::span<T> x, T beta, std::span<T> y) {
  constexpr auto s = eve::wide<T>::size();

  auto m = a.size() / x.size();
  auto n = x.size();

  for (auto i = 0; i < n; i += s) {
    auto w0 = eve::wide<T>([alpha, x, i] (auto k, auto) {
      return alpha * x[i + k];
    });

    auto w1 = eve::wide<T>(T(0));

    auto ai = get_rows(n, a, i);

    auto b = (i / (2 * s)) * (2 * s);

    if (b)
      xsymv_l_kernel_4x4(b, ai, x, y, w0, w1);
    if (b < i)
      xsymv_l_kernel_1x4(b, i, ai, x, y, w0, w1);

    for (auto k = 0; k < s; k++) {
      auto ai = get_row(m, a, i + k);

      for (auto j = i; j < i + k; j++) {
        y[j] += w0.get(k) * ai[j];

        w1.set(k, w1.get(k) + ai[j] * x[j]);
      }

      y[i + k] += w0.get(k) * ai[i + k] + alpha * w1.get(k);
    }
  }
  
  for (auto i = (m / s) * s; i < m; i++) {
    auto w0 = alpha * x[i];

    auto w1 = 0.0f;

    auto a0 = get_row(n, a, i);

    auto b = (i / (2 * s)) * (2 * s);

    if (b)
      xsymv_l_kernel_8x1(b, a0, x, y, &w0, &w1);

    for (auto j = b; j < i; j++) {
      y[j] += w0 * a0[j];

      w1 += a0[j] * x[j];
    }

    y[i] += w0 * a0[i] + alpha * w1;
  }
};

template <typename T>
void xsymv(char uplo, T alpha, std::span<T> a, std::span<T> x, T beta, std::span<T> y) {
  if (uplo == 'U' || uplo == 'u')
    xsymv_u(alpha, a, x, beta, y);
  else if (uplo == 'L' || uplo == 'l')
    xsymv_l(alpha, a, x, beta, y);
};

template <typename T>
void xsbmv(std::size_t k, T alpha, std::span<T> a, std::span<T> x, T beta,
           std::span<T> y){
    // TODO: banded
};

template <typename T>
void xspmv(T alpha, std::span<T> ap, std::span<T> x, T beta, std::span<T> y) {
  // TODO: packed
}

// TRIANGULAR

template <typename T>
void xtrmv(std::span<T> a, std::span<T> x){
    // TODO
};

template <typename T>
void xtbmv(char uplo, std::size_t k, std::span<T> a, std::span<T> x){
    // TODO: banded
};

template <typename T>
void xtpmv(std::span<T> ap, std::span<T> x){
    // TODO: packed
};

template <typename T>
void xtrsv(std::span<T> a, std::span<T> x){
    // TODO: solver
};

template <typename T>
void xtbsv(std::size_t k, std::span<T> a, std::span<T> x){
    // TODO: solver
};

template <typename T>
void xtpsv(std::span<T> ap, std::span<T> x){
    // TODO: solver
};

// GENERAL

template <typename T>
void xger(T alpha, std::span<T> x, std::span<T> y, std::span<T> a){
    // TODO
};

template <typename T>
void xgeru(T alpha, std::span<T> x, std::span<T> y, std::span<T> a){
    // TODO: complex
};

template <typename T>
void xgerc(T alpha, std::span<T> x, std::span<T> y, std::span<T> a){
    // TODO: complex
};

// HERMITIAN

template <typename T>
void xher(T alpha, std::span<T> x, std::span<T> a){
    // TODO: complex
};

template <typename T>
void xhpr(T alpha, std::span<T> x, std::span<T> ap){
    // TODO: complex
};

template <typename T>
void xher2(T alpha, std::span<T> x, std::span<T> y, std::span<T> a){
    // TODO: complex
};

template <typename T>
void xhpr2(T alpha, std::span<T> x, std::span<T> y, std::span<T> ap) {
  // TODO: complex
}

// SYMMETRIC

template <typename T>
void xsyr(T alpha, std::span<T> x, std::span<T> a){
    // TODO
};

template <typename T>
void xspr(T alpha, std::span<T> x, std::span<T> ap){
    // TODO: packed
};

template <typename T>
void xsyr2(T alpha, std::span<T> x, std::span<T> y, std::span<T> a){
    // TODO
};

template <typename T>
void xspr2(T alpha, std::span<T> x, std::span<T> y, std::span<T> ap){
    // TODO: packed
};
} // namespace meatballs

#endif