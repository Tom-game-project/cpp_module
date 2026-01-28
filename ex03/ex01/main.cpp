#include "ScavTrap.hpp"
#include <iostream>

int main() {
    std::cout << "=== TEST 1: Construction Chain ===" << std::endl;
    ScavTrap *robot = new ScavTrap("Serena");
    
    std::cout << "\n=== TEST 2: Attributes & Attack ===" << std::endl;
    // HP: 100, EP: 50, AD: 20 のはず
    robot->attack("TargetDummy"); 
    // EPは49になるはず
    
    std::cout << "\n=== TEST 3: Special Ability ===" << std::endl;
    robot->guardGate();
    
    std::cout << "\n=== TEST 4: Polymorphism Safety (Destruction) ===" << std::endl;
    // ClapTrapポインタで受けて削除する場合のテスト（仮想デストラクタの確認）
    ClapTrap *basePtr = new ScavTrap("Polymorph");
    delete basePtr; // ScavTrap -> ClapTrap の順で呼ばれればOK

    std::cout << "\n=== TEST 5: Stack Destruction Chain ===" << std::endl;
    delete robot;

    return 0;
}
