#include "ClapTrap.hpp"
#include <iostream>

int main() {
    // 1. コンストラクタのテスト
    std::cout << "--- Construction ---" << std::endl;
    ClapTrap hero("Hero");
    ClapTrap villain("Villain");

    // 2. 攻撃とダメージのテスト
    std::cout << "\n--- Battle Start ---" << std::endl;
    hero.attack("Villain");
    villain.takeDamage(0); // 攻撃力0なのでダメージ0

    // 3. ダメージと回復のテスト
    std::cout << "\n--- Taking Damage & Repairing ---" << std::endl;
    hero.takeDamage(5);    // 5ダメージ受ける (HP: 10 -> 5)
    hero.beRepaired(3);    // 3回復する (HP: 5 -> 8, Energy: 10 -> 8)

    // 4. エネルギー枯渇のテスト
    std::cout << "\n--- Energy Depletion Test ---" << std::endl;
    // エネルギーを使い果たすまで行動させる
    for (int i = 0; i < 12; ++i) {
        hero.attack("Dummy");
    }
    // ここではエネルギー不足で攻撃できないはず

    // 5. HP枯渇のテスト
    std::cout << "\n--- HP Depletion Test ---" << std::endl;
    villain.takeDamage(100); // 致命的なダメージ
    villain.attack("Hero");  // 死んでいるので攻撃できないはず
    villain.beRepaired(10);  // 死んでいるので回復できないはず

    // 6. デストラクタのテスト
    std::cout << "\n--- Destruction ---" << std::endl;
    // main関数のスコープを抜けるときに自動的にデストラクタが呼ばれる
    return 0;
}
