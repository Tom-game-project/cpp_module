#include "Sifl.hpp"
#include <cstddef>
#include <iostream>
#include <ostream>
#include <string>

int main(int argc, char* argv[]) {
	if (argc == 4) {
		std::string filename = argv[1];
		std::string s1 = argv[2];
		std::string s2 = argv[3];
		Sifl* sifl = new Sifl(filename, s1, s2);
		if (sifl == NULL) {
			std::cout << "Sifl alloc Error" << std::endl;
			return 1;
		}
		sifl->out();
		delete sifl;
		// TODO
	} else {
		std::cout << "replace s1 to s2" << std::endl;
		std::cout << "then this program generate <filename>.replace file" << std::endl;
		std::cout << "Usage: ./sifl <filename> <s1> <s2>" << std::endl;
	}
}
