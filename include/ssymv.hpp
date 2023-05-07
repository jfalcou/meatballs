#ifndef SSYMV_HPP
#define SSYMV_HPP

#include <span>

#include <eve/module/algo.hpp>

#include <utilities.hpp>

void ssymv_kernel_4x4(std::size_t to,                           //
                      std::span<float> a0, std::span<float> a1, //
                      std::span<float> a2, std::span<float> a3, //
                      std::span<float> x, std::span<float> y,   //
                      float* vertical, float* horizontal) {
  for (auto i = 0; i < to; i++) {
    // different columns / different x
    y[i] += vertical[0] * a0[i] + //
            vertical[1] * a1[i] + //
            vertical[2] * a2[i] + //
            vertical[3] * a3[i];

    // same column / same x
    horizontal[0] += a0[i] * x[i];
    horizontal[1] += a1[i] * x[i];
    horizontal[2] += a2[i] * x[i];
    horizontal[3] += a3[i] * x[i];
  }
}

void ssymv_kernel_1x4(std::size_t from, std::size_t to,         //
                      std::span<float> a0, std::span<float> a1, //
                      std::span<float> a2, std::span<float> a3, //
                      std::span<float> x, std::span<float> y,   //
                      float* vertical, float* horizontal) {
  for (auto i = from; i < to; i++) {
    // different columns / different x
    y[i] += vertical[0] * a0[i] + //
            vertical[1] * a1[i] + //
            vertical[2] * a2[i] + //
            vertical[3] * a3[i];

    // same column / same x
    horizontal[0] += a0[i] * x[i];
    horizontal[1] += a1[i] * x[i];
    horizontal[2] += a2[i] * x[i];
    horizontal[3] += a3[i] * x[i];
  }
}

void ssymv_kernel_8x1(std::size_t to,                         //
                      std::span<float> a0,                    //
                      std::span<float> x, std::span<float> y, //
                      float* vertical, float* horizontal) {
  // TODO: why (to / 4) * 4? to = (k / 8) * 8...
  for (auto i = 0; i < (to / 4) * 4; i += 4) {
    // same column / same x
    y[i + 0] += *vertical * a0[i + 0];
    y[i + 1] += *vertical * a0[i + 1];
    y[i + 2] += *vertical * a0[i + 2];
    y[i + 3] += *vertical * a0[i + 3];

    // same column / same x
    *horizontal += a0[i] * x[i + 0];
    *horizontal += a0[i] * x[i + 1];
    *horizontal += a0[i] * x[i + 2];
    *horizontal += a0[i] * x[i + 3];
  }
}

void ssymv(float alpha, std::span<float> a, std::span<float> x, float beta,
           std::span<float> y) {
  // INFO: column major matrix

  auto m = a.size() / x.size();

  for (auto j = 0; j < m; j += 4) {
    float vertical[4];
    vertical[0] = alpha * x[j + 0];
    vertical[1] = alpha * x[j + 1];
    vertical[2] = alpha * x[j + 2];
    vertical[3] = alpha * x[j + 3];

    float horizontal[4];
    horizontal[0] = 0.0f;
    horizontal[1] = 0.0f;
    horizontal[2] = 0.0f;
    horizontal[3] = 0.0f;

    auto a0 = get_column(m, a, j + 0);
    auto a1 = get_column(m, a, j + 1);
    auto a2 = get_column(m, a, j + 2);
    auto a3 = get_column(m, a, j + 3);

    auto b = (j / 8) * 8;

    // full block (4n x 4 and 4 x 4)
    if (b)
      ssymv_kernel_4x4(b, a0, a1, a2, a3, x, y, vertical, horizontal);
    if (b < j)
      ssymv_kernel_1x4(b, j, a0, a1, a2, a3, x, y, vertical, horizontal);

    // half block
    for (auto k = 0; k < 4; k++) {
      auto aj = get_column(m, a, j + k);

      // upper part
      for (auto i = j; i < j + k; i++) {
        y[i] += vertical[k] * aj[i];

        horizontal[k] += aj[i] * x[i];
      }

      // diagonal
      y[j + k] += vertical[k] * aj[k] + alpha * horizontal[k];
    }
  }

  for (auto j = (m / 4) * 4; j < m; j++) {
    auto vertical = alpha * x[j];

    auto horizontal = 0.0f;

    auto a0 = get_column(m, a, j);

    auto b = (j / 8) * 8;

    // full block (4n x 4 and 4 x 4)
    if (b)
      ssymv_kernel_8x1(b, a0, x, y, &vertical, &horizontal);

    // half block - upper part
    for (auto i = b; i < j; i++) {
      y[i] += vertical * a0[i];

      horizontal += a0[i] * x[i];
    }

    // half block - diagonal
    y[j] += vertical * a0[j] + alpha * horizontal;
  }
}

#endif