cmake_minimum_required(VERSION 3.27)
project(ConcurrentLogger)

set(CMAKE_CXX_STANDARD 17)

add_executable(ConcurrentLogger main.cpp
        ThreadSafeQueue.h
        Logger.cpp
        Logger.h
        LogLevel.h
        LogMessage.h)
