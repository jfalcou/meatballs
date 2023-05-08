#ifndef SSYMV_HPP
#define SSYMV_HPP

#include <span>

#include <eve/module/algo.hpp>

#include <utilities.hpp>

void ssymv_kernel_4x4(std::size_t to,                           //
                      std::span<float> a0, std::span<float> a1, //
                      std::span<float> a2, std::span<float> a3, //
                      std::span<float> x, std::span<float> y,   //
                      float* w0, float* w1) {
  for (auto i = 0; i < to; i++) {
    // different columns / different x
    y[i] += w0[0] * a0[i] + //
            w0[1] * a1[i] + //
            w0[2] * a2[i] + //
            w0[3] * a3[i];

    // same column / same x
    w1[0] += a0[i] * x[i];
    w1[1] += a1[i] * x[i];
    w1[2] += a2[i] * x[i];
    w1[3] += a3[i] * x[i];
  }
}

void ssymv_kernel_1x4(std::size_t from, std::size_t to,         //
                      std::span<float> a0, std::span<float> a1, //
                      std::span<float> a2, std::span<float> a3, //
                      std::span<float> x, std::span<float> y,   //
                      float* w0, float* w1) {
  for (auto i = from; i < to; i++) {
    // different columns / different x
    y[i] += w0[0] * a0[i] + //
            w0[1] * a1[i] + //
            w0[2] * a2[i] + //
            w0[3] * a3[i];

    // same column / same x
    w1[0] += a0[i] * x[i];
    w1[1] += a1[i] * x[i];
    w1[2] += a2[i] * x[i];
    w1[3] += a3[i] * x[i];
  }
}

void ssymv_kernel_8x1(std::size_t to,                         //
                      std::span<float> a0,                    //
                      std::span<float> x, std::span<float> y, //
                      float* w0, float* w1) {
  // TODO: why (to / 4) * 4? to = (k / 8) * 8...
  for (auto i = 0; i < (to / 4) * 4; i += 4) {
    // same column / same x
    y[i + 0] += *w0 * a0[i + 0];
    y[i + 1] += *w0 * a0[i + 1];
    y[i + 2] += *w0 * a0[i + 2];
    y[i + 3] += *w0 * a0[i + 3];

    // same column / same x
    *w1 += a0[i] * x[i + 0];
    *w1 += a0[i] * x[i + 1];
    *w1 += a0[i] * x[i + 2];
    *w1 += a0[i] * x[i + 3];
  }
}

void ssymv(float alpha, std::span<float> a, std::span<float> x, float beta,
           std::span<float> y) {
  // INFO: column major matrix

  auto m = a.size() / x.size();
  auto n = x.size();

  for (auto j = 0; j < n; j += 4) {
    float w0[4];
    w0[0] = alpha * x[j + 0];
    w0[1] = alpha * x[j + 1];
    w0[2] = alpha * x[j + 2];
    w0[3] = alpha * x[j + 3];

    float w1[4];
    w1[0] = 0.0f;
    w1[1] = 0.0f;
    w1[2] = 0.0f;
    w1[3] = 0.0f;

    auto a0 = get_column(m, a, j + 0);
    auto a1 = get_column(m, a, j + 1);
    auto a2 = get_column(m, a, j + 2);
    auto a3 = get_column(m, a, j + 3);

    auto b = (j / 8) * 8;

    // full block (4n x 4 and 4 x 4)
    if (b)
      ssymv_kernel_4x4(b, a0, a1, a2, a3, x, y, w0, w1);
    if (b < j)
      ssymv_kernel_1x4(b, j, a0, a1, a2, a3, x, y, w0, w1);

    // half block
    for (auto k = 0; k < 4; k++) {
      auto aj = get_column(m, a, j + k);

      // upper part
      for (auto i = j; i < j + k; i++) {
        y[i] += w0[k] * aj[i];

        w1[k] += aj[i] * x[i];
      }

      // diagonal
      y[j + k] += w0[k] * aj[j + k] + alpha * w1[k];
    }
  }

  for (auto j = (m / 4) * 4; j < m; j++) {
    auto w0 = alpha * x[j];

    auto w1 = 0.0f;

    auto a0 = get_column(m, a, j);

    auto b = (j / 8) * 8;

    // full block (4n x 4 and 4 x 4)
    if (b)
      ssymv_kernel_8x1(b, a0, x, y, &w0, &w1);

    // half block - upper part
    for (auto i = b; i < j; i++) {
      y[i] += w0 * a0[i];

      w1 += a0[i] * x[i];
    }

    // half block - diagonal
    y[j] += w0 * a0[j] + alpha * w1;
  }
}

#endif