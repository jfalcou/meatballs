#ifndef MEATBALLS_LEVEL_2_HPP
#define MEATBALLS_LEVEL_2_HPP

#include <span>

#include <eve/module/algo.hpp>

#include <meatballs/level_1.hpp>

#include <utilities.hpp>

// INFO: no dimension parameters (m, n)
// INFO: no increment parameters (incx, incy)
// INFO: no first-dimension parameters (lda)

namespace meatballs {
// GENERAL

template <typename T>
void xgemv_n(T alpha, std::span<T> a, std::span<T> x, T beta, std::span<T> y) {
  // INFO: column major matrix
  
  auto m = a.size() / x.size();
  auto n = x.size();

  auto aj = get_column(n, a, 0);

  auto t = alpha * x[0];

  eve::algo::transform_to(eve::views::zip(aj, y), y, [t, beta](auto aj_y) {
    auto [aj, y] = aj_y;

    return eve::fma(t, aj, eve::fma(beta, y, T(0)));
  });

  for (auto j = 1; j < n; j++) {
    aj = get_column(n, a, j);

    t = alpha * x[j];

    xaxpy(t, aj, y);
  }
};

template <typename T>
void xgemv_t(T alpha, std::span<T> a, std::span<T> x, T beta, std::span<T> y) {
  // INFO: column major matrix
  
  auto m = a.size() / x.size();
  auto n = x.size();

  for (auto j = 0; j < m; j++) {
    auto aj = get_column(n, a, j);

    auto t = alpha * xdot(aj, x);

    y[j] = eve::fma(beta, y[j], t);
  }
};

template <typename T>
void xgemv_c(T alpha, std::span<T> a, std::span<T> x, T beta, std::span<T> y){
    // TODO
};

template <typename T>
void xgemv(char trans, T alpha, std::span<T> a, std::span<T> x, T beta,
           std::span<T> y) {
  // INFO: column major matrix

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
  // INFO: column major matrix

  auto n = x.size();

  for (auto j = 0; j < n; j++) {
    y[j] *= beta;

    y[j] += alpha * a[j + j * n] * x[j];

    auto i = 0;
    auto m = j;

    auto aj = std::span<T>(&a[i + j * n], m);
    auto yi = std::span<T>(&y[i], m);
    auto xi = std::span<T>(&x[i], m);

    y[j] += alpha * xdot(aj, xi);
  }

  for (auto j = 0; j < n; j++) {
    auto i = 0;
    auto m = j;

    auto aj = std::span<T>(&a[i + j * n], m);
    auto yi = std::span<T>(&y[i], m);
    auto xi = std::span<T>(&x[i], m);

    xaxpy(alpha * x[j], aj, yi);
  }
}

template <typename T>
void xsymv_l(T alpha, std::span<T> a, std::span<T> x, T beta, std::span<T> y) {
  // INFO: column major matrix

  auto n = x.size();

  for (auto j = 0; j < n; j++) {
    y[j] *= beta;

    y[j] += alpha * a[j + j * n] * x[j];

    auto i = j + 1;
    auto m = n - i;

    auto aj = std::span<T>(&a[i + j * n], m);
    auto yi = std::span<T>(&y[i], m);
    auto xi = std::span<T>(&x[i], m);

    y[j] += alpha * xdot(aj, xi);
  }

  for (auto j = 0; j < n; j++) {
    auto i = j + 1;
    auto m = n - i;

    auto aj = std::span<T>(&a[i + j * n], m);
    auto yi = std::span<T>(&y[i], m);
    auto xi = std::span<T>(&x[i], m);

    xaxpy(alpha * x[j], aj, yi);
  }
}

template <typename T>
void xsymv(char uplo, T alpha, std::span<T> a, std::span<T> x, T beta, std::span<T> y) {
  // INFO: column major matrix

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
void xtrmv_u(std::span<T> a, std::span<T> x) {
  // INFO: row major matrix

  auto n = x.size();

  for (auto i = 0; i < n; i++) {
    auto j = i;
    auto m = n - j;

    auto aj = std::span<T>(&a[i * n + j], m);
    auto xi = std::span<T>(&x[j], m);

    x[i] = xdot(aj, xi);;
  }
};

template <typename T>
void xtrmv_l(std::span<T> a, std::span<T> x) {
  // INFO: row major matrix

  auto n = x.size();

  for (auto i = 0; i < n; i++) {
    auto j = 0;
    auto m = n - i;

    auto aj = std::span<T>(&a[(n - i - 1) * n + j], m);
    auto xi = std::span<T>(&x[j], m);

    x[(n - i - 1)] = xdot(aj, xi);;
  }
};

template <typename T>
void xtrmv(char uplo, std::span<T> a, std::span<T> x) {
  // INFO: row major matrix

  // TODO: transpose and unit

  if (uplo == 'U' || uplo == 'u')
    xtrmv_u(a, x);
  else if (uplo == 'L' || uplo == 'l')
    xtrmv_l(a, x);
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