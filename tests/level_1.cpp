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
  
  {
    auto am = a;
    auto bm = b;
    auto cm = 0.0f;
    auto sm = 0.0f;
    auto ac = a;
    auto bc = b;
    auto cc = 0.0f;
    auto sc = 0.0f;

    meatballs::srotg(am, bm, cm, sm);
    cblas_srotg(&ac, &bc, &cc, &sc); 

    auto b = am == ac && bm == bc && cm == cc && sm == sc;

    std::cout << "[srotg ]\t" << (b ? "OK" : "KO") << "\n";

    // std::cout << am << ' ' << bm << ' ' << cm << ' ' << sm << std::endl;
    // std::cout << ac << ' ' << bc << ' ' << cc << ' ' << sc << std::endl;
  }

  // TODO: srotmg

  // TODO: srot

  // TODO: srotm

  {
    auto xm = std::vector<float>(x);
    auto ym = std::vector<float>(y);

    meatballs::sswap(xm, ym); 

    auto b = xm == y && ym == x;

    std::cout << "[sswap ]\t" << (b ? "OK" : "KO") << "\n";
  }

  {
    auto xm = std::vector<float>(x);
    auto xc = std::vector<float>(x);

    meatballs::sscal(alpha, xm); 
    cblas_sscal(n, alpha, xc.data(), 1);

    auto b = xm == xc;

    std::cout << "[sscal ]\t" << (b ? "OK" : "KO") << "\n";
  }

  {
    auto ym = std::vector<float>(y);

    meatballs::scopy(x, ym); 

    auto b = ym == x;

    std::cout << "[scopy ]\t" << (b ? "OK" : "KO") << "\n";
  }

  {
    auto ym = std::vector<float>(y);
    auto yc = std::vector<float>(y);

    meatballs::saxpy(alpha, x, ym); 
    cblas_saxpy(n, alpha, x.data(), 1, yc.data(), 1); 

    auto b = ym == yc;

    std::cout << "[saxpy ]\t" << (b ? "OK" : "KO") << "\n";
  }

  {
    auto rm = meatballs::sdot(x, y); 
    auto rc = cblas_sdot(n, x.data(), 1, y.data(), 1); 

    auto b = rm == rc;

    std::cout << "[sdot  ]\t" << (b ? "OK" : "KO") << "\n";
  }
  
  {
    auto rm = meatballs::sdsdot(alpha, x, y); 
    auto rc = cblas_sdsdot(n, alpha, x.data(), 1, y.data(), 1); 

    auto b = rm == rc;

    std::cout << "[sdsdot]\t" << (b ? "OK" : "KO") << "\n";
  }
  
  {
    auto rm = meatballs::snrm2(x); 
    auto rc = cblas_snrm2(n, x.data(), 1); 

    auto b = rm == rc;

    std::cout << "[snrm2 ]\t" << (b ? "OK" : "KO") << "\n";
  }
  
  // TODO: scnrm2

  {
    auto rm = meatballs::sasum(x); 
    auto rc = cblas_sasum(n, x.data(), 1); 

    auto b = rm == rc;

    std::cout << "[sasum ]\t" << (b ? "OK" : "KO") << "\n";
  }

  {
    auto rm = meatballs::isamax(x); 
    auto rc = cblas_isamax(n, x.data(), 1);

    auto b = rm == rc;

    std::cout << "[isamax]\t" << (b ? "OK" : "KO") << "\n";
  }

  return 0;
}