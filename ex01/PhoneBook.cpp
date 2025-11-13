#include "PhoneBook.hpp"
#include "Contact.hpp"
#include <string>
#include <iostream>
#include <sstream>

// ====== helper functions ======

int string2index(std::string index_string) {
	int n;
	std::stringstream ss(index_string);
	ss >> n;
	if (ss.fail()) {
		return -1;
	} else {
		return n;
	}
}

PhoneBook::PhoneBook() : len(0), ptr(0) { }

void PhoneBook::add(
	std::string first_name,
	std::string last_name,
	std::string nickname,
	std::string phone_number,
	std::string secret
) {
	this->contacts[this->ptr].set_first_name(first_name);
	this->contacts[this->ptr].set_last_name(last_name);
	this->contacts[this->ptr].set_nickname(nickname);
	this->contacts[this->ptr].set_phone_number(phone_number);
	this->contacts[this->ptr].set_secret(secret);
	this->ptr = (this->ptr + 1) % 8;
	if (this->len < 8) {
		this->len += 1;
	}
}

Contact *PhoneBook::get_contact_by_index(int index){
	if (0 <= index && index < this -> len) {
		return &this->contacts[index];
	} else {
		return NULL;
	}
}

void PhoneBook::show_contacts() {
	for (int i = 0; i < this->len; i++) {

		std::string spaces(10, ' ');
		spaces[9] = '0' + i;
		std::cout << spaces << "|" << this->contacts[i].get_show_contact() << std::endl;
	}
}

// ====== command functions ======

int PhoneBook::search_command() {
	std::string number;
	this->show_contacts();
	std::cout << "index: " ;
	std::getline(std::cin, number);
	int index = string2index(number);
	if (index == -1)
	{
		std::cout << "error! you have to enter number." << std::endl;
	}
	else {
		// show contact info 
		Contact *contact = this->get_contact_by_index(index);
		if (contact == NULL) {
			std::cout << "please enter the number range of 0 <= n < " << this->len << std::endl;
		} else {
			contact->show_all_info_per_line();
		}
	}
	return 0;
}

int PhoneBook::add_command() {
	std::string first_name;
	std::string last_name;
	std::string nickname;
	std::string phone_number;
	std::string secret;

	std::cout << "first_name: " ;
	std::getline(std::cin, first_name);
	std::cout << "last_name: " ;
	std::getline(std::cin, last_name);
	std::cout << "nickname: " ;
	std::getline(std::cin, nickname);
	std::cout << "phone_number: " ;
	std::getline(std::cin, phone_number);
	std::cout << "secret: " ;
	std::getline(std::cin, secret);
	if (
		first_name == "" ||
		last_name == "" ||
		nickname == "" ||
		phone_number == "" ||
		secret == ""
	) {
		std::cout << "empty field not be allowed" << std::endl;
	} else {
		this->add(
			first_name,
			last_name,
			nickname,
			phone_number, 
			secret
		);
	}
	return 0;
}

int PhoneBook::show_all_info_per_line() {
	return 0;
}

