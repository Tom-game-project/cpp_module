#include "ScalarConverter.hpp"
#include <cstddef>
#include <iostream>
#include <ostream>

// template <typename T, size_t N>
// size_t array_size(T (&)[N]) {
//     return N;
// }

int main(int argc, char* args[]) {
  if (argc == 2) {
    std::string s(args[1]);
    ScalarConverter::convert(s);
  } else {
    std::cout << "incorrect arg size" << std::endl;
  }

  // std::string test_cases[] = {
  //   // char
  //   "a",
  //   "z",
  //   "A",
  //   "Z",
  //   " ",
  //   "~",
  // 
  //   // int 
  //   "0",
  //   "42",
  //   "+42",
  //   "-42",
  //   "2147483647",
  //   "-2147483648",
  // 
  //   // float 
  //   "inff",
  //   "+inff",
  //   "-inff",
  //   "nanf",
  //   "+nanf",
  //   "-nanf",
  //   "42.0f",
  //   "+42.0f",
  //   "-42.0f",
  //   "1.8e2f",
  //   "+1.8e2f",
  //   "-1.8e2f",
  //   "1.8e+2f",
  //   "+1.8e+2f",
  //   "-1.8e+2f",
  //   "1.8e-2f",
  //   "+1.8e-2f",
  //   "-1.8e-2f",
  // 
  //   // double
  //   "inf",
  //   "+inf",
  //   "-inf",
  //   "nan",
  //   "+nan",
  //   "-nan",
  //   "42.0",
  //   "+42.0",
  //   "-42.0",
  //   "1.8e2",
  //   "+1.8e2",
  //   "-1.8e2",
  //   "1.8e+2",
  //   "+1.8e+2",
  //   "-1.8e+2",
  //   "1.8e-2",
  //   "+1.8e-2",
  //   "-1.8e-2",
  // 
  //   // impossible
  //   "hello", 
  //   "+hello",
  //   "-diff",
  //   "?123",
  //   "123hello",
  // 
  //   // 
  //   // int overflow
  //   "2147483648",   // int最大値 + 1
  //   "-2147483649",  // int最小値 - 1
  //   "4294967296",   // 符号なしint(unsigned int)の最大値すら超える値
  // 
  //   // float overflow
  //   "3.5e+38",      // floatの正の限界を少し超える
  //   "-3.5e+38",     // floatの負の限界を少し超える
  // 
  //   // double overflow
  //   "2.0e+308",
  //   "-2.0e+308",
  // };
  // 
  // for (std::size_t i = 0; i < array_size(test_cases); i++) {
  //   std::cout << "test case (" << i << "): \"" << test_cases[i] << "\"" << std::endl;
  //   ScalarConverter::convert(test_cases[i]);
  // }
}
