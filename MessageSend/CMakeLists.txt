cmake_minimum_required(VERSION 3.27)
project(MessageSend)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "-g")

add_executable(MessageSend main.cpp
        IMessageSender.h
        EmailSender.cpp
        EmailSender.h
        SmsSender.cpp
        SmsSender.h
        NotificationService.cpp
        NotificationService.h
        Test.h)

add_compile_options(-g)