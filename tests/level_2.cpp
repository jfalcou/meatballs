#include <openblas/cblas.h>

#include <meatballs/single/level_2.hpp>

#include <utilities.hpp>

#include <ssymv.hpp>

int main() {
  std::srand(std::time(nullptr));

  auto m = 256;
  auto n = 256;

  auto a = create_random_matrix<float>(m, n);
  auto alpha = create_random_scalar<float>();
  auto x = create_random_vector<float>(n);
  auto beta = create_random_scalar<float>();
  auto y = create_random_vector<float>(n);

  {
    auto ym = std::vector<float>(y);
    auto yc = std::vector<float>(y);

    meatballs::sgemv('N', alpha, a, x, beta, ym);
    cblas_sgemv(CblasRowMajor, CblasNoTrans, m, n, alpha, a.data(), n, x.data(), 1, beta, yc.data(), 1);

    auto b = ym == yc;

    std::cout << "[sgemv:N]\t" << (b ? "OK" : "KO") << "\n";
  }

  {
    auto ym = std::vector<float>(y);
    auto yc = std::vector<float>(y);

    meatballs::sgemv('T', alpha, a, x, beta, ym);
    cblas_sgemv(CblasRowMajor, CblasTrans, m, n, alpha, a.data(), n, x.data(), 1, beta, yc.data(), 1);

    auto b = ym == yc;

    std::cout << "[sgemv:T]\t" << (b ? "OK" : "KO") << "\n";
  }

  // TODO: sgbmv

  // {
  //   auto ym = std::vector<float>(y);
  //   auto yc = std::vector<float>(y);

  //   meatballs::ssymv('U', alpha, a, x, beta, ym);
  //   cblas_ssymv(CblasRowMajor, CblasUpper, n, alpha, a.data(), n, x.data(), 1, beta, yc.data(), 1);

  //   auto b = ym == yc;

  //   std::cout << "[ssymv  ]\t" << (b ? "OK" : "KO") << "\n";
  // }

  {
    auto ym = std::vector<float>(y);
    auto yc = std::vector<float>(y);

    ssymv(alpha, a, x, beta, ym);
    cblas_ssymv(CblasColMajor, CblasUpper, n, alpha, a.data(), n, x.data(), 1, beta, yc.data(), 1);

    auto b = ym == yc;

    std::cout << "[ssymv  ]\t" << (b ? "OK" : "KO") << "\n";
  }

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