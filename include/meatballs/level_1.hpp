#ifndef MEATBALLS_LEVEL_1_HPP
#define MEATBALLS_LEVEL_1_HPP

#include <span>

#include <eve/module/algo.hpp>

// INFO: no dimension parameter (n)
// INFO: no increment parameters (incx, incy)

namespace meatballs {
// SUBROUTINES

template <typename T> void xrotg(T& a, T& b, T& c, T& s) {
  auto abs_a = eve::abs(a);
  auto abs_b = eve::abs(b);

  auto sigma = abs_a > abs_b ? eve::sign(a) : eve::sign(b);

  auto r = sigma * eve::sqrt(a * a + b * b);

  c = r == 0 ? 1 : a / r;
  s = r == 0 ? 0 : b / r;

  auto z = 1;

  if (abs_a > abs_b)
    z = s;
  else if (c != 0)
    z = 1 / c;

  a = r;
  b = z;
};

template <typename T>
void xrotmg(T d1, T d2, T a, T b, std::span<T, 5> param){
    // TODO: scalar
};

template <typename T>
void xrot(std::span<T> x, std::span<T> y, T c, T s){
    // TODO: scalar
};

template <typename T>
void xrotm(std::span<T> x, std::span<T> y, std::span<T, 5> param){
    // TODO: scalar
};

template <typename T> void xswap(std::span<T> x, std::span<T> y) {
  eve::algo::swap_ranges(x, y);
};

template <typename T> void xscal(T alpha, std::span<T> x) {
  eve::algo::transform_inplace(x, [alpha](auto x) { return alpha * x; });
};

template <typename T> void xcopy(std::span<T> x, std::span<T> y) {
  eve::algo::copy(x, y);
};

template <typename T> void xaxpy(T alpha, std::span<T> x, std::span<T> y) {
  eve::algo::transform_to(eve::views::zip(x, y), y, [alpha](auto x_y) {
    auto [x, y] = x_y;

    return eve::fma(alpha, x, y);
  });
};

// FUNCTIONS

template <typename T> T xdot(std::span<T> x, std::span<T> y) {
  return eve::algo::transform_reduce(
      eve::views::zip(x, y),
      [](auto x_y) {
        auto [x, y] = x_y;

        return x * y;
      },
      T(0));
};

template <typename T>
T xdotu(std::span<T> x, std::span<T> y){
    // TODO: complex
};

template <typename T>
T xdotc(std::span<T> x, std::span<T> y){
    // TODO: complex
};

template <typename T>
T xxdot(std::span<T> x, std::span<T> y){
    // TODO: sdsdot and dsdot?
};

template <typename T> T xnrm2(std::span<T> x) {
  return eve::sqrt(eve::algo::transform_reduce(
      x, [](auto x) { return x * x; }, T(0)));
};

template <typename T> T xasum(std::span<T> x) {
  return eve::algo::transform_reduce(
      x, [](auto x) { return eve::abs(x); }, T(0));
};

template <typename T> std::size_t ixamai(std::span<T> x) {
  // INFO: indices are reversed to compute the first element

  constexpr auto s = eve::wide<T>::size();

  auto n = x.size();
  
  auto is = eve::wide<int>([](auto k, auto) { return s - k - 1; });

  // local indices and values
  auto li = eve::wide<int>(0);
  auto lv = eve::wide<T>(T(0));

  // global indices and values
  auto gi = eve::wide<int>(0);
  auto gv = eve::wide<T>(T(0));

  for (auto i = 0; i < n; i += s) {
    // li = is + (n - (i + s - 1) - 1);
    li = is + n - i - s;
    lv = eve::abs(eve::wide<T>(&x[i]));

    gi = eve::if_else(gv >= lv, gi, li);
    gv = eve::max(gv, lv);
  }

  // eve::algo::for_each(..., [](auto iterator, auto ignore) {
  //   // TODO
  // });

  gi = eve::if_else(gv == eve::reduce(gv, eve::max), gi, eve::zero);

  return n - eve::reduce(gi, eve::max) - 1;
};
} // namespace meatballs

#endif