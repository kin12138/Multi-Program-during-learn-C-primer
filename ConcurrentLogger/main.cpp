#include <iostream>
#include "Logger.h"

void worker(int id) {
    for(int i = 0; i < 10; ++i) {
        Logger::instance().log(LogLevel::INFO, "worker %d, count %d", id, i);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

int main() {
    Logger::instance().configure("../Resource/app_log", 1024*1024, false);
    std::thread t1(worker, 1);
    std::thread t2(worker, 2);
    t1.join();
    t2.join();

    // 确保所有日志写入文件并关闭
    Logger::instance().flush();
    return 0;
}
