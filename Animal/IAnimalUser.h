//
// Created by libin on 2025/5/15.
//

#ifndef ANIMAL_IANIMALUSER_H
#define ANIMAL_IANIMALUSER_H

#include <string>

class IAnimalUser {
public:
    virtual void makeSound() const = 0;
    virtual std::string name() const = 0;
    virtual ~IAnimalUser() = default;
};

#endif //ANIMAL_IANIMALUSER_H
