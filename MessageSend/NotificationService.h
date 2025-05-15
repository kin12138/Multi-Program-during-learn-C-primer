//
// Created by libin on 2025/5/13.
//

#ifndef MESSAGESEND_NOTIFICATIONSERVICE_H
#define MESSAGESEND_NOTIFICATIONSERVICE_H
#include <memory>
#include "IMessageSender.h"

class NotificationService {
public:
    NotificationService(std::unique_ptr<IMessageSender> s) : sender_(std::move(s))  { }
    void notify(const std::string & user, const std::string & msg){
        // 仅依赖抽象接口，无需关心具体实现
        sender_->send(user, msg);
    }
private:
    std::unique_ptr<IMessageSender> sender_;
};


#endif //MESSAGESEND_NOTIFICATIONSERVICE_H
