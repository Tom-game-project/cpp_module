#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"
#include <iostream>

int main()
{
    const Animal* meta = new Animal();
    const Animal* j = new Dog();
    const Animal* i = new Cat();
    std::cout << j->getType() << " " << std::endl;
    std::cout << i->getType() << " " << std::endl;
    i->makeSound(); //will output the cat sound!
    j->makeSound();
    meta->makeSound();

    delete i;
    delete j;
    delete meta;

    // wrong animal case
    const WrongAnimal* wrong_meta = new WrongAnimal();
    const WrongAnimal* wrong_cat = new WrongCat();

    std::cout << wrong_cat->getType() << " " << std::endl;
    std::cout << wrong_meta->getType() << " " << std::endl;

    wrong_cat->makeSound();  // wanimal wanimal
    wrong_meta->makeSound(); 

    delete wrong_cat;
    delete wrong_meta;

    return 0;
}
