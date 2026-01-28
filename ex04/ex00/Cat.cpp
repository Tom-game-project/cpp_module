#include "Cat.hpp"
#include "Animal.hpp"
#include <iostream>

Cat::Cat(): Animal() {
    this->type = "Cat";
    std::cout << "Cat constructor called" << std::endl;
}

Cat::Cat(const Cat &other): Animal() {
    *this = other;
}

Cat &Cat::operator=(const Cat &other) {
    if (this != &other) {
        Cat::operator=(other);
    }    
    return *this;
}

Cat::~Cat() {
    std::cout << "Cat destructor called" << std::endl;
}

void Cat::makeSound() const {
    std::cout << "nya- nya-" << std::endl;
}
