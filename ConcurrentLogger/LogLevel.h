//
// Created by libin on 2025/6/19.
//

#ifndef CONCURRENTLOGGER_LOGLEVEL_H
#define CONCURRENTLOGGER_LOGLEVEL_H

enum class LogLevel{ DEBUG, INFO,WARN, ERROR, FATAL };

inline const char* toString(LogLevel level) {
    switch (level) {
        case LogLevel::DEBUG : return "DEBUG";
        case LogLevel::INFO : return "INFO";
        case LogLevel::WARN : return "WARN";
        case LogLevel::ERROR : return "ERROR";
        case LogLevel::FATAL : return "FATAL";
        default:                return "UNKNOWN";
    }
}

#endif //CONCURRENTLOGGER_LOGLEVEL_H
