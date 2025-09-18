//
// Created by libin on 2025/6/18.
//

#ifndef THREADPOOL_THREADPOOL_H
#define THREADPOOL_THREADPOOL_H
#include <vector>
#include <thread>
#include <future>
//#include <queue>
#include <condition_variable>
#include <functional>
#include "ThreadSafeQueue.h"
#include <iostream>

class ThreadPool {
private:
    std::vector<std::thread> workers;  // 保存所有的工作线程
    ThreadSafeQueue<std::function<void()>> tasks;    // 任务队列

private:
    void worker();      // 工作线程主循环

public:
    // 构造，启动 numThreads 个工作线程，立即进入等待任务状态
    explicit ThreadPool(size_t numThreads);

    // 禁用拷贝，避免多重析构或混乱
    ThreadPool(const ThreadPool &) = delete;
    ThreadPool & operator=(const ThreadPool &) = delete;

    // 提交任务模板
    // F: 可调用对象类型，Args: 参数包
    // 返回：std::future<return_type>
    template<typename F, typename ... Args>
    auto enqueue(F && f, Args&& ...args)
                ->std::future<typename std::result_of<F(Args...)>::type>;

    // 析构：设置停止标志，通知所有线程并等待它们的退出
    ~ThreadPool();
};

// enqueue 模板函数
// 使用 std::packaged_task 包装任意可调用对象与参数，获取 std::future
template<typename F, typename ...Args>
auto ThreadPool::enqueue(F &&f, Args &&...args)
-> std::future<typename std::result_of<F(Args...)>::type>
{
    using return_type = typename std::result_of<F(Args...)>::type;
    // 使用 std::bind 将 f 与 args 绑定，构造无参可调用对象
    auto boundTask = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
    // 用 packaged_task 将无参可调用对象包装，以便获取 std::future
    auto taskPtr = std::make_shared<std::packaged_task<return_type()>> (boundTask);
    // 从 taskPtr 获取 future ，返回给调用者
    std::future<return_type> result = taskPtr->get_future();
//    std::cerr << "[ThreadPool] enqueue task\n";

    try {
        // 推入队列
        tasks.push([taskPtr] () { (*taskPtr)();});
//        std::cerr << "[ThreadPool] task pushed\n";
    }catch (const std::exception & e) {
        std::cerr << "[ThreadPool] enqueue(): push threw: " << e.what() << "\n";
        throw;
    }
    return result;
}


#endif //THREADPOOL_THREADPOOL_H
