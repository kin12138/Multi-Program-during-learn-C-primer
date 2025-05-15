//
// Created by libin on 2025/5/13.
//

#ifndef MESSAGESEND_IMESSAGESENDER_H
#define MESSAGESEND_IMESSAGESENDER_H
#include <string>
#include <iostream>

/* 抽象基类 高层模块定义*/
class IMessageSender {
public:
    virtual void send(const std::string & recipient, const std::string & contents) = 0;
    virtual ~IMessageSender() = default;
};


#endif //MESSAGESEND_IMESSAGESENDER_H
