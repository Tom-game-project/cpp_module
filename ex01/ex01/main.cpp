#include "Zombie.hpp"

Zombie* zombieHorde(int N, std::string name);

int main() {
	// test
	int number_of_zombie = 10;
	Zombie* zs = zombieHorde(number_of_zombie, "Tom");
	for (int i=0; i < number_of_zombie; i++) {
		zs[i].announce();
	}
	zs[1].announce();
	delete [] zs;
	return 0;
}
