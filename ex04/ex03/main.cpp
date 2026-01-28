/*
// subject example test 
#include "IMateriaSource.hpp"
#include "ICharacter.hpp"
#include "Character.hpp"
#include "MateriaSource.hpp"
#include "Ice.hpp"
#include "Cure.hpp"

int main()
{
    IMateriaSource* src = new MateriaSource();
    src->learnMateria(new Ice());
    src->learnMateria(new Cure());
    ICharacter* me = new Character("me");
    AMateria* tmp;
    tmp = src->createMateria("ice");
    me->equip(tmp);
    tmp = src->createMateria("cure");
    me->equip(tmp);
    ICharacter* bob = new Character("bob");
    me->use(0, *bob);
    me->use(1, *bob);
    delete bob;
    delete me;
    delete src;
    return 0;
}
*/

#include <iostream>
#include "IMateriaSource.hpp"
#include "ICharacter.hpp"
#include "Character.hpp"
#include "MateriaSource.hpp"
#include "Ice.hpp"
#include "Cure.hpp"

int main()
{
    std::cout << "=== MateriaSource 作成 ===" << std::endl;
    IMateriaSource* src = new MateriaSource();
    src->learnMateria(new Ice());
    src->learnMateria(new Cure());

    std::cout << "\n=== Character me 作成 ===" << std::endl;
    ICharacter* me = new Character("me");

    AMateria* tmp;
    tmp = src->createMateria("ice");
    me->equip(tmp);
    tmp = src->createMateria("cure");
    me->equip(tmp);

    std::cout << "\n=== Character bob 作成 ===" << std::endl;
    ICharacter* bob = new Character("bob");

    std::cout << "\n=== me -> bob use ===" << std::endl;
    me->use(0, *bob);
    me->use(1, *bob);

    std::cout << "\n=== コピーコンストラクタのテスト ===" << std::endl;
    Character copy_me(*(Character*)me);   // ← copy ctor
    copy_me.use(0, *bob);
    copy_me.use(1, *bob);
    std::cout << "\n=== me がbobへaction ===" << std::endl;
    me->use(0, *bob);

    std::cout << "\n=== 代入演算子（copy-and-swap）のテスト ===" << std::endl;
    Character assigned("assigned");

    assigned = *(Character*)me;            // ← operator=
    assigned.use(0, *bob);
    assigned.use(1, *bob);

    std::cout << "\n=== me がbobへaction ===" << std::endl;
    me->use(0, *bob);

    std::cout << "\n=== オリジナル削除 ===" << std::endl;
    delete bob;
    delete me;

    std::cout << "\n=== コピー達はまだ使えるか ===" << std::endl;
    ICharacter* dummy = new Character("dummy");
    copy_me.use(0, *dummy);
    assigned.use(1, *dummy);
    delete dummy;

    std::cout << "\n=== 終了処理 ===" << std::endl;
    delete src;
    return 0;
}

