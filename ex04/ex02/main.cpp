#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"

#define LENGTH_OF_ANIMAL_ARRAY 100

int main()
{
    // const Animal* animal = new Animal(); 
    const Animal* dog = new Dog();
    const Animal* cat = new Cat();
    delete dog;//should not create a leak
    delete cat;

    const Animal *animal_array[LENGTH_OF_ANIMAL_ARRAY];

    for (int i = 0; i < LENGTH_OF_ANIMAL_ARRAY; i++) {
        if (i % 2 == 0) {
            animal_array[i] = new Dog();
        } else {
            animal_array[i] = new Cat();
        }
    }

    animal_array[50]->makeSound();
    animal_array[51]->makeSound();

    for (int i = 0; i < LENGTH_OF_ANIMAL_ARRAY; i++) {
        delete animal_array[i];
    }
    return 0;
}
