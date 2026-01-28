#pragma once
#include "WrongAnimal.hpp"
#ifndef __WrongCAT_HPP__
#define __WrongCAT_HPP__

class WrongCat: public WrongAnimal {
    public:
        WrongCat();
        WrongCat(const WrongCat &other);
        WrongCat&operator=(const WrongCat &other);
        ~WrongCat();
        void makeSound();
};

#endif
