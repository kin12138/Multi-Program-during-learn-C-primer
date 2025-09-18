//
// Created by libin on 2025/6/22.
//

#ifndef CHATSERVER_SESSION_H
#define CHATSERVER_SESSION_H
#include "ThreadSafeQueue.h"
#include <thread>
#include <atomic>
#include <memory>
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>

class Dispatcher;

class Session : public std::enable_shared_from_this<Session> {
public:
    Session(SOCKET clientSock, Dispatcher & disp) :
            sock_(clientSock), dispatcher_(disp) { }
    ~Session();

    // 启动读写线程
    void start() {
        readThr_ = std::thread(&Session::readLoop, this);
        writeThr_ = std::thread(&Session::writeLoop, this);
    }

    // 将外部消息推入此 session 的发送队列
    void deliver(const std::string & msg) {
        inbox_.push(msg);
    }
private:
    void readLoop();
    void writeLoop();
private:
    SOCKET              sock_;
    Dispatcher          &dispatcher_;
    queue<std::string>  inbox_;         // 每个 session 自己的发送队列
    std::thread         readThr_;
    std::thread         writeThr_;
    std::atomic<bool>   running_{true};
};


#endif //CHATSERVER_SESSION_H
