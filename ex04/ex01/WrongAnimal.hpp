#pragma once
#include <string>
#ifndef __WRONGANIMAL_HPP__
#define  __WRONGANIMAL_HPP__

class WrongAnimal {
    public:
        // Orthodox Canonical Form
        WrongAnimal();
        WrongAnimal(const WrongAnimal &other);
        WrongAnimal &operator=(const WrongAnimal &other);
        ~WrongAnimal(); // no virtual

        std::string getType() const;
        void makeSound() const; // no virtual
    private:
        //

    protected:
        std::string type;
};

#endif
