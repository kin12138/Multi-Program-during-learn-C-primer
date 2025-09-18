//
// Created by libin on 2025/6/7.
//

#include "TaskQueue.h"

void TaskQueue::run() {
    while (true) {
        std::function<void()> task;
        {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [this] { return stop_flag || tasks.empty(); });
            if (stop_flag && tasks.empty()) break;
            task = std::move(tasks.front());
            tasks.pop();
        }
        task();     // 执行
    }
}

void TaskQueue::stop() {
    {
        std::unique_lock<std::mutex> lock(mtx);
        stop_flag = true;
    }
    cv.notify_all();
}