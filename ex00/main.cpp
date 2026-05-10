#include <iostream>

#include "BitcoinExchange.hpp"

// data.csvの用意
// ```
// wget https://cdn.intra.42.fr/document/document/46100/cpp_09.tgz && tar -xzvf *.tgz && mv cpp_09/data.csv . && rm cpp_09.tgz && rmdir cpp_09
// ```

int main(int argc, char *argv[]) {
  if (argc == 2) {
    return func(argv[1]);
  } else {
    std::cout << "Error: could not open file." << std::endl;
    return 1;
  }
}
