#pragma once
#include <string>
#ifndef __AMATERIA_HPP__
#define __AMATERIA_HPP__

class ICharacter;

class AMateria
{
    protected:
        std::string type;
    public:
        AMateria();
        AMateria(const AMateria &other);
        AMateria&operator=(const AMateria &other);

        AMateria(std::string const & type);
        virtual ~AMateria();
        std::string const & getType() const; //Returns the materia type
        virtual AMateria* clone() const = 0;
        virtual void use(ICharacter& target);
};

#endif
