#include "PmergeMe.hpp"
#include <cstddef>
#include <deque>
#include <iostream>
#include <string>
#include <cstdlib>
#include <climits>
#include <cerrno>
#include <vector>
#include <ctime>

int parse_positive_integer(const std::string& str) {
  if (str.empty()) {
    return -1;
  }

  size_t start = 0;
  // 先頭の '+' は許容する
  if (str[0] == '+') {
    start = 1;
    if (str.length() == 1) return -1;
  }

  for (size_t i = start; i < str.length(); ++i) {
    if (str[i] < '0' || str[i] > '9') {
      return -1;
    }
  }

  errno = 0; 
  long val = std::strtol(str.c_str(), NULL, 10);

  if (errno == ERANGE || val > INT_MAX) {
    return -1;
  }

  return static_cast<int>(val);
}

// 実験手順
// bash -c './PmergeMe $(python3 a.py)'

int main(int argc, char** argv) {
  // vector
  std::vector<int> numbers_vector;
  for (int i = 1; i < argc; ++i) {
    int num = parse_positive_integer(argv[i]);
    
    if (num == -1) {
      std::cerr << "Error" << std::endl;
      return 1;
    }
    numbers_vector.push_back(num);
  }

  // deque
  std::deque<int> numbers_deque;
  for (int i = 1; i < argc; ++i) {
    int num = parse_positive_integer(argv[i]);
    
    if (num == -1) {
      std::cerr << "Error" << std::endl;
      return 1;
    }
    numbers_deque.push_back(num);
  }

  std::clock_t vector_start_time = std::clock();
  std::vector<int> sorted_numbers_vector = ford_johnson_sort(numbers_vector);
  std::clock_t vector_end_time = std::clock();

  std::clock_t deque_start_time = std::clock();
  std::deque<int> sorted_numbers_deque = ford_johnson_sort(numbers_deque);
  std::clock_t deque_end_time = std::clock();

  // 差分を計算し、CLOCKS_PER_SEC で割って秒にし、1000000 を掛けてマイクロ秒にする
  double vector_elapsed_time_us = static_cast<double>(vector_end_time - vector_start_time) / CLOCKS_PER_SEC * 1000000.0;
  double deque_elapsed_time_us = static_cast<double>(deque_end_time - deque_start_time) / CLOCKS_PER_SEC * 1000000.0;

  std::cout << "Before: ";
  for (std::size_t i = 0; i < numbers_vector.size(); i++) {
    std::cout << sorted_numbers_vector[i] << " ";
  }
  std::cout << std::endl;
  std::cout << "After:  ";
  for (std::size_t i = 0; i < sorted_numbers_vector.size(); i++) {
    std::cout << sorted_numbers_vector[i] << " ";
  }
  std::cout << std::endl;

  std::cout << "Time to process a range of " << numbers_vector.size() <<" elements with std::vector : " << vector_elapsed_time_us << " us\n";
  std::cout << "Time to process a range of " << numbers_deque.size() <<" elements with std::deque : " << deque_elapsed_time_us << " us"
    << std::endl;

  return 0;
}

