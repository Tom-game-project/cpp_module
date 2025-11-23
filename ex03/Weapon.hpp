#pragma once
#include <string>
#ifndef __WEAPON_H__
#define __WEAPON_H__

class Weapon {
public:
	Weapon(std::string type);
	~Weapon();
	std::string& getType();
	void setType(std::string newType);
private:
	std::string type;
};

#endif

