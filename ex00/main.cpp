#include "whatever.hpp"
#include <iostream>
#include <string>

struct Data {
  std::string value;
};

struct DataA {
  int value;

  bool operator<(DataA& a) const {
    return this->value < a.value;
  }

  bool operator>(DataA& a) const {
    return this->value > a.value;
  }
};

int main() {
  int a = 1;
  int b = 2;

  Data data_a;
  data_a.value = "A";
  Data data_b;
  data_b.value = "B";

  Whatever::swap<int>(a, b);
  std::cout << "a: " << a << std::endl;
  std::cout << "b: " << b << std::endl;

  Whatever::swap<Data>(data_a, data_b);

  int a_arr[] = {1,2,3};
  int b_arr[] = {3, 2,1};

  Whatever::swap(a_arr, b_arr);

  for (std::size_t i = 0; i < 3; i++) {
    std::cout << "a_arr[" << i << "] :" << a_arr[i] << std::endl;
  }

  std::cout << "data_a: " << data_a.value << std::endl;
  std::cout << "data_b: " << data_b.value << std::endl;

  int min_one = Whatever::min(a, b);
  int max_one = Whatever::max(a, b);

  std::cout << "min one: " << min_one << std::endl;
  std::cout << "max one: " << max_one << std::endl;

  DataA aa;
  aa.value = 0;
  DataA bb;
  bb.value = 1;

  DataA max_data = Whatever::min(aa, bb);
  DataA min_data = Whatever::max(aa, bb);

  std::cout << "min one: " << max_data.value << std::endl;
  std::cout << "max one: " << min_data.value << std::endl;

  return 0;
}

// int main( void ) {
//   int a = 2;
//   int b = 3;
//   Whatever::swap( a, b );
//   std::cout << "a = " << a << ", b = " << b << std::endl;
//   std::cout << "min(a, b) = " << Whatever::min( a, b ) << std::endl;
//   std::cout << "max(a, b) = " << Whatever::max( a, b ) << std::endl;
//   std::string c = "chaine1";
//   std::string d = "chaine2";
//   Whatever::swap(c, d);
//   std::cout << "c = " << c << ", d = " << d << std::endl;
//   std::cout << "min(c, d) = " << Whatever::min( c, d ) << std::endl;
//   std::cout << "max(c, d) = " << Whatever::max( c, d ) << std::endl;
//   return 0;
// }
