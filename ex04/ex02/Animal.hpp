#pragma once
#include <string>
#ifndef __ANIMAL_HPP__
#define __ANIMAL_HPP__

class Animal {
    public:
        // Orthodox Canonical Form
        Animal();
        Animal(const Animal &other);
        Animal &operator=(const Animal &other);
        virtual ~Animal();

        std::string getType() const;
        virtual void makeSound() const = 0;
    private:
        //

    protected:
        std::string type;
};

#endif
