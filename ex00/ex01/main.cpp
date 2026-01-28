#include "PhoneBook.hpp"
#include <string>
#include <iostream>

// ====== entr point ======

int main() {
	PhoneBook *phone_book = new PhoneBook();

	while (true) {
		std::string line;
		std::cout << "> " ;
		std::getline(std::cin, line);
		if (line ==  "ADD") {
			phone_book->add_command ();
		} else if (line == "SEARCH"){
			phone_book->search_command();
		} else if (line == "EXIT") {
			break;
		} else {
			// ignore
		}
	}
}
