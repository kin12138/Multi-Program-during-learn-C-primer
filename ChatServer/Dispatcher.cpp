//
// Created by libin on 2025/6/22.
//

#include "Dispatcher.h"
#include "Session.h"

// 新客户端加入
void Dispatcher::join(std::shared_ptr<Session> sess) {
    std::lock_guard<std::mutex> lk(m_);
    sessions_.insert(sess);
}

// 客户端离开
void Dispatcher::leave(std::shared_ptr<Session> sess) {
    std::lock_guard<std::mutex> lk(m_);
    sessions_.erase(sess);
}

// 广播消息给除发送者之外的所有客户端
void Dispatcher::broadcast(const std::string & msg, std::shared_ptr<Session> from) {
    std::lock_guard<std::mutex> lk(m_);
    for (auto & s : sessions_) {
        if (s != from) s->deliver(msg);
    }
}