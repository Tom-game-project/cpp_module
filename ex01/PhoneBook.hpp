#pragma once
#ifndef __PHONEBOOK_H__
#define __PHONEBOOK_H__
#include "Contact.hpp"

class PhoneBook {
public:
	PhoneBook();
	~PhoneBook();
	void add(
		std::string first_name,
		std::string last_name,
		std::string nickname,
		std::string phone_number,
		std::string secret
	);
	void show_contacts();
	const Contact *search(int index);
private:
	Contact contacts[8];
	int len;
	int ptr;
};

#endif

