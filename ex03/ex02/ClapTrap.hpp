#pragma once
#ifndef __CLAPTRAP_H__
#define __CLAPTRAP_H__

#include <string>

class ClapTrap {
public:
	// Orthodox Canonical Form
	ClapTrap();
	ClapTrap(const ClapTrap &other);
	ClapTrap &operator=(const ClapTrap &other);
    // subject
	ClapTrap(std::string name);
    // 将来的に呼び出しの際に以下のようにされ、且つ基底クラスのデストラクタにvirtualをつけないと継承クラスのデストラクタが呼び出されず未定義動作を引き起こす可能性がある
    // なので、基底クラスのデストラクタはvirtualにする必要がある
	virtual ~ClapTrap();
    virtual void attack(const std::string& target);
    void takeDamage(unsigned int amount);
    void beRepaired(unsigned int amount);
protected:
    std::string name;
    unsigned int hit_points;
    unsigned int energy_points;
    unsigned int attack_damage;
};

#endif


