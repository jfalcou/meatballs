#ifndef STRMV_HPP
#define STRMV_HPP

#include <span>

#include <utilities.hpp>

// INFO: row major matrix

// TODO: transpose and unit

void strmv_u(std::span<float> a, std::span<float> x) {
  auto n = x.size();

  for (auto i = 0; i < n; i++) {
    auto t = 0.0f;

    for (auto j = i; j < n; j++)
      t += a[i * n + j] * x[j];

    x[i] = t;
  }
}

void strmv_l(std::span<float> a, std::span<float> x) {
  auto n = x.size();

  for (auto i = 0; i < n; i++) {
    auto t = 0.0f;

    for (auto j = 0; j < n - i; j++)
      t += a[(n - i - 1) * n + j] * x[j];

    x[(n - i - 1)] = t;
  }
}

void strmv(char uplo, std::span<float> a, std::span<float> x) {
  if (uplo == 'U' || uplo == 'u')
    strmv_u(a, x);
  else if (uplo == 'L' || uplo == 'l')
    strmv_l(a, x);
};

#endif