//
// Created by libin on 2025/6/7.
//

#ifndef MULTITHREADINGPRACTICE_TASKQUEUE_H
#define MULTITHREADINGPRACTICE_TASKQUEUE_H

#include <queue>
#include <functional>
#include <mutex>
#include <condition_variable>

/*
 * 实现一个多线程处理任务队列类，支持多生产者和多消费者
 * 内部维护 std::queue<std::function<void()>> tasks;
 * 提供模板方法 push_task(F&& f)
 * 消费者线程循环从队列中 pop 任务并执行
 * */
class TaskQueue {
public:
    TaskQueue() = default;
    ~TaskQueue() { stop(); }

    // 完全在头文件中定义模板方法，确保 push_task 可见
    template<typename F>
    void push_task(F &&f) {
        {
            std::unique_lock<std::mutex> lock(mtx);
            tasks.emplace(std::forward<F>(f));  // 完美转发，可移动可复制
        }
        cv.notify_one();
    }

    void run();     // 在消费者线程调用，循环执行任务
    void stop();    // 通知停止，退出 run() 循环
private:
    std::queue<std::function<void()>> tasks;
    std::mutex mtx;
    std::condition_variable cv;
    bool stop_flag = false;
};


#endif //MULTITHREADINGPRACTICE_TASKQUEUE_H
