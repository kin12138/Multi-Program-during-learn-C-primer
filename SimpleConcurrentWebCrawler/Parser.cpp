//
// Created by libin on 2025/6/20.
//

#include "Parser.h"
#include <regex>

std::vector<std::string> Parser::parseLinks(const std::string &html) {
    static const std::regex urlRe(
            R"((https?://[^\s"'>]+))",std::regex::icase
            );
    std::vector<std::string> links;
    std::smatch m;
    auto begin = html.cbegin(), end = html.cend();
    while (std::regex_search(begin, end, m, urlRe)) {
        links.push_back(m[1].str());
        begin = m.suffix().first;
    }
    return links;
}
