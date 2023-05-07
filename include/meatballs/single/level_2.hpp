#ifndef MEATBALLS_SINGLE_LEVEL_2_HPP
#define MEATBALLS_SINGLE_LEVEL_2_HPP

#include <span>

#include <meatballs/level_2.hpp>

namespace meatballs {
void sgemv(char trans, float alpha, std::span<float> a, std::span<float> x,
           float beta, std::span<float> y) {
  xgemv(trans, alpha, a, x, beta, y);
}

// TODO: sgbmv

void ssymv(char uplo, float alpha, std::span<float> a, std::span<float> x, float beta,
           std::span<float> y) {
  xsymv(uplo, alpha, a, x, beta, y);
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
} // TODO: namespace meatballs

#endif