//
// Created by libin on 2025/5/10.
//

#include "Query.h"
#include "WordQuery.h"

std::ostream & operator<<(std::ostream & os, const Query & query) {
    os << query.rep();
    return os;
}

Query::Query(const std::string & s) : q(new WordQuery(s)) {
    std::cout << "Query constructor where s = " + s << std::endl;
}