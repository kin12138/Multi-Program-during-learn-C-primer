//
// Created by libin on 2025/6/23.
//

#include "Server.h"
#include "Session.h"
#include <iostream>
#include "Logger.h"

Server::Server(uint16_t port) {
    listenSock_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listenSock_ == INVALID_SOCKET)
        throw std::runtime_error("socket() failed");
    u_long yes = 1;
    setsockopt(listenSock_, SOL_SOCKET, SO_REUSEADDR, (char*)&yes, sizeof(yes));

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);

    if (bind(listenSock_, (sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR ||
        listen(listenSock_, SOMAXCONN) == SOCKET_ERROR) {
        closesocket(listenSock_);
        throw std::runtime_error("bind/listen failed");
    }
    Logger::instance().log(LogLevel::INFO, "bind/listen...");
}

Server::~Server() {
    running_ = false;
    closesocket(listenSock_);
}

void Server::run() {
    std::cout << "Server running, waiting connections...\n";
    acceptLoop();
}

void Server::acceptLoop() {
    while (running_){
        sockaddr_in cli{};
        int len = sizeof(cli);
        SOCKET client = accept(listenSock_, (sockaddr*)&cli, &len);
        if (client == INVALID_SOCKET) continue;
        // 获取客户端地址
        char ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &cli.sin_addr, ip, sizeof(ip));
        int port = ntohs(cli.sin_port);
        Logger::instance().log(LogLevel::INFO,
                               "New connection from %s:%d", ip, port);

        auto sess = std::make_shared<Session>(client, dispatcher_);
        dispatcher_.join(sess);
        sess->start();
    }
}

void Server::printClientInfoToFile(SOCKET clientSock) {
    // 获取远端地址和端口
    sockaddr_storage addr;
    int addrLen = sizeof(addr);

    // 获取对端地址
    if(getpeername(clientSock, (sockaddr*)&addr, &addrLen) == SOCKET_ERROR) {
        std::cerr  << "getpeername failed: " << WSAGetLastError() << "\n";
        return;
    }
    // 根据地址族分别处理
    char host[NI_MAXHOST], service[NI_MAXSERV];
    int rc = getnameinfo((sockaddr*)&addr, addrLen,
                         host, sizeof(host),
                         service, sizeof(service),
                         NI_NUMERICHOST | NI_NUMERICSERV );
    if (rc != 0){
        std::cerr << "getnameinfo failed: " << rc << "\n";
    }
    Logger::instance().log(LogLevel::INFO, "Client connect from %s : %s",host,service);
}