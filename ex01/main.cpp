#include "Serializer.hpp"
#include "Data.hpp"
#include <cassert>
#include <stdint.h>
#include <iostream>

int main () {
  Data data;
  data.value = "hello";

  std::cout << "original addr: " << &data << std::endl;

  Data *p;
  uintptr_t ptr = Serializer::serialize(&data);
  std::cout << "ptr :" << ptr << std::endl;

  p = Serializer::deserialize(ptr);
  assert(&data == p); // 元のアドレスと等しいかどうか

  std::cout << "data->value :" << p->value << std::endl;
  return 0;
}
