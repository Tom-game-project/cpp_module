#include "Character.hpp"
#include "ICharacter.hpp"
#include <cstddef>
#include <string>

Character::Character(std::string const &name): _name(name) {
    for (int i = 0; i < INVENTORY_LENGTH; i++) {
        this->_inventory[i] = NULL;
    }
}

Character::Character(): _name("default") {
    for (int i = 0; i < INVENTORY_LENGTH; i++) {
        this->_inventory[i] = NULL;
    }
}

Character::Character(Character const & other): _name(other._name) {
    for (int i = 0; i < INVENTORY_LENGTH; i++) {
        if (other._inventory[i])
            this->_inventory[i] = other._inventory[i]->clone(); // 複製を作成
        else
            this->_inventory[i] = NULL;
    }
}

void Character::assign(Character & other) {
    for (int i = 0; i < INVENTORY_LENGTH; i++) {
        if (this->_inventory[i] && other._inventory[i]) {
            if (this->_inventory[i]->getType() == other._inventory[i]->getType()) {
                *this->_inventory[i] = *other._inventory[i];
            } else {
                delete this->_inventory[i];
                this->_inventory[i] = other._inventory[i]->clone();
            }
        } else {
            if (this->_inventory[i] != NULL) {
                delete this->_inventory[i];
            }
            this->_inventory[i] = (other._inventory[i] ?
                    other._inventory[i]->clone():
                    NULL);
        }
    }
}

// 代入演算子
Character & Character::operator=(Character & other) {
    if (this!= &other) {
        this->assign(other);
    }
    return *this;
}

Character::~Character() {
    for (int i = 0; i < INVENTORY_LENGTH; i++) {
        if (this->_inventory[i])
            delete this->_inventory[i];
    }
}

std::string const & Character::getName() const {
    return this->_name;
}

void Character::equip(AMateria* m) {
    if (!m) 
        return;

    for (int i = 0; i < INVENTORY_LENGTH; i++) {
        if (this->_inventory[i] == NULL) {
            this->_inventory[i] = m;
            return;
        }
    }
}

// deleteはしない
void Character::unequip(int idx) {
    if (idx >= 0 && idx < INVENTORY_LENGTH) {
        this->_inventory[idx] = NULL; // ポインタを外すだけ
    }
}

void Character::use(int idx, ICharacter& target) {
    if (idx >= 0 && idx < INVENTORY_LENGTH && this->_inventory[idx]) {
        this->_inventory[idx]->use(target);
    }
}
