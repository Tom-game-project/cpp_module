#include <iostream>

#include "BitcoinExchange.hpp"

int main(int argc, char *argv[]) {
  if (argc == 2) {
    return func(argv[1]);
  } else {
    std::cout << "Error: could not open file." << std::endl;
    return 1;
  }
}
