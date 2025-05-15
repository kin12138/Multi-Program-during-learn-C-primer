//
// Created by libin on 2025/5/10.
//

#ifndef QUERY_TEST_WORDQUERY_H
#define QUERY_TEST_WORDQUERY_H
#include "Query_base.h"

class WordQuery : public Query_base{
private:
    friend class Query;     // Query 使用 WordQuery 的构造函数
private:
    WordQuery(const std::string & s) : query_word(s) { }
    // 具体的类，WordQuery 将定义所有继承而来的纯虚函数
    QueryResult eval(const TextQuery & t) const override
            { return t.query(query_word); }
    std::string rep() const override {
        std::cout << "WordQuery rep" << std::endl;
        return query_word;
    }

    Query_base * clone() const override {
        return new WordQuery(*this);
    }

private:
    std::string query_word;     // 要查询的单词
};


#endif //QUERY_TEST_WORDQUERY_H
