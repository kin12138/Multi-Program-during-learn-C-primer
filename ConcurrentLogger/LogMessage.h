//
// Created by libin on 2025/6/19.
//

#ifndef CONCURRENTLOGGER_LOGMESSAGE_H
#define CONCURRENTLOGGER_LOGMESSAGE_H
#include "LogLevel.h"
#include <string>
#include <chrono>
#include <thread>

struct LogMessage {
    LogLevel level;
    std::string text;
    std::chrono::system_clock::time_point timeStamp;
    std::thread::id threadID;
};

#endif //CONCURRENTLOGGER_LOGMESSAGE_H
