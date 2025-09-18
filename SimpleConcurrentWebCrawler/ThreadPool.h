//
// Created by libin on 2025/6/20.
//

#ifndef SIMPLECONCURRENTWEBCRAWLER_THREADPOOL_H
#define SIMPLECONCURRENTWEBCRAWLER_THREADPOOL_H
#include "queue.h"
#include <vector>
#include <thread>
#include <functional>
#include <future>

class ThreadPool {
public:
    explicit ThreadPool (size_t num_threads);
    ThreadPool(const ThreadPool&) = delete;
    ThreadPool & operator=(const ThreadPool &) = delete;

    template<typename F, typename ... Args>
    auto enqueue(F && f, Args&& ...args)
                -> std::future<typename std::result_of<F(Args...)>::type>;

    ~ThreadPool();
private:
    void worker();  // 工作线程主循环
private:
    std::vector<std::thread> workers;   // 保存所有线程
    queue<std::function<void()>> tasks;     // 任务队列
};

inline
void ThreadPool::worker() {
    auto tid = std::this_thread::get_id();
    while (true) {
        std::function<void()> task;
        if (!tasks.wait_and_pop(task))
            break;
        task();
    }
}

inline
ThreadPool::ThreadPool(size_t num_threads) {
    // 启动指定数量的线程
    for (size_t i = 0; i < num_threads; ++i)
        workers.emplace_back([this] { this->worker(); });
}

inline
ThreadPool::~ThreadPool() {
    // 关闭任务队列
    tasks.close();
    // 等待每个线程执行完毕
    for (std::thread & t : workers) if (t.joinable()) t.join();
}

template<typename F, typename ... Args>
auto ThreadPool::enqueue(F &&f, Args &&...args)
        -> std::future<typename std::result_of<F(Args...)>::type>
{
    using return_type = typename std::result_of<F(Args...)>::type;
    auto bound = std::bind(std::forward<F>(f), std::forward<Args>(args)...);    // 构造无参可调用对象
    auto taskPtr =std::make_shared<std::packaged_task<return_type()>>(bound);   // 包装无参可调用对象
    std::future<return_type> res =taskPtr->get_future();     // 获取 future，返回给调用者

    tasks.push([taskPtr]() { (*taskPtr)(); });
    return res;
}

#endif //SIMPLECONCURRENTWEBCRAWLER_THREADPOOL_H
