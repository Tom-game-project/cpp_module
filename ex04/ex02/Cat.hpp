#pragma once
#include "Animal.hpp"
#include "Brain.hpp"
#ifndef __CAT_HPP__
#define __CAT_HPP__

class Cat: public Animal {
    public:
        Cat();
        Cat(const Cat &other);
        Cat&operator=(const Cat &other);
        ~Cat();

        std::string getType();
        void makeSound() const;
    private:
        Brain *_brain;
};

#endif
