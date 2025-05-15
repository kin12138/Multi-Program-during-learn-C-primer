//
// Created by libin on 2025/4/17.
//

#ifndef KNOWLEDGETEST_QUERYRESULT_H
#define KNOWLEDGETEST_QUERYRESULT_H
#include <string>
#include <memory>
#include <utility>
#include <vector>
#include <map>
#include <set>
#include <iostream>
#include "strBlob.h"

class QueryResult {
    friend std::ostream & print(std::ostream & os, const QueryResult &);

public:
    QueryResult(const std::string & s,
                strBlob c,
                std::shared_ptr<std::set<unsigned>> ls )
                : sought(s),  contents(std::move(c)), lines(std::move(ls)){ }
private:
    std::string sought;
    strBlob contents;
    std::shared_ptr<std::set<unsigned>> lines;
};

std::ostream & print(std::ostream & os, const QueryResult &);

#endif //KNOWLEDGETEST_QUERYRESULT_H
