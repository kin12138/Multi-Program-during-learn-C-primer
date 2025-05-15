//
// Created by libin on 2025/5/10.
//

#ifndef QUERY_TEST_ANDQUERY_H
#define QUERY_TEST_ANDQUERY_H
#include "BinaryQuery.h"
#include "Query.h"

class AndQuery : public BinaryQuery{
private:
    friend Query operator&(const Query&, const Query &);
    AndQuery(const Query &left, const Query &right) :
                                            BinaryQuery(left, right, "&") { std::cout << "AndQuery constructor" << std::endl; }
private:
    // 具体的类：AndQuery 继承了 rep ，并定义了其他纯虚函数
    QueryResult eval(const TextQuery &) const override;
    Query_base * clone() const override { return new AndQuery(*this); }
};

inline
Query operator&(const Query & lhs, const Query & rhs) {
//    return std::shared_ptr<Query_base> (new AndQuery(lhs, rhs));
    return new AndQuery(lhs, rhs);
}

#endif //QUERY_TEST_ANDQUERY_H
