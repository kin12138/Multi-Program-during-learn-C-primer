cmake_minimum_required(VERSION 3.27)
project(ATM)

set(CMAKE_CXX_STANDARD 17)

add_executable(ATM main.cpp
        queue.h
        sender.h
        receiver.h
        dispatcher.h
        TemplateDispatcher.h
        message.h
        atm.h
        bank_machine.h
        interface_machine.h)
