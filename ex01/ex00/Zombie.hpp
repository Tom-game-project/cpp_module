#pragma once
#include <string>
#ifndef __Zombie_H__
#define __Zombie_H__

class Zombie {
public:
	Zombie(std::string);
	~Zombie();
	void announce(void);
private:
	std::string name;
};

#endif

