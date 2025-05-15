//
// Created by libin on 2025/5/15.
//

#ifndef ANIMAL_TEST_H
#define ANIMAL_TEST_H

#include "AnimalFactory.h"

void test() {
   auto dog = AnimalFactory::create("dog");
   dog->makeSound();
   auto cat = AnimalFactory::create("cat");
   cat->makeSound();
}

#endif //ANIMAL_TEST_H
