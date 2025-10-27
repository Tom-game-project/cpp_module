#include "Contact.hpp"
#include <string>

Contact::Contact ():
	first_name(""),
       	last_name(""),
       	nickname(""),
       	phone_number(""),
       	secret("") {
}

Contact::~Contact () {}

void Contact::set_first_name(std::string first_name) {
	this->first_name=first_name;
}

void Contact::set_last_name(std::string last_name) {
	this->last_name = last_name;
}

void Contact::set_nickname(std::string nickname) {
	this->nickname=nickname;
}

void Contact::set_phone_number(std::string phone_number) {
	this->phone_number=phone_number;
}

void Contact::set_secret(std::string secret) {
	this->secret=secret;
}

std::string out_formatter(std::string str) {
	if (10 <= str.length()) {
		str[9] = '.';
		str.erase(10);
		return str;
	} else {
		std::string s1(10 - str.length(), ' ');
		std::string new_s = s1 + str;
		return new_s;
	}
}

std::string Contact::get_show_contact() {
	// std::string s1 = "hello";
	// std::cout << out_formatter(s1) << std::endl;
	std::string new_s = 
		out_formatter(this->first_name) + "|" \
		+ out_formatter(this->last_name) + "|" \
		+ out_formatter(this->nickname);
	return new_s;
}

/*
int main() {
	std::string s1 = "helloworld";
	std::cout << "\"" << out_formatter(s1) << "\"" << std::endl;
}
*/
