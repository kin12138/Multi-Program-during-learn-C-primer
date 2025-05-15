//
// Created by libin on 2025/5/10.
//

#ifndef QUERY_TEST_QUERY_BASE_H
#define QUERY_TEST_QUERY_BASE_H
#include "TextQuery.h"
#include "QueryResult.h"

class Query_base {
    friend class Query;
protected:
    using line_no = TextQuery::line_no;
    virtual ~Query_base() = default;
    // 增加多态拷贝
    virtual Query_base * clone() const = 0;
private:
    // eval 返回与当前 Query 匹配的 QueryResult
    virtual QueryResult eval(const TextQuery &) const = 0;
    // rep 是表示查询的一个 string
    virtual std::string rep() const = 0;
};


#endif //QUERY_TEST_QUERY_BASE_H
