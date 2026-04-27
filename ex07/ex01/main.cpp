#include "iter.hpp"
#include <iostream>

void func(int n) {
  std::cout << "number " << n << std::endl;
}

int main() {
  int arr[] = {
    1, 2, 3
  };
  iter(arr, 3, func);
}
