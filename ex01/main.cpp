#include "Zombie.hpp"

Zombie* zombieHorde(int N, std::string name);

int main() {
	Zombie* zs = zombieHorde(10, "Tom");
	zs[1].announce();
	delete [] zs;
	return 0;
}
