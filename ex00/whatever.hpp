#ifndef WHATEVER_HPP
#define WHATEVER_HPP
#include <cstddef>

template<typename T>
static void swap(T& a, T& b) {
  T tmp;
  tmp = a;
  a = b;
  b = tmp;
}

template<typename T, std::size_t N>
static void swap(T (&a)[N], T(& b)[N]) {
  for (std::size_t i = 0; i < N; i++) {
    swap(a[i], b[i]);
  }
}

template<typename T>
static T min(T& a, T& b) {
  return a < b ? a : b;
}

template<typename T>
static T max(T& a, T& b) {
  return b < a ? a : b;
}

#endif
