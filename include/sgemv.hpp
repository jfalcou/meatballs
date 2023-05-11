#ifndef SGEMV_HPP
#define SGEMV_HPP

#include <span>

#include <utilities.hpp>

// INFO: column major matrix

void sgemv_n(float alpha, std::span<float> a, std::span<float> x, float beta,
          std::span<float> y) {
  auto m = a.size() / x.size();
  auto n = x.size();

  for (auto i = 0; i < m; i++) {
    y[i] *= beta;
    
    for (auto j = 0; j < n; j++) 
      y[i] += alpha * a[i + j * m] * x[j];
  }
}

void sgemv_t(float alpha, std::span<float> a, std::span<float> x, float beta,
          std::span<float> y) {
  auto m = a.size() / x.size();
  auto n = x.size();

  for (auto j = 0; j < n; j++) {
    y[j] *= beta;
    
    for (auto i = 0; i < m; i++) 
      y[j] += alpha * a[i + j * m] * x[i];
  }
}

void sgemv(char trans, float alpha, std::span<float> a, std::span<float> x, float beta,
           std::span<float> y) {
  if (trans == 'N' || trans == 'n')
    sgemv_n(alpha, a, x, beta, y);
  else if (trans == 'T' || trans == 't')
    sgemv_t(alpha, a, x, beta, y);
};

#endif