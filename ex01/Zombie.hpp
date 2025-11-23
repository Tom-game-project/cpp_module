#pragma once
#include <string>
#ifndef __Zombie_H__
#define __Zombie_H__

class Zombie {
public:
	Zombie();
	~Zombie();
	void announce(void);

	void setName(std::string);
private:
	std::string name;
};

#endif

