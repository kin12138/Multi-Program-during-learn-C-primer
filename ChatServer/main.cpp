#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include "Server.h"
#include "Logger.h"

int main() {
    // 初始化日志系统
    Logger::instance().configure("../Resource/app_log", 1024*1024, false);
    // 初始化 WinSock2 库
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        std::cerr << "WSAStartup failed\n";
        return 1;
    }
    Logger::instance().log(LogLevel::INFO, "Server starting on port %d", 23);
    // 启动服务器
    try {
        Server server(23);
        server.run();
    } catch (const std::exception & e) {
        Logger::instance().log(LogLevel::ERR, "Fatal: %s", e.what());
    }

    // 清理 Winsock
    WSACleanup();
    return 0;
}
