//
// Created by libin on 2025/6/23.
//

#ifndef CHATSERVER_LOGGER_H
#define CHATSERVER_LOGGER_H
#include <string>
#include <chrono>
#include <thread>
#include <atomic>
#include <fstream>
#include "ThreadSafeQueue.h"

enum class LogLevel { DEBUG, INFO, WARN, ERR, FATAL };
inline
const char * toString(LogLevel level) {
    switch (level) {
        case LogLevel::DEBUG    : return "DEBUG";
        case LogLevel::INFO     : return "INFO";
        case LogLevel::WARN     : return "WARN";
        case LogLevel::ERR    : return "ERROR";
        case LogLevel::FATAL    : return "FATAL";
        default:                  return "UNKNOWN";
    }
}

struct LogMessage{
    LogLevel                                level_;
    std::string                             text_;
    std::chrono::system_clock::time_point   timeStamp_;
    std::thread::id                         threadId_;
};


class Logger {
public:
    static Logger & instance();     // 获取单例
    template<typename ...Args>
    void log(LogLevel level,
             const char * fmt,
             Args&& ...args);       // 格式化并入队
    void flush();                   // 强制刷新队列中所有日志到文件
    void setLevel(LogLevel level);  // 设置日志级别, 低于该级别的消息将被忽略
    void configure(const std::string & pathPrefix,
                   size_t maxFileSize = 10 * 1024 * 1024,/* 默认 10MB*/
                   bool dailyRolling = false);

private:
    Logger();
    ~Logger();
    Logger(const Logger &) = delete;
    Logger & operator=(const Logger &) = delete;

    void wordThread();
    void writeBatch(const std::vector<LogMessage> & batch);
    void rotateFile(bool byDate = false);
private:
    // 内部状态
    LogLevel            currentLevel_;      // 当前日志等级
    queue<LogMessage>   logQueue_;          // 日志消息队列
    std::thread         logWorker_;         // 日志线程
    std::atomic<bool>   running_;           // 日志系统运行标志

    std::string         pathPrefix_;        // 文件路径
    size_t              maxFileSize_;       // 文件最大容量
    bool                dailyRolling_;      // 按天滚动标志
    std::ofstream       currentFile_;       // 当前文件流
    std::mutex          fileMutex_;         // 保护文件句柄
};

template<typename ...Args>
void Logger::log(LogLevel level, const char *fmt, Args &&...args) {
    if (level < currentLevel_) return;
    {
        std::lock_guard<std::mutex> lk(fileMutex_);
        if (!currentFile_.is_open())
            currentFile_.open(pathPrefix_ + ".log", std::ios::app);
    }

    // 时间戳 + 线程 id
    auto now = std::chrono::system_clock::now();
    std::thread::id tid = std::this_thread::get_id();
    //格式化文本
    char buf[1024];
    int length = std::snprintf(buf, sizeof(buf), fmt, std::forward<Args>(args)...);
    // 构造 LogMessage 并入队
    LogMessage msg{level, std::string(buf, length), now, tid};
    logQueue_.push(msg);
}


#endif //CHATSERVER_LOGGER_H
