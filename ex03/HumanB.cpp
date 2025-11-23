#include "HumanB.hpp"
#include "Weapon.hpp"
#include <string>
#include <iostream>

HumanB::HumanB(std::string name): name(name) {
	this->weapon = NULL;
}
HumanB::~HumanB () {}

void HumanB::attack () {
	if (weapon == NULL) {
		std::cout << this->name << " have no weapon" << std::endl;
	} else {
		std::cout << this->name << " attacks with their " << weapon->getType() << std::endl;
	}
}

void HumanB::setWeapon(Weapon &weapon) {
	this->weapon = &weapon;
}
