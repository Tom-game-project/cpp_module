#include "Weapon.hpp"
#include <string>

Weapon::Weapon (std::string type): type(type) {}
Weapon::~Weapon () {}

std::string& Weapon::getType() {
	return this->type;
}

void Weapon::setType(std::string newType) {
	this->type = newType;
}

