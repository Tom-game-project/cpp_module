#include "Bureaucrat.hpp"
#include <cassert>
#include <cstring>
#include <exception>
#include <iostream>

int main () {
  Bureaucrat b0("Hello", 150);

  try {
    b0.decrement();
  } catch (std::exception& e) {
    // std::cout << e.what() << std::endl;
    assert(std::strcmp(GradeTooLowExceptionMsg, e.what()) == 0);
  }

  Bureaucrat b1("World", 1);
  
  try {
    b1.increment();
  } catch (std::exception& e) {
    // std::cout << e.what() << std::endl;
    assert(std::strcmp(GradeTooHighExceptionMsg, e.what()) == 0);
  }

  Bureaucrat* b2 = new Bureaucrat("A", 150);

  b2->increment();
  assert(b2->getGrade() == 149);

  Bureaucrat* b3 = new Bureaucrat("B", 1);

  b3->decrement();
  assert(b3->getGrade() == 2);

  std::cout << b0 << std::endl;
  std::cout << b1 << std::endl;
  std::cout << *b2 << std::endl;
  std::cout << *b3 << std::endl;
}
