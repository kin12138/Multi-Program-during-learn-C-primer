//
// Created by libin on 2025/6/23.
//

#include "Logger.h"
#include <vector>

Logger & Logger::instance() {
    static Logger init;
    return init;
}

Logger::Logger() :
            currentLevel_(LogLevel::DEBUG),
            running_(true),
            maxFileSize_( 10 * 1024 * 1024 /* 10MB */),
            dailyRolling_(false)
{
    logWorker_ = std::thread(&Logger::wordThread, this);
}

Logger::~Logger() {
    running_.store(false);
    logQueue_.close();
    if (logWorker_.joinable()) logWorker_.join();
    // 刷新并关闭文件
    std::lock_guard<std::mutex> lk(fileMutex_);
    currentFile_.flush();
    currentFile_.close();
}

void Logger::wordThread() {
    std::vector<LogMessage> batch;
    batch.reserve(64);
    while (running_ || !logQueue_.empty()) {
        LogMessage msg;
        if (logQueue_.wait_and_pop(msg))
            batch.push_back(std::move(msg));
        // 如果队列为空，或批量已达阈值，则写盘
        if (batch.size() >= 5 || (!running_ && !logQueue_.empty())) {
            writeBatch(batch);
            batch.clear();
        }
    }
}

void Logger::writeBatch(const std::vector<LogMessage> &batch) {
    std::lock_guard<std::mutex> lk(fileMutex_);
    for(auto & msg : batch) {
        // 格式 YYYY-MM-DD HH:MM:SS [Level] [Tid] text\n
        auto t = std::chrono::system_clock::to_time_t(msg.timeStamp_);
        char timebuf[32];
        std::strftime(timebuf, sizeof(timebuf), "%Y-%m-%d %H:%M:%S", std::localtime(&t));
        currentFile_ << timebuf
                     << " [" << toString(msg.level_) << "]"
                     << " [" << msg.threadId_ << "] "
                     << msg.text_ << "\n";
    }

    currentFile_.flush();
    // 按大小滚动
    if (currentFile_.tellp() > static_cast<std::streamoff> (maxFileSize_))
        rotateFile();
    // 按日期滚动
    if (dailyRolling_)
        rotateFile(true);
}

void Logger::rotateFile(bool byDate) {
    // 关闭当前文件，重命名打开新文件
    currentFile_.close();
    std::string new_name = pathPrefix_;
    if (byDate) {
        auto now = std::chrono::system_clock::now();
        auto tt = std::chrono::system_clock::to_time_t(now);
        char buf[16];
        std::strftime(buf, sizeof(buf), "%Y%m%d", std::localtime(&tt));
        new_name += "_" + std::string(buf) + ".log";
    } else {
        static int idx = 0;
        new_name += "_" + std::to_string(++idx) + ".log";
    }
    std::rename((pathPrefix_+".log").c_str(), new_name.c_str());
    currentFile_.open(pathPrefix_ + ".log", std::ios::trunc);
}

void Logger::flush() {
    // 等待队列清空
    while (!logQueue_.empty())  std::this_thread::sleep_for(std::chrono::milliseconds(10));
    // 刷新文件
    std::lock_guard<std::mutex> lk(fileMutex_);
    currentFile_.flush();
}

void Logger::setLevel(LogLevel level) {
    currentLevel_ = level;
}

void Logger::configure(const std::string &pathPrefix, size_t maxFileSize, bool dailyRolling) {
    pathPrefix_ = pathPrefix;
    maxFileSize_ = maxFileSize;
    dailyRolling_ = dailyRolling;
}