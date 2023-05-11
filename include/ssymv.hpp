#ifndef SSYMV_HPP
#define SSYMV_HPP

#include <span>

#include <utilities.hpp>

// INFO: column major matrix

void ssymv_u(float alpha, std::span<float> a, std::span<float> x, float beta,
          std::span<float> y) {
  auto m = y.size();

  for (auto j = 0; j < m; j++) {
    y[j] *= beta;

    y[j] += alpha * a[j + j * m] * x[j];

    for (auto i = 0; i < j; i++)
      y[j] += alpha * a[i + j * m] * x[i];
  }

  for (auto j = 0; j < m; j++)
    for (auto i = 0; i < j; i++) 
      y[i] += alpha * a[i + j * m] * x[j];
}

void ssymv_l(float alpha, std::span<float> a, std::span<float> x, float beta,
          std::span<float> y) {
  auto m = y.size();

  for (auto j = 0; j < m; j++) {
    y[j] *= beta;

    y[j] += alpha * a[j + j * m] * x[j];

    for (auto i = j + 1; i < m; i++)
      y[j] += alpha * a[i + j * m] * x[i];
  }

  for (auto j = 0; j < m; j++)
    for (auto i = j + 1; i < m; i++)
      y[i] += alpha * a[i + j * m] * x[j];
}

void ssymv(char uplo, float alpha, std::span<float> a, std::span<float> x, float beta,
           std::span<float> y) {
  if (uplo == 'U' || uplo == 'u')
    ssymv_u(alpha, a, x, beta, y);
  else if (uplo == 'L' || uplo == 'l')
    ssymv_l(alpha, a, x, beta, y);
};

#endif