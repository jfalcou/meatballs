#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <ctime>
#include <iostream>
#include <vector>
#include <span>

#define MAX_VALUE 8

// SCALAR

template <typename T> T create_random_scalar() {
  return std::rand() % (2 * MAX_VALUE) - MAX_VALUE;
}

// VECTOR

template <typename T> std::vector<T> create_vector(std::size_t n) {
  auto x = std::vector<T>();

  for (auto i = 0; i < n; i++)
    x.push_back(i);

  return x;
}

template <typename T> std::vector<T> create_zero_vector(std::size_t n) {
  auto x = std::vector<T>();

  for (auto i = 0; i < n; i++)
    x.push_back(T(0));

  return x;
}

template <typename T> std::vector<T> create_random_vector(std::size_t n) {
  auto x = std::vector<T>();

  for (auto i = 0; i < n; i++)
    x.push_back(create_random_scalar<T>());

  return x;
}

template <typename T> void print_vector(std::size_t n, std::vector<T> x) {
  for (auto i = 0; i < n; i++)
    std::cout << x[i] << ' ';

  std::cout << '\n';
}

// MATRIX

template <typename T>
std::span<T> get_column(std::size_t m, std::span<T> a, std::size_t j) {
  return std::span<T>(&a[j * m], m);
}

// MATRIX

template <typename T> std::vector<T> create_matrix(std::size_t m, std::size_t n) {
  auto a = std::vector<T>();

  for (auto i = 0; i < m * n; i++)
    a.push_back(i);

  return a;
}

template <typename T>
std::vector<T> create_random_matrix(std::size_t m, std::size_t n) {
  auto a = std::vector<T>();

  for (auto i = 0; i < m * n; i++)
    a.push_back(create_random_scalar<T>());

  return a;
}

template <typename T>
void print_matrix(std::size_t m, std::size_t n, std::vector<T> a) {
  for (auto i = 0; i < m; i++) {
    for (auto j = 0; j < n; j++)
      std::cout << a[i + j * m] << ' ';

    std::cout << '\n';
  }
}

#endif