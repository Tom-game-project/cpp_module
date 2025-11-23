#include "Zombie.hpp"
#include <string>
#include <iostream>

Zombie::Zombie(std::string name): name(name) {}

Zombie::~Zombie() {
	std::cout << this->name << " is dead" << std::endl;
}

void Zombie::announce() {
	std::cout << this->name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}

