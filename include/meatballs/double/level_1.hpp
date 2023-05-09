#ifndef MEATBALLS_DOUBLE_LEVEL_1_HPP
#define MEATBALLS_DOUBLE_LEVEL_1_HPP

#include <complex>
#include <span>

#include <meatballs/level_1.hpp>

namespace meatballs {
void drotg(double& a, double& b, double& c, double& s) { xrotg(a, b, c, s); }

void drotmg(double d1, double d2, double a, double b,
            std::span<double, 5> param) {
  xrotmg(d1, d2, a, b, param);
}

void drot(std::span<double> x, std::span<double> y, double c, double s) {
  xrot(x, y, c, s);
}

void drotm(std::span<double> x, std::span<double> y,
           std::span<double, 5> param) {
  xrotm(x, y, param);
}

void dswap(std::span<double> x, std::span<double> y) { xswap(x, y); }

void dscal(double alpha, std::span<double> x) { xscal(alpha, x); }

void dcopy(std::span<double> x, std::span<double> y) { xcopy(x, y); }

void daxpy(double alpha, std::span<double> x, std::span<double> y) {
  xaxpy(alpha, x, y);
}

double ddot(std::span<double> x, std::span<double> y) { return xdot(x, y); }

double dsdot(double alpha, std::span<double> x, std::span<double> y) {
  // TODO: xxdot?
  
  return alpha + xdot(x, y);
}

double dnrm2(std::span<double> x) { return xnrm2(x); }

double dznrm2(std::span<std::complex<double>> x) {
  // TODO: complex

  return 0.0;
}

double dasum(std::span<double> x) { return xasum(x); }

std::size_t idamax(std::span<double> x) { return ixamai(x); }
} // namespace meatballs

#endif