#pragma once
#ifndef __SCAVTRAP_H__
#define __SCAVTRAP_H__
#include "ClapTrap.hpp"

class ScavTrap : public ClapTrap {
public:
	// Orthodox Canonical Form
    ScavTrap();
    ScavTrap(std::string name);
    ScavTrap(const ScavTrap &src);
    ~ScavTrap();
    ScavTrap &operator=(const ScavTrap &rhs);

    void attack(const std::string &target);

    // scavtrap unique method
    void guardGate();
};

#endif


