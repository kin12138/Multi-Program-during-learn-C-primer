//
// Created by libin on 2025/4/17.
//

#ifndef KNOWLEDGETEST_TEXTQUERY_H
#define KNOWLEDGETEST_TEXTQUERY_H

#include <memory>
#include <vector>
#include <map>
#include <set>
#include <fstream>
#include "strBlob.h"

class QueryResult;
class TextQuery {

    using line_no = unsigned ;
    using Line_set = std::set<line_no>;
    using Line_map = std::map<std::string, std::shared_ptr<Line_set>>;
public:
    TextQuery(std::ifstream &);
    QueryResult query(const std::string &) const;

private:
    strBlob data;
    //wl_map 关联单词与行号 set
    Line_map wl_map;
};


#endif //KNOWLEDGETEST_TEXTQUERY_H
