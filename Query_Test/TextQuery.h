//
// Created by libin on 2025/5/10.
//

#ifndef QUERY_TEST_TEXTQUERY_H
#define QUERY_TEST_TEXTQUERY_H
#include <map>
#include <set>
#include <vector>
#include <memory>
#include <string>
#include <fstream>

class QueryResult;
class TextQuery {
public:
    using line_no = unsigned ;
    using line_set = std::set<line_no>;
    using line_map = std::map<std::string, std::shared_ptr<line_set>>;

    TextQuery(std::ifstream &);
    QueryResult query(const std::string &) const;
private:
    std::shared_ptr<std::vector<std::string>> data;    // vector 的每个元素都是一行文本
    line_map wl_map;    // 关联 word 与行号 set
};


#endif //QUERY_TEST_TEXTQUERY_H
