//
// Created by libin on 2025/5/15.
//

#ifndef ANIMAL_CAT_H
#define ANIMAL_CAT_H
#include "Animals.h"
#include <iostream>

class Cat : public Animals{
public:
    Cat() : Animals("Cat") { }
    void makeSound() const override { std::cout << "Meow!\n"; }
};


#endif //ANIMAL_CAT_H
