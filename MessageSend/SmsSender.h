//
// Created by libin on 2025/5/13.
//

#ifndef MESSAGESEND_SMSSENDER_H
#define MESSAGESEND_SMSSENDER_H
#include "IMessageSender.h"

/* 低层模块实现，短信发送*/
class SmsSender : public IMessageSender{
public:
    void send(const std::string & recipient, const std::string & contents) override {
        std::cout << "SMS to " << recipient << ": " << contents << std::endl;
    }
};


#endif //MESSAGESEND_SMSSENDER_H
