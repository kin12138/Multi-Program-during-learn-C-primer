//
// Created by libin on 2025/3/21.
//

#include "Person.h"

// 输入 人的名字，地址信息
std::istream & read(std::istream & is, Person &item) {
    is >> item.name >> item.address;
    return is;
}

std::ostream & print(std::ostream & os, const Person & item) {
    os << item.getName() + " " << item.address;
    return os;
}