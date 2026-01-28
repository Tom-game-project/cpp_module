#include "ClapTrap.hpp"
#include <iostream>
#include <ostream>

ClapTrap::ClapTrap (): name("Default"), hit_points(10), energy_points(10), attack_damage(0) {
    std::cout << "ClapTrap Default constructor called" << std::endl;
}

ClapTrap::ClapTrap (std::string name): name(name), hit_points(10), energy_points(10), attack_damage(0) {
    std::cout << "ClapTrap Constructor for " << this->name << " called" << std::endl;
}


ClapTrap::ClapTrap(const ClapTrap &other) {
    std::cout << "ClapTrap Copy constructor called" << std::endl;
    *this = other;
}

ClapTrap &ClapTrap::operator=(const ClapTrap &other) {
    std::cout << "ClapTrap Copy assignment operator called" << std::endl;
	if (this == &other) {
	} else {
		this->name = other.name;
		this->hit_points = other.hit_points;
        this->energy_points = other.energy_points;
        this->attack_damage = other.attack_damage;
	}

	return *this;
}

ClapTrap::~ClapTrap () {
    std::cout << "ClapTrap Destructor for " << this->name << " called" << std::endl;
}

void ClapTrap::attack(const std::string& target) {
    if (0 < this->energy_points && 0 < this->hit_points) {
        this->energy_points -= 1;
        std::cout << "ClapTrap " << this->name << " attacks " << target 
                  << ", causing " << this->attack_damage << " points of damage!" << std::endl;
    } else {
        std::cout << "ClapTrap " << this->name << " can't attack (no energy or hp left)!" << std::endl;
    }
}

void ClapTrap::takeDamage(unsigned int amount) {
    if (this->hit_points == 0) {
        std::cout << "ClapTrap " << this->name << " is already dead!" << std::endl;
        return;
    }

    // オーバーフロー対策（HPより大きいダメージが来たら0にする）
    if (this->hit_points <= amount) {
        this->hit_points = 0;
    } else {
        this->hit_points -= amount;
    }

    std::cout << "ClapTrap " << this->name << " takes " << amount
              << " damage! (HP: " << this->hit_points << ")" << std::endl;
}

void ClapTrap::beRepaired(unsigned int amount) {
    if (0 < this->energy_points && 0 < this->hit_points) {
        this->energy_points -= 1;
        this->hit_points += amount;
        
        std::cout << "ClapTrap " << this->name << " repairs itself, getting " 
                  << amount << " hit points back! (HP: " << this->hit_points << ")" << std::endl;
    } else {
        std::cout << "ClapTrap " << this->name << " can't be repaired (no energy or hp left)!" << std::endl;
    }
}
