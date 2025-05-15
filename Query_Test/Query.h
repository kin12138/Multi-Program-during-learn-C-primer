//
// Created by libin on 2025/5/10.
//

#ifndef QUERY_TEST_QUERY_H
#define QUERY_TEST_QUERY_H
#include "Query_base.h"

// 这是一个管理 Query_base 继承体系的接口类
class Query {
    // 这些运算符需要访问接受 shared_ptr 的构造函数，而该函数是私有的
    friend Query operator~(const Query &);
    friend Query operator&(const Query &, const Query &);
    friend Query operator|(const Query &, const Query &);
public:
    Query(const Query & other) : q(other.q->clone()) { }
    Query & operator=(const Query & rhs) {
        if (this != &rhs) {
            delete q;
            q = rhs.q->clone();
        }
        return *this;
    }
    Query(Query && other) noexcept :q(other.q) { other.q = nullptr; }
    Query & operator=(Query && rhs) noexcept {
        if (this != &rhs) {
            delete q;
            q = rhs.q;
            rhs.q = nullptr;
        }
        return *this;
    }
    ~Query() { delete q; }
public:
    Query(const std::string & );    // 构建一个新的 WordQuery
    // 接口函数：调用对应的 Query_base 操作
    QueryResult eval(const TextQuery & t) const { return q->eval(t); }
    std::string rep() const {
        std::cout << "Query rep" << std::endl;
        return q->rep();
    }
private:
    /*Query(std::shared_ptr<Query_base> query) : q(query) {
        std::cout << "Query::Query(std::shared_ptr<Query_base> query)" << std::endl;
    }*/
    Query(Query_base *query) : q(query) { }
private:
//    std::shared_ptr<Query_base> q;
    Query_base *q;
};

std::ostream & operator<<(std::ostream & os, const Query & query);

#endif //QUERY_TEST_QUERY_H
