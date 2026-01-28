#include "ClapTrap.hpp"
#include "FragTrap.hpp"
#include <iostream>
#include <string>

FragTrap::FragTrap(): ClapTrap() {
    this->hit_points = 100;
    this->energy_points = 100;
    this->attack_damage = 30;
    std::cout << "FragTrap Default constructor called" << std::endl;
}

FragTrap::FragTrap(const std::string name): ClapTrap(name) {
    this->hit_points = 100;
    this->energy_points = 100;
    this->attack_damage = 30;
    std::cout << "FragTrap Constructor for " << this->name << " called" << std::endl;
}

FragTrap::FragTrap(const FragTrap &src) : ClapTrap(src) {
    std::cout << "FragTrap copy constructor called" << std::endl;
}

FragTrap &FragTrap::operator=(const FragTrap &rhs) {
    if (this!= &rhs) {
        ClapTrap::operator=(rhs);
    }
    std::cout << "FragTrap assignment operator called" << std::endl;
    return *this;
}

FragTrap::~FragTrap () {
    std::cout << "FragTrap Destructor for " << this->name << " called" << std::endl;
}

void FragTrap::attack(const std::string &target) {
    if (0 < this->energy_points && 0 < this->hit_points) {
        this->energy_points -= 1;
        std::cout << "FragTrap " << this->name << " attacks " << target 
                  << " aggressively, dealing " << this->attack_damage 
                  << " points of damage!" << std::endl;
    } else {
        std::cout << "FragTrap " << this->name << " requires repair." << std::endl;
    }
}

void FragTrap::highFivesGuys(void) {
    std::cout << "FragTrap " << this->name << "highfives guys" << std::endl;
}

