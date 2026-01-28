#pragma once
#include "ClapTrap.hpp"
#ifndef __FRAGTRAP_H__
#define __FRAGTRAP_H__
#include "ClapTrap.hpp"

class FragTrap : public ClapTrap {
public:
	// Orthodox Canonical Form
    FragTrap();
    FragTrap(std::string name);
    FragTrap(const FragTrap &src);
    ~FragTrap();
    FragTrap &operator=(const FragTrap &rhs);

    void attack(const std::string &target);

    void highFivesGuys(void);
};

#endif


