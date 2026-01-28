#include "ScavTrap.hpp"
#include "ClapTrap.hpp"
#include <iostream>
#include <string>

ScavTrap::ScavTrap(): ClapTrap() {
    this->hit_points = 100;
    this->energy_points = 50;
    this->attack_damage = 20;
    std::cout << "ScavTrap Default constructor called" << std::endl;
}

ScavTrap::ScavTrap(std::string name): ClapTrap(name) {
    this->hit_points = 100;
    this->energy_points = 50;
    this->attack_damage = 20;
    std::cout << "ScavTrap Constructor for " << this->name << " called" << std::endl;
}

ScavTrap::ScavTrap(const ScavTrap &src) : ClapTrap(src) {
    std::cout << "ScavTrap copy constructor called" << std::endl;
}

ScavTrap &ScavTrap::operator=(const ScavTrap &rhs) {
    if (this!= &rhs) {
        ClapTrap::operator=(rhs);
    }
    std::cout << "ScavTrap assignment operator called" << std::endl;
    return *this;
}

ScavTrap::~ScavTrap () {
    std::cout << "ScavTrap Destructor for " << this->name << " called" << std::endl;
}

void ScavTrap::attack(const std::string &target) {
    if (0 < this->energy_points && 0 < this->hit_points) {
        this->energy_points -= 1;
        std::cout << "ScavTrap " << this->name << " attacks " << target 
                  << " aggressively, dealing " << this->attack_damage 
                  << " points of damage!" << std::endl;
    } else {
        std::cout << "ScavTrap " << this->name << " requires repair." << std::endl;
    }
}

void ScavTrap::guardGate() {
    std::cout << "ScavTrap " << this->name << " guard gate" << std::endl;
}


