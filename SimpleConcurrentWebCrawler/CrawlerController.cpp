//
// Created by libin on 2025/6/20.
//

#include "CrawlerController.h"
#include "Fetcher.h"
#include "Parser.h"
#include <iostream>

void CrawlerController::addSeed(const std::string &url) {
    std::lock_guard<std::mutex> lk(visitedMutex_);
    if (visited_.insert(url).second)
        queue_.push({url, 0});
}

void CrawlerController::start() {
    // 主线程不断从队列提取任务并提交给线程池
    UrlDepth ud;
    while (queue_.wait_and_pop(ud))
        pool_.enqueue([this, ud] { processUrl(ud); });
}

void CrawlerController::waitFinsh() {
    queue_.close();
    // pool_ 在析构时自动解析
}

void CrawlerController::processUrl(const UrlDepth &ud) {
    if (ud.depth > maxDepth_) return;
    try {
        auto html = Fetcher::fetch(ud.url);
        std::cout << "Fetched: " << ud.url << "\n";
        auto links = Parser::parseLinks(html);
        for (auto & link : links) {
            std::lock_guard<std::mutex> lk(visitedMutex_);
            if (visited_.insert(link).second)
                queue_.push({link, ud.depth + 1});
        }
    } catch (const std::exception &e) {
        std::cerr << "Error fetching " << ud.url << ": " << e.what() << "\n";
    }
}