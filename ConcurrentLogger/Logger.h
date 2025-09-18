//
// Created by libin on 2025/6/19.
//

#ifndef CONCURRENTLOGGER_LOGGER_H
#define CONCURRENTLOGGER_LOGGER_H
#include "LogMessage.h"
#include <vector>
#include <atomic>
#include "ThreadSafeQueue.h"
#include <fstream>

class Logger {
public:
    // 获取单例实例（线程安全）
    static Logger & instance();

    // 核心日志接口：格式化并入队
    template<typename ...Args>
    void log(LogLevel level, const char * fmt, Args&& ... args);

    // 强制刷新队列中所有日志到文件
    void flush();

    // 设置日志级别，低于该级别的消息将被忽略
    void setLevel(LogLevel level);

    // 设置日志文件路径与滚动策略
    void configure(const std::string & pathPrefix,
                   size_t maxFileSize = 10 * 1024 * 1024,   // 默认 10 MB
                   bool dailyRolling  = false);
private:
    Logger();
    ~Logger();
    Logger(const Logger&) = delete;
    Logger & operator=(const Logger&) = delete;

    void workerThread();
    void writeBatch(const std::vector<LogMessage> & batch);
    void rotateFile(bool byDate = false);

private:
    // 内部状态
    LogLevel currentLevel_;     // 当前日志级别
    ThreadSafeQueue<LogMessage> queue_;    // 消息队列
    std::thread worker_;          // 日志线程
    std::atomic<bool> running_;

    std::string pathPrefix_;        // 文件路径
    size_t maxFileSize_;            // 文件最大容量
    bool dailyRolling_;             // 按天滚动标志
    std::ofstream currentFile_;     // 文件流
    std::mutex fileMutex;       // 保护文件句柄
};

template<typename ...Args>
void Logger::log(LogLevel level, const char *fmt, Args &&...args) {
    if (level < currentLevel_) return;
    {
        std::unique_lock<std::mutex> lk(fileMutex);
        if(!currentFile_.is_open()) {
            currentFile_.open(pathPrefix_ + ".log", std::ios::app);
        }
    }
    // 时间戳 + 线程 id
    auto now = std::chrono::system_clock::now();
    std::thread::id tid = std::this_thread::get_id();
    // 格式化文本
    char buf[1024];
    int length = std::snprintf(buf,sizeof(buf), fmt, std::forward<Args>(args)...);
    // 构造 LogMessage 并入队
    LogMessage msg{level, std::string(buf, length), now, tid};
    queue_.push(std::move(msg));
}

// 显式的实例化模板
template void Logger::log<>(LogLevel, const char *);

#endif //CONCURRENTLOGGER_LOGGER_H
