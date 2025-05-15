//
// Created by libin on 2025/4/17.
//

#include "TextQuery.h"
#include "QueryResult.h"
#include <sstream>

TextQuery::TextQuery(std::ifstream &infile) : data(){
    std::string text;
    while (std::getline(infile, text)) {
        // 将一行文本保存为 vector 的一个元素
        data.push_back(text);
        line_no line_number = data.size() - 1;    // 当前行号

        // 在 map 中保存每个单词和它相应的行号
        std::string word;
        std::istringstream stream(text);
        while (stream >> word) {
            auto &lines = wl_map[word];
            if (!lines)     // 如果单词是第一次碰到的，此指针为空
                lines.reset(new Line_set);  // 分配一个新的 set
            lines->insert(line_number);
        }
    }
}

QueryResult TextQuery::query(const std::string & word) const {
    static auto no_lines = std::make_shared<Line_set> ();

    auto it = wl_map.find(word);
    if (it == wl_map.end())
        return QueryResult(word, data, no_lines);
    else
        return QueryResult(word, data, it->second);
}