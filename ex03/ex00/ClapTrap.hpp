#pragma once
#ifndef __ClapTrap_H__
#define __ClapTrap_H__

#include <string>

class ClapTrap {
public:
	// Orthodox Canonical Form
	ClapTrap();
	ClapTrap(const ClapTrap &other);
	ClapTrap &operator=(const ClapTrap &other);
    // subject
	ClapTrap(std::string name);
	~ClapTrap();
    void attack(const std::string& target);
    void takeDamage(unsigned int amount);
    void beRepaired(unsigned int amount);
private:
    std::string name;
    unsigned int hit_points;
    unsigned int energy_points;
    unsigned int attack_damage;
};

#endif


