//
// Created by libin on 2025/6/20.
//

#ifndef SIMPLECONCURRENTWEBCRAWLER_FETCHER_H
#define SIMPLECONCURRENTWEBCRAWLER_FETCHER_H
#pragma once
#include <string>


class Fetcher {
public:
    // 下载 URL，返回页面正文；抛出异常或返回空串表示失败
    static std::string fetch(const std::string & url);
};


#endif //SIMPLECONCURRENTWEBCRAWLER_FETCHER_H
