//
// Created by libin on 2025/5/15.
//

#ifndef ANIMAL_ANIMALADAPTER_H
#define ANIMAL_ANIMALADAPTER_H
#include "Animals.h"
#include "IAnimalUser.h"
#include <memory>

class AnimalAdapter : public IAnimalUser{
public:
    explicit AnimalAdapter(std::unique_ptr<Animals> animals) :
                                animals_(std::move(animals)) { }

    void makeSound() const override { animals_->makeSound(); }
    std::string name() const override { return animals_->name_; }

private:
    std::unique_ptr<Animals> animals_;
};


#endif //ANIMAL_ANIMALADAPTER_H
