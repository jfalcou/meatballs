#include <nanobench.h>

#include <openblas/cblas.h>

#include <meatballs/single/level_1.hpp>

#include <utilities.hpp>

int main() {
  std::srand(std::time(nullptr));
  
  auto n = 4096;

  auto a = create_random_scalar<float>();
  auto b = create_random_scalar<float>();
  auto alpha = create_random_scalar<float>();
  auto x = create_random_vector<float>(n);
  auto y = create_random_vector<float>(n);

  auto bench = ankerl::nanobench::Bench().relative(true);

  // {
  //   bench.title("srotg");

  //   auto a_ = a;
  //   auto b_ = b;
  //   auto c_ = 0.0f;
  //   auto s_ = 0.0f;

  //   bench.run("cblas", [&] { cblas_srotg(&a_, &b_, &c_, &s_); });
    
  //   bench.run("meatballs", [&] { meatballs::srotg(a_, b_, c_, s_); });
  // }

  // TODO: srotmg

  // TODO: srot

  // TODO: srotm

  {
    bench.title("sswap");

    auto x_ = std::vector<float>(x);
    auto y_ = std::vector<float>(y);

    bench.run("cblas", [&] { cblas_sswap(n, x_.data(), 1, y_.data(), 1); });
    
    x_ = std::vector<float>(x);
    y_ = std::vector<float>(y);

    bench.run("meatballs", [&] { meatballs::sswap(x_, y_); });
  }

  {
    bench.title("sscal");

    auto x_ = std::vector<float>(x);

    bench.run("cblas", [&] { cblas_sscal(n, alpha, x_.data(), 1); });

    x_ = std::vector<float>(x);

    bench.run("meatballs", [&] { meatballs::sscal(alpha, x_); });
  }

  {
    bench.title("scopy");

    auto y_ = std::vector<float>(y);

    bench.run("cblas", [&] { cblas_scopy(n, x.data(), 1, y_.data(), 1); });
    
    y_ = std::vector<float>(y);

    bench.run("meatballs", [&] { meatballs::scopy(x, y_); });
  }

  {
    bench.title("saxpy");

    auto y_ = std::vector<float>(y);

    bench.run("cblas",
              [&] { cblas_saxpy(n, alpha, x.data(), 1, y_.data(), 1); });
    
    y_ = std::vector<float>(y);

    bench.run("meatballs", [&] { meatballs::saxpy(alpha, x, y_); });
  }

  {
    bench.title("sdot");

    bench.run("cblas", [&] { cblas_sdot(n, x.data(), 1, y.data(), 1); });

    bench.run("meatballs", [&] { meatballs::sdot(x, y); });
  }

  {
    bench.title("sdsdot");

    bench.run("cblas",
              [&] { cblas_sdsdot(n, alpha, x.data(), 1, y.data(), 1); });

    bench.run("meatballs", [&] { meatballs::sdsdot(alpha, x, y); });
  }

  {
    bench.title("snrm2");

    bench.run("cblas", [&] { cblas_snrm2(n, x.data(), 1); });

    bench.run("meatballs", [&] { meatballs::snrm2(x); });
  }

  // TODO: scnrm2

  {
    bench.title("sasum");

    bench.run("cblas", [&] { cblas_sasum(n, x.data(), 1); });

    bench.run("meatballs", [&] { meatballs::sasum(x); });
  }

  {
    bench.title("isamax");

    bench.run("cblas", [&] { cblas_isamax(n, x.data(), 1); });

    bench.run("meatballs", [&] { meatballs::isamax(x); });
  }

  return 0;
}