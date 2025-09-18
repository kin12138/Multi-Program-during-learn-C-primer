//
// Created by libin on 2025/6/20.
//

#ifndef SIMPLECONCURRENTWEBCRAWLER_PARSER_H
#define SIMPLECONCURRENTWEBCRAWLER_PARSER_H
#pragma once
#include "UrlDepth.h"
#include <vector>

class Parser {
public:
    // 从 html 中提取所有 HTTP/HTTPS 链接
    static std::vector<std::string> parseLinks(const std::string & html);
};


#endif //SIMPLECONCURRENTWEBCRAWLER_PARSER_H
