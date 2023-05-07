#include <iostream>

#include <nanobench.h>

#include <openblas/cblas.h>

#include <meatballs/single/level_2.hpp>

#include <utilities.hpp>

int main() {
  auto m = 4196;
  auto n = 4196;

  
  auto a = create_random_matrix<float>(m, n);
  auto alpha = create_random_scalar<float>();
  auto x = create_random_vector<float>(n);
  auto beta = create_random_scalar<float>();
  auto y = create_random_vector<float>(n);

  
  auto bench = ankerl::nanobench::Bench().relative(true);

  {
    bench.title("sgemv:N");

    auto y_ = std::vector<float>(y);

    bench.run("cblas", [&] { cblas_sgemv(CblasRowMajor, CblasNoTrans, m, n, alpha, a.data(), n, x.data(), 1, beta, y_.data(), 1); });
    
    y_ = std::vector<float>(y);

    bench.run("meatballs", [&] { meatballs::sgemv('N', alpha, a, x, beta, y_); });
  }

  {
    bench.title("sgemv:T");

    auto y_ = std::vector<float>(y);

    bench.run("cblas", [&] { cblas_sgemv(CblasRowMajor, CblasTrans, m, n, alpha, a.data(), n, x.data(), 1, beta, y_.data(), 1); });
    
    y_ = std::vector<float>(y);

    bench.run("meatballs", [&] { meatballs::sgemv('T', alpha, a, x, beta, y_); });
  }

  // TODO: sgemv:T

  // TODO: sgbmv

  // TODO: ssymv

  // TODO: ssbmv

  // TODO: sspmv

  // TODO: strmv

  // TODO: stbmv

  // TODO: stpmv

  // TODO: strsv

  // TODO: stmsv

  // TODO: stpsv

  // TODO: sger

  // TODO: ssyr

  // TODO: ssyr2

  return 0;
}