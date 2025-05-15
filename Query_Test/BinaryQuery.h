//
// Created by libin on 2025/5/10.
//

#ifndef QUERY_TEST_BINARYQUERY_H
#define QUERY_TEST_BINARYQUERY_H
#include "Query_base.h"
#include "Query.h"

class BinaryQuery : public Query_base {
protected:
    BinaryQuery(const Query & l, const Query & r, std::string s) :
                lhs(l), rhs(r), opSym(s) { std::cout << "BinaryQuery constructor" << std::endl;}
    std::string rep() const override {
        std::cout << "BinaryQuery rep" << std::endl;
        return "(" + lhs.rep() + " " + opSym + " " + rhs.rep() + ")" ;
    }
protected:
    Query lhs, rhs;     // 左侧和右侧运算对象
    std::string opSym;  // 运算符的名字
};

#endif //QUERY_TEST_BINARYQUERY_H
