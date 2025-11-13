#pragma once
#ifndef __PHONEBOOK_H__
#define __PHONEBOOK_H__
#include "Contact.hpp"

class PhoneBook {
public:
	PhoneBook();
	~PhoneBook();

// ====== command functions ======
	int search_command();
	int add_command();
	int show_all_info_per_line();
private:
	Contact contacts[8];
	int len;
	int ptr;
	Contact *get_contact_by_index(int index);
	std::string get_secret_by_index(int index);
	void show_contacts();
	void add(
		std::string first_name,
		std::string last_name,
		std::string nickname,
		std::string phone_number,
		std::string secret
	);
};

#endif

