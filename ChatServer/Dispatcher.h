//
// Created by libin on 2025/6/22.
//

#ifndef CHATSERVER_DISPATCHER_H
#define CHATSERVER_DISPATCHER_H

#include <set>
#include <mutex>
#include <memory>
#include <string>

class Session;

class Dispatcher {
public:
    // 新客户端加入
    void join(std::shared_ptr<Session> sess);
    // 客户端离开
    void leave(std::shared_ptr<Session> sess);
    // 广播消息给除发送者之外的所有客户端
    void broadcast(const std::string &, std::shared_ptr<Session> from);

private:
    std::mutex m_;
    std::set<std::shared_ptr<Session>> sessions_;
};


#endif //CHATSERVER_DISPATCHER_H
