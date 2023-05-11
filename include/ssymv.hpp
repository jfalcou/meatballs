#ifndef SSYMV_HPP
#define SSYMV_HPP

#include <span>

#include <utilities.hpp>

// INFO: column major matrix

void ssymv_u(float alpha, std::span<float> a, std::span<float> x, float beta,
          std::span<float> y) {
  auto m = y.size();

  for (auto i = 0; i < m; i++) {
    y[i] *= beta;
    
    for (auto j = i; j < m; j++) 
      y[i] += alpha * a[i + j * m] * x[j];
  }

  for (auto i = 0; i < m; i++)
    for (auto j = i + 1; j < m; j++) 
      y[j] += alpha * a[i + j * m] * x[i];
}

void ssymv_l(float alpha, std::span<float> a, std::span<float> x, float beta,
          std::span<float> y) {
  auto m = y.size();

  for (auto j = 0; j < m; j++) {
    y[j] *= beta;

    for (auto i = j; i < m; i++)
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