#include "PmergeMe.hpp"
#include <cstddef>
#include <iostream>
#include <vector>

int main () {
  std::vector<int> a; // = {3, 5, 9, 7, 4};
  a.push_back(3);
  a.push_back(5);
  a.push_back(9);
  a.push_back(7);
  a.push_back(4);
  std::vector<int> sorted = ford_johnson_sort(a);

  for (std::size_t i = 0; i < sorted.size(); i++) {
    std::cout << sorted[i] << std::endl;
  }
  return 0;
}
