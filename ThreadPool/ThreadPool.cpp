//
// Created by libin on 2025/6/18.
//

#include "ThreadPool.h"
#include <memory>

// 构造函数
ThreadPool::ThreadPool(size_t numThreads) {
    // 启动指定数量的线程
    for (int i = 0; i < numThreads; ++i) {
        // 每个线程执行 worker() 函数
        workers.emplace_back([this] {
            this->worker();
        });
    }
}

// 析构函数
ThreadPool::~ThreadPool() {
//    std::cerr << "[ThreadPool] Destructor: closing queue\n";
    tasks.close();
//    std::cerr << "[ThreadPool] Destructor: joined?\n";
    // 等待每个线程执行完毕
    for(std::thread & t : workers) if (t.joinable()) t.join();
//    std::cerr << "[ThreadPool] Destructor: all joined\n";
}

// 工作线程函数

void ThreadPool::worker() {
    auto tid = std::this_thread::get_id();
    while (true) {
        std::function<void()> task;
        if (!tasks.wait_and_pop(task))      // wait_and_pop 返回 false 表示队列关闭且空
            break;
        try {
            task();
        }
        catch (const std::exception & e) {
//            std::cerr << "[Worker "<< tid <<"] task threw: " << e.what() << "\n";
        }
    }
}