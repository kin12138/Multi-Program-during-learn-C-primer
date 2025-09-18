//
// Created by libin on 2025/6/20.
//

#ifndef SIMPLECONCURRENTWEBCRAWLER_CRAWLERCONTROLLER_H
#define SIMPLECONCURRENTWEBCRAWLER_CRAWLERCONTROLLER_H
#pragma once
#include "queue.h"
#include "UrlDepth.h"
#include "ThreadPool.h"
#include <unordered_set>
#include <mutex>
#include <future>

class CrawlerController {
public:
    CrawlerController(int maxDepth, int poolSize) :
            maxDepth_(maxDepth), pool_(poolSize) { }        // 启动 poolSize 个线程

    ~CrawlerController() {
        waitFinsh();    // 确保队列已关闭，线程池析构会等待
    }
    void addSeed(const std::string & url);
    void start();     // 启动消费循环
    void waitFinsh();   // 关闭队列并等待所有任务完成
private:
    void processUrl(const UrlDepth & ud);
private:
    int     maxDepth_;
    queue<UrlDepth> queue_;
    std::unordered_set<std::string> visited_;
    std::mutex visitedMutex_;

    ThreadPool pool_;
};


#endif //SIMPLECONCURRENTWEBCRAWLER_CRAWLERCONTROLLER_H
