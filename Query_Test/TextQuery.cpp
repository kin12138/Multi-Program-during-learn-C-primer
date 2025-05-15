//
// Created by libin on 2025/5/10.
//

#include "TextQuery.h"
#include <sstream>
#include "QueryResult.h"


TextQuery::TextQuery(std::ifstream & infile) : data(new std::vector<std::string>()) {
    std::string line_text;
    while (std::getline(infile, line_text)) {
        // 将一行文本保存为 vector 的一个元素
        data->push_back(line_text);
        line_no lineNo = data->size() - 1;  // 当前行号

        // 在 map 中保存每个 word 与其对应的行号
        std::string word;
        std::istringstream stream(line_text);
        while (stream >> word) {
            auto &lines = wl_map[word];
            if (!lines)
                lines.reset(new line_set);
            lines->insert(lineNo);
        }
    }
}

QueryResult TextQuery::query(const std::string &word) const {
    static auto no_lines = std::make_shared<line_set>();

    auto it = wl_map.find(word);
    if (it == wl_map.end())
        return QueryResult{word, no_lines, data};
    else
        return QueryResult{word, it->second, data};
}