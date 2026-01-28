#pragma once
#include <string>
#ifndef __HUMANA_H__
#define __HUMANA_H__
#include "Weapon.hpp"

class HumanA {
public:
	HumanA(std::string name, Weapon& weapon);
	~HumanA();
	void attack();
private:
	std::string name;
	Weapon &weapon;
};

#endif

