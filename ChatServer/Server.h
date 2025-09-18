//
// Created by libin on 2025/6/23.
//

#ifndef CHATSERVER_SERVER_H
#define CHATSERVER_SERVER_H
#include "Dispatcher.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <atomic>


class Server {
public:
    explicit Server(uint16_t port);
    ~Server();

    // 阻塞运行服务器
    void run();

    // 打印客户端信息
    static void printClientInfoToFile(SOCKET clientSock);
private:
    void acceptLoop();
private:
    SOCKET              listenSock_;
    Dispatcher          dispatcher_;
    std::atomic<bool>   running_{true};
};


#endif //CHATSERVER_SERVER_H
