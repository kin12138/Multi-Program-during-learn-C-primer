//
// Created by libin on 2025/5/15.
//

#ifndef ANIMAL_ANIMALS_H
#define ANIMAL_ANIMALS_H
#include <string>

class AniamlAdapter;
class Animals {
    friend class AnimalAdapter;
public:
    explicit Animals(std::string n) : name_(std::move(n)) { }
    virtual void makeSound() const = 0;
    virtual ~Animals() = default;
protected:
    std::string name_;
};

#endif //ANIMAL_ANIMALS_H
