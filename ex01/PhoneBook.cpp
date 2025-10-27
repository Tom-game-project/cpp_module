#include "PhoneBook.hpp"
#include "Contact.hpp"
#include <string>
#include <iostream>

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

void PhoneBook::show_contacts() {
	for (int i = 0; i < this->len; i++) {

		std::string spaces(10, ' ');
		spaces[9] = '0' + i;
		std::cout << spaces << "|" << this->contacts[i].get_show_contact() << std::endl;
	}
}

int main() {
	PhoneBook *a = new PhoneBook();

	a->add("Tom", "0427", "Phantom", "89846295", "empty");
	a->add("Tom", "0427", "Phantom", "89846295", "empty");
	a->add("Tom", "0427", "Phantom", "89846295", "empty");
	a->add("Tom", "0427", "Phantom", "89846295", "empty");
	a->show_contacts();
}
