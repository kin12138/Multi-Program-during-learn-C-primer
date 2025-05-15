//
// Created by libin on 2025/5/15.
//

#ifndef ANIMAL_DOG_H
#define ANIMAL_DOG_H
#include "Animals.h"
#include <iostream>

class Dog : public Animals {
public:
    Dog() : Animals("Dog") { }
    void makeSound () const override { std::cout << "Woof\n";}
};


#endif //ANIMAL_DOG_H
