//
// Created by libin on 2025/3/21.
//

#ifndef KNOWLEDGETEST_PERSON_H
#define KNOWLEDGETEST_PERSON_H

#include <string>

struct Person {
    // member function
    std::string getName() const { return name; }
    std::string getAddress() {return address; }


    // data member
    std::string name;       // 姓名
    std::string address;    // 住址
};

std::istream & read(std::istream &is, Person & item);
std::ostream & print(std::ostream & os, const Person & item);

#endif //KNOWLEDGETEST_PERSON_H
