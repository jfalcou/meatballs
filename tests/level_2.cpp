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
  auto y = create_random_vector<float>(m);

  {
    auto ym = std::vector<float>(y);
    auto yc = std::vector<float>(y);

    meatballs::sgemv('N', alpha, a, x, beta, ym);
    cblas_sgemv(CblasColMajor, CblasNoTrans, m, n, alpha, a.data(), m, x.data(), 1, beta, yc.data(), 1);

    auto b = ym == yc;

    std::cout << "[sgemv:N]\t" << (b ? "OK" : "KO") << "\n";
  }

  {
    auto ym = std::vector<float>(y);
    auto yc = std::vector<float>(y);

    meatballs::sgemv('T', alpha, a, x, beta, ym);
    cblas_sgemv(CblasColMajor, CblasTrans, m, n, alpha, a.data(), m, x.data(), 1, beta, yc.data(), 1);

    auto b = ym == yc;

    std::cout << "[sgemv:T]\t" << (b ? "OK" : "KO") << "\n";
  }

  // TODO: sgemv:C

  // TODO: sgbmv

  {
    auto ym = std::vector<float>(y);
    auto yc = std::vector<float>(y);

    meatballs::ssymv('U', alpha, a, x, beta, ym);
    cblas_ssymv(CblasColMajor, CblasUpper, n, alpha, a.data(), n, x.data(), 1, beta, yc.data(), 1);

    auto b = ym == yc;

    std::cout << "[ssymv:U]\t" << (b ? "OK" : "KO") << "\n";
  }

  {
    auto ym = std::vector<float>(y);
    auto yc = std::vector<float>(y);

    meatballs::ssymv('L', alpha, a, x, beta, ym);
    cblas_ssymv(CblasColMajor, CblasLower, n, alpha, a.data(), n, x.data(), 1, beta, yc.data(), 1);

    auto b = ym == yc;

    std::cout << "[ssymv:L]\t" << (b ? "OK" : "KO") << "\n";
  }

  // TODO: ssbmv

  // TODO: sspmv

  {
    auto xm = std::vector<float>(x);
    auto xc = std::vector<float>(x);

    // meatballs::strmv('U', a, xm);
    strmv('U', a, xm);
    cblas_strmv(CblasRowMajor, CblasUpper, CblasNoTrans, CblasNonUnit, n, a.data(), n, xc.data(), 1);

    auto b = xm == xc;

    std::cout << "[strmv:U]\t" << (b ? "OK" : "KO") << "\n";
  }

  {
    auto xm = std::vector<float>(x);
    auto xc = std::vector<float>(x);

    // meatballs::strmv('L', a, xm);
    strmv('L', a, xm);
    cblas_strmv(CblasRowMajor, CblasLower, CblasNoTrans, CblasNonUnit, n, a.data(), n, xc.data(), 1);

    auto b = xm == xc;

    std::cout << "[strmv:L]\t" << (b ? "OK" : "KO") << "\n";
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