cmake_minimum_required(VERSION 3.27)
project(Animal)

set(CMAKE_CXX_STANDARD 14)

add_executable(Animal main.cpp
        Animals.h
        Dog.cpp
        Dog.h
        Cat.cpp
        Cat.h
        AnimalFactory.h
        Test.h
        IAnimalUser.h
        AnimalAdapter.cpp
        AnimalAdapter.h)
