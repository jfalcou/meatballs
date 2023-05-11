#include <iostream>

#include <nanobench.h>

#include <openblas/cblas.h>

#include <meatballs/single/level_2.hpp>

#include <utilities.hpp>

#include <sgemv.hpp>
#include <ssymv.hpp>
#include <strmv.hpp>

int main() {
  std::srand(std::time(nullptr));
  
  auto m = 4096;
  auto n = 4096;

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
    
    y_ = std::vector<float>(y);

    bench.run("naive", [&] { sgemv('N', alpha, a, x, beta, y_); });
  }

  {
    bench.title("sgemv:T");

    auto y_ = std::vector<float>(y);

    bench.run("cblas", [&] { cblas_sgemv(CblasRowMajor, CblasTrans, m, n, alpha, a.data(), n, x.data(), 1, beta, y_.data(), 1); });
    
    y_ = std::vector<float>(y);

    bench.run("meatballs", [&] { meatballs::sgemv('T', alpha, a, x, beta, y_); });
    
    y_ = std::vector<float>(y);

    bench.run("naive", [&] { sgemv('T', alpha, a, x, beta, y_); });
  }

  // TODO: sgemv:C

  // TODO: sgbmv

  {
    bench.title("ssymv:U");

    auto y_ = std::vector<float>(y);

    bench.run("cblas", [&] { cblas_ssymv(CblasColMajor, CblasUpper, n, alpha, a.data(), n, x.data(), 1, 1.0f, y_.data(), 1); });
    
    y_ = std::vector<float>(y);

    bench.run("meatballs", [&] { meatballs::ssymv('U', alpha, a, x, 1.0f, y_); });
    
    y_ = std::vector<float>(y);

    bench.run("naive", [&] { ssymv('U', alpha, a, x, 1.0f, y_); });
  }

  {
    bench.title("ssymv:L");

    auto y_ = std::vector<float>(y);

    bench.run("cblas", [&] { cblas_ssymv(CblasColMajor, CblasLower, n, alpha, a.data(), n, x.data(), 1, 1.0f, y_.data(), 1); });
    
    y_ = std::vector<float>(y);

    bench.run("meatballs", [&] { meatballs::ssymv('L', alpha, a, x, 1.0f, y_); });
    
    y_ = std::vector<float>(y);

    bench.run("naive", [&] { ssymv('L', alpha, a, x, 1.0f, y_); });
  }

  // TODO: ssbmv

  // TODO: sspmv

  {
    bench.title("strmv:U");

    auto x_ = std::vector<float>(x);

    bench.run("cblas", [&] { cblas_strmv(CblasRowMajor, CblasUpper, CblasNoTrans, CblasNonUnit, n, a.data(), n, x_.data(), 1); });
    
    x_ = std::vector<float>(x);

    bench.run("meatballs", [&] { meatballs::strmv('U', a, x_); });

    x_ = std::vector<float>(x);

    bench.run("naive", [&] { strmv('U', a, x_); });
  }

  {
    bench.title("strmv:L");

    auto x_ = std::vector<float>(x);

    bench.run("cblas", [&] { cblas_strmv(CblasRowMajor, CblasLower, CblasNoTrans, CblasNonUnit, n, a.data(), n, x_.data(), 1); });
    
    x_ = std::vector<float>(x);

    bench.run("meatballs", [&] { meatballs::strmv('L', a, x_); });

    x_ = std::vector<float>(x);

    bench.run("naive", [&] { strmv('L', a, x_); });
  }

  // TODO: stbmv

  // TODO: stpmv

  // TODO: strsv

  // TODO: stbsv

  // TODO: stpsv

  // TODO: sger

  // TODO: ssyr

  // TODO: ssyr2

  // TODO: sspr2

  return 0;
}