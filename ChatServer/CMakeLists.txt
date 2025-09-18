cmake_minimum_required(VERSION 3.27)
project(ChatServer)

set(CMAKE_CXX_STANDARD 17)

add_executable(ChatServer main.cpp
        ThreadSafeQueue.h
        Dispatcher.cpp
        Dispatcher.h
        Session.cpp
        Session.h
        Server.cpp
        Server.h
        Logger.cpp
        Logger.h)

if (WIN32)
    target_link_libraries(ChatServer PRIVATE Ws2_32)
endif ()
