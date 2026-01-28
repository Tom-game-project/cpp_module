#pragma once
#include "ICharacter.hpp"
#include "AMateria.hpp"
#ifndef __CHARACTER_HPP__
#define __CHARACTER_HPP__

#define INVENTORY_LENGTH 4

class Character: public ICharacter{
    private:
        std::string _name;
        AMateria*   _inventory[INVENTORY_LENGTH]; // マテリアを格納する固定長配列
        void assign(Character &other);
    public:
        Character();
        Character(const Character &other);
        Character&operator=(Character &other);

        Character(std::string const & name);

        virtual ~Character();
        virtual std::string const & getName() const;
        virtual void equip(AMateria* m);
        virtual void unequip(int idx);
        virtual void use(int idx, ICharacter& target);
};

#endif
