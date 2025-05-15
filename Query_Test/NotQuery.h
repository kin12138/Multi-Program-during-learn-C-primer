//
// Created by libin on 2025/5/10.
//

#ifndef QUERY_TEST_NOTQUERY_H
#define QUERY_TEST_NOTQUERY_H
#include "Query_base.h"
#include "Query.h"

class NotQuery : public Query_base{
    friend Query operator~(const Query &);
private:
    NotQuery(const Query & q) : query(q) { std::cout << "NotQuery constructor" << std::endl; }
private:
    std::string rep() const override {
        std::cout << "NotQuery rep" << std::endl;
        return "~(" + query.rep() + ")";
    }
    QueryResult eval(const TextQuery &) const override;

    Query_base * clone() const override {
        return new NotQuery(*this);
    }
private:
    Query query;
};

inline
Query operator~(const Query & operand) {
//    return std::shared_ptr<Query_base> (new NotQuery(operand));
    return new NotQuery(operand);
}

#endif //QUERY_TEST_NOTQUERY_H
