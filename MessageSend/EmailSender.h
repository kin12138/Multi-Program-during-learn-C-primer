//
// Created by libin on 2025/5/13.
//

#ifndef MESSAGESEND_EMAILSENDER_H
#define MESSAGESEND_EMAILSENDER_H
#include "IMessageSender.h"

/* 低层模块实现：邮件发送*/
class EmailSender : public IMessageSender {
public:
    void send(const std::string & recipient, const std::string & contents) override {
        std::cout << "Email to " << recipient << ": " << contents << std::endl;
    }
};


#endif //MESSAGESEND_EMAILSENDER_H
