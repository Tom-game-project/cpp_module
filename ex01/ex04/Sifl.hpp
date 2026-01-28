#pragma once
#include <string>
#ifndef __SIFL_H__
#define __SIFL_H__

class Sifl {
public:
	Sifl(std::string filename, std::string s1, std::string s2);
	~Sifl();
	std::string replace();
	void out();
private:
	std::string filename;
	std::string content;
       	std::string s1;
       	std::string s2;
};

#endif

