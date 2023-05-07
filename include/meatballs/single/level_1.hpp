#ifndef MEATBALLS_SINGLE_LEVEL_1_HPP
#define MEATBALLS_SINGLE_LEVEL_1_HPP

#include <complex>
#include <span>

#include <meatballs/level_1.hpp>

namespace meatballs {
void srotg(float& a, float& b, float& c, float& s) { xrotg(a, b, c, s); }

void srotmg(float d1, float d2, float a, float b, std::span<float, 5> param) {
  xrotmg(d1, d2, a, b, param);
}

void srot(std::span<float> x, std::span<float> y, float c, float s) {
  xrot(x, y, c, s);
}

void srotm(std::span<float> x, std::span<float> y, std::span<float, 5> param) {
  xrotm(x, y, param);
}

void sswap(std::span<float> x, std::span<float> y) { xswap(x, y); }

void sscal(float alpha, std::span<float> x) { xscal(alpha, x); }

void scopy(std::span<float> x, std::span<float> y) { xcopy(x, y); }

void saxpy(float alpha, std::span<float> x, std::span<float> y) {
  xaxpy(alpha, x, y);
}

float sdot(std::span<float> x, std::span<float> y) { return xdot(x, y); }

float sdsdot(float alpha, std::span<float> x, std::span<float> y) {
  return alpha + xdot(x, y); // TODO: xxdot?
}

float snrm2(std::span<float> x) { return xnrm2(x); }

float scnrm2(std::span<std::complex<float>> x) {
  return 0.0f; // TODO: complex
}

float sasum(std::span<float> x) { return xasum(x); }

std::size_t isamax(std::span<float> x) { return ixamai(x); }
} // namespace meatballs

#endif