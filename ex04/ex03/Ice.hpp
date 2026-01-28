#pragma once
#include "AMateria.hpp"
#ifndef __ICE_HPP__
#define __ICE_HPP__

class Ice: public AMateria
{
    public:
        // Orthodox Canonical Form
        Ice();
        Ice(const Ice &other);
        Ice&operator=(const Ice &other);
        ~Ice();
        std::string const & getType() const; //Returns the materia type
        virtual AMateria* clone() const;
        virtual void use(ICharacter& target);
};

#endif
