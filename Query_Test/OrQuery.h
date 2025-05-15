//
// Created by libin on 2025/5/10.
//

#ifndef QUERY_TEST_ORQUERY_H
#define QUERY_TEST_ORQUERY_H
#include "BinaryQuery.h"
#include "Query.h"

class OrQuery : public BinaryQuery{
private:
    friend Query operator|(const Query &, const Query&);
    OrQuery(const Query & left, const Query & right) :
            BinaryQuery(left, right, "|") { std::cout << "OrQuery constructor" << std::endl; }
private:
    // 具体的类，OrQuery 继承了 rep，定义了其他纯虚函数
    QueryResult eval(const TextQuery & ) const override;
    Query_base * clone() const override { return new OrQuery(*this); }
};

inline
Query operator|(const Query & lhs, const Query & rhs) {
//    return std::shared_ptr<Query_base> (new OrQuery(lhs, rhs));
    return new OrQuery(lhs, rhs);
}

#endif //QUERY_TEST_ORQUERY_H
