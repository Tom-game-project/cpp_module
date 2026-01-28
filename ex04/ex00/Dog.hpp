#pragma once
#include "Animal.hpp"
#ifndef __DOG_HPP__
#define __DOG_HPP__

class Dog: public Animal {
    public:
        Dog();
        Dog(const Dog &other);
        Dog&operator=(const Dog &other);
        ~Dog();
        void makeSound() const;
};

#endif
