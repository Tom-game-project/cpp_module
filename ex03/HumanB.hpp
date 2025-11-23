#pragma once
#include <string>
#ifndef __HUMANB_H__
#define __HUMANB_H__
#include "Weapon.hpp"

class HumanB {
public:
	HumanB(std::string name);
	~HumanB();
	void attack();
	void setWeapon(Weapon &weapon);
private:
	std::string name;
	Weapon *weapon;
};

#endif

