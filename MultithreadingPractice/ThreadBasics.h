//
// Created by libin on 2025/6/5.
//

#ifndef MULTITHREADINGPRACTICE_THREADBASICS_H
#define MULTITHREADINGPRACTICE_THREADBASICS_H

#include <thread>
#include <iostream>
#include <vector>
#include <atomic>
#include <chrono>
#include <ctime>
#include "TaskQueue.h"

void print_hello() {
    std::cout << "Hello from thread!" << std::endl;
}

void test_thread() {
    std::thread t(print_hello);
    t.join();
    std::cout << "main thread ends." << std::endl;
}

struct func {
    int &i_;
    func(int & i) : i_(i) { }
    void operator()() {
        for (unsigned j = 0; j < 100000; ++j)
            // do something
            ++i_;       // 潜在访问隐患：悬空引用
    }
};

void oops() {
    int some_local_state = 0;
    func my_func(some_local_state);
    std::thread my_thread(my_func);
    my_thread.detach();     // 不等线程结束
}                           // 新线程可能还在运行


void f() {
    int some_local_state = 0;
    func my_func(some_local_state);
    std::thread t(my_func);
    try {
        // do_something
    }
    catch (...)
    {
        t.join();
        throw;
    }
    t.join();
}

class thread_guard {
    std::thread & t_;
public:
    explicit thread_guard(std::thread & t) : t_(t) { }
    ~thread_guard() {
        if (t_.joinable())
            t_.join();
    }
    thread_guard(const thread_guard &) = delete;
    thread_guard & operator=(thread_guard &) = delete;
};

struct func;
void f2() {
    int some_local_state = 0;
    func my_func(some_local_state);
    std::thread t(my_func);
    // do something in current threading
}

void hello() {
    std::cout << "Hello from thread, ID = "
              << std::this_thread::get_id()
              << std::endl;
}

void fib_range(int start, int count) {
    long long a = 0, b = 1;
    for (int i = 0; i < start + count; ++i) {
        long long next = a + b;
        a = b;
        b = next;
        if (i >= start)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            std::cout << "Thread " << std::this_thread::get_id()
                      << " computes Fib(" << i << ") = " << a << std::endl;
        }
    }
}

void main_thread() {
    const int num_threads = 4;
    const int per_thread = 5;
    std::vector<std::thread> threads;

    // 启动 4 个线程，分别计算不同区间
    for (int i = 0; i < num_threads; ++i) {
        int start_index = i * per_thread;
        threads.emplace_back(fib_range, start_index, per_thread);
    }

    // 等待所有线程执行结束
    for(auto & t : threads) {
        if (t.joinable()) {
            t.join();
        }
    }
}

void work_with_join() {
    std::cout << "[子线程] 开始执行，ID = " << std::this_thread::get_id() << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    std::cout << "[子线程] 结束执行\n";
}

void main_work_with_join() {
    std::cout << "[主线程] 创建子线程并等待它的完成\n";
    std::thread t(work_with_join);

    if (t.joinable())
        t.join();

    std::cout << "[主线程] 子线程已经完成，继续执行，程序退出\n";
}

void work_with_detach() {
    std::cout << "[子线程](守护) 开始执行，ID = " << std::this_thread::get_id() << std::endl;
//    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << "[子线程](守护) 结束执行\n";
}

void main_work_with_detach() {
    std::cout << "[主线程] 创建子线程并 detach\n";
    std::thread t(work_with_detach);
    if(t.joinable())
        t.detach();
    std::cout << "[主线程] 继续执行并退出\n";
}

// 全局原子标志，用于通知守护线程停止
std::atomic<bool> stop_flag{false};

// 守护日志线程函数
void logger_thread() {
    while (!stop_flag.load(std::memory_order_relaxed)) {
        // 获取当前时间戳
        auto now = std::chrono::system_clock::now();
        std::time_t t = std::chrono::system_clock::to_time_t(now);

        // 打印日志
        std::cout << "[日志线程] " << std::ctime(&t) << " 记录心跳日志" << std::endl;

        // 等待 1 秒
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    std::cout << "[日志线程] 检测到停止信号，退出线程\n";
}

void main_with_logger_thread() {
    // 启动守护线程
    std::thread t(logger_thread);
    if (t.joinable())
        t.detach();

    // 主线程循环读取用户输入
    std::string line;
    std::cout << "[主线程] 输入文本，输入 \"quit\" 可退出程序\n";
    while (std::getline(std::cin, line)) {
        if (line == "quit") {
            stop_flag.store(true, std::memory_order_relaxed);
            break;
        }
        std::cout << "[主线程] 您输入：" << line << std::endl;
    }

    // 给守护线程一些退出时间
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "[主线程] 已退出，主程序结束\n";
}

/* 测试 TaskQueue */
void test_TaskQueue() {
    TaskQueue queue;

    // 启动消费者线程
    std::thread consumer([&queue]()
                         { queue.run(); });

    // 推送多种任务
    queue.push_task([]() {
        std::cout << "Lambda task executed\n";
    });

    queue.push_task(std::bind([](int x)
        { std::cout << "Bind task with x=" << x << std::endl; }
        , 42));
    queue.push_task([]() {
        std::cout << "Another lambda task.\n";
    });

    auto free_func = []() {
        std::cout << "Free function task\n";
    };

    queue.push_task(free_func);

    // 停止并等待消费者退出
    queue.stop();
    consumer.join();
}

#endif //MULTITHREADINGPRACTICE_THREADBASICS_H
