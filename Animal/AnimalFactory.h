//
// Created by libin on 2025/5/15.
//

#ifndef ANIMAL_ANIMALFACTORY_H
#define ANIMAL_ANIMALFACTORY_H
#include "Animals.h"
#include "IAnimalUser.h"
#include "AnimalAdapter.h"
#include "Dog.h"
#include "Cat.h"
#include <memory>

class AnimalFactory{
public:
    static std::unique_ptr<IAnimalUser> create(const std::string & type) {
        if (type == "dog") {
            return std::make_unique<AnimalAdapter>( std::make_unique<Dog>());
        } else if (type == "cat") {
            return std::make_unique<AnimalAdapter>( std::make_unique<Cat>());
        }
        return nullptr;
    }
};

#endif //ANIMAL_ANIMALFACTORY_H
