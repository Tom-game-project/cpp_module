#pragma once
#include "AMateria.hpp"
#ifndef __CURE_HPP__
#define __CURE_HPP__

class Cure: public AMateria
{
    public:
        // Orthodox Canonical Form
        Cure();
        Cure(const Cure &other);
        Cure&operator=(const Cure &other);
        ~Cure();
        std::string const & getType() const; //Returns the materia type
        virtual AMateria* clone() const;
        virtual void use(ICharacter& target);
};


#endif
