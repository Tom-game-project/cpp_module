#include "ScalarConverter.hpp"

int main() {
  std::string s = "-1234";
  // std::string s = "-1234.0";
  ScalarConverter::convert(s);
}
