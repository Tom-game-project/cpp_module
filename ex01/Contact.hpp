#pragma once
#ifndef __CONTACT_H__
#define __CONTACT_H__
#include <string>

class Contact {
public:
	Contact();
	~Contact();
	//
	std::string get_show_contact();

	// setting functions
	void set_first_name(std::string first_name);
	void set_last_name(std::string last_name);
	void set_nickname(std::string nickname);
	void set_phone_number(std::string phone_number);
	void set_secret(std::string secret);
private:
	std::string first_name;
	std::string last_name;
	std::string nickname;
	std::string phone_number;
	std::string secret;
};

#endif
