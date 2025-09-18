//
// Created by libin on 2025/6/22.
//

#include "Session.h"
#include "Dispatcher.h"
#include "Logger.h"

void Session::readLoop() {
    char buf[1024];
    while (running_) {
        int n = recv(sock_, buf, sizeof(buf) - 1, 0);
        if (n <= 0) break;  // 客户端断开或出错
        buf[n] = '\0';
        Logger::instance().log(LogLevel::DEBUG,
                               "Received from [%u]: %s",
                               static_cast<unsigned>(sock_), buf);
        dispatcher_.broadcast(buf, shared_from_this());
    }
    Logger::instance().log(LogLevel::INFO,
                           "Session %u disconnected", static_cast<unsigned>(sock_));
    dispatcher_.leave(shared_from_this());
}

void Session::writeLoop() {
    std::string msg;
    while(inbox_.wait_and_pop(msg)) {
        send(sock_, msg.data(), (int)msg.size(), 0);
        Logger::instance().log(LogLevel::DEBUG,
                               "Sent to [%u]: %s", static_cast<unsigned>(sock_), msg.c_str());
    }
}

Session::~Session() {
    running_ = false;
    inbox_.close();
    if (readThr_.joinable()) readThr_.join();
    if (writeThr_.joinable()) writeThr_.join();
    closesocket(sock_);
}