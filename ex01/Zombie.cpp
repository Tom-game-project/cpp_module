#include "Zombie.hpp"
#include <string>
#include <iostream>

Zombie::Zombie(): name("") {}

Zombie::~Zombie() {
	std::cout << this->name << " is dead" << std::endl;
}

void Zombie::announce() {
	std::cout << this->name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}

void Zombie::setName(std::string name) {
	this->name = name;
}
