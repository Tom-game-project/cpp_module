#include "Zombie.hpp"
#include <string>

Zombie *newZombie(std::string name) {
	Zombie* z = new Zombie(name);
	z->announce();
	return z;
}
