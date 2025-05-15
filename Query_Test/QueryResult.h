//
// Created by libin on 2025/5/10.
//

#ifndef QUERY_TEST_QUERYRESULT_H
#define QUERY_TEST_QUERYRESULT_H
#include <string>
#include <map>
#include <set>
#include <vector>
#include <memory>
#include <iostream>

class QueryResult {
    friend std::ostream & print(std::ostream & os, const QueryResult &);
public:
    using line_no = unsigned ;
    using line_set = std::set<line_no>;
    using Text = std::shared_ptr<std::vector<std::string>>;

    QueryResult(const std::string & s, std::shared_ptr<line_set> ls, Text c) :
                sought(s), lines(ls), files(c) { }

     line_set::iterator begin() { return lines->begin(); }
    line_set::iterator end() { return lines->end(); }
    Text get_file() { return Text{files}; }
private:
    std::string sought;
    std::shared_ptr<line_set> lines;
    Text files;
};

std::ostream & print(std::ostream & os, const QueryResult &);

#endif //QUERY_TEST_QUERYRESULT_H
