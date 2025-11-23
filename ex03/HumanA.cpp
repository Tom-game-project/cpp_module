#include "HumanA.hpp"
#include "Weapon.hpp"
#include <string>
#include <iostream>

HumanA::HumanA(std::string name, Weapon& weapon): name(name), weapon(weapon) {}
HumanA::~HumanA () {}

void HumanA::attack () {
	std::cout << this->name << " attacks with their " << weapon.getType() << std::endl;
}
