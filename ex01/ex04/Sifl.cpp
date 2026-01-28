#include "Sifl.hpp"
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <fstream>

Sifl::Sifl(std::string filename, std::string s1, std::string s2) : filename(filename), s1(s1), s2(s2) {
	std::ifstream file(filename.c_str());
	std::basic_stringstream<char> buffer;
	if (file.is_open()){
		buffer << file.rdbuf();
		this->content = buffer.str();
	} else { 
		std::cout << "Failed to open in file" << std::endl;
		return ;
	}
}

Sifl::~Sifl() {}

std::string Sifl::replace() {
	if (this->s1.empty())
		return this->content;
	std::string result;
	std::size_t pos = 0;
	std::size_t foundPos;
	while ((foundPos = this->content.find(s1, pos)) != std::string::npos) {
		result.append(this->content, pos, foundPos - pos);
		result.append(this->s2);
		pos = foundPos + s1.length();
	}
	result.append(this->content, pos, std::string::npos);
	return result;
}

void Sifl::out() {
	std::string out_filename = this->filename + ".replace";

	std::ofstream ofs(out_filename.c_str(), std::ios::out | std::ios::trunc);
	if (ofs.is_open()) {

		ofs << this->replace() << std::flush;
		return ;
	}else {
		std::cout << "Failed to open out file" << std::endl;
		return ;
	}
}
