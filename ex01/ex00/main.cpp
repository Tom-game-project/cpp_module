#include "Zombie.hpp"
#include <iostream>
#include <ostream>
#include <string>

Zombie *newZombie(std::string name);
void randomChump(std::string name);

int main() {
	randomChump("Tom");

	std::cout << "---" << std::endl;
	Zombie*z = newZombie("Tom");
	//z->announce();
	delete z;
	return 0;
}
