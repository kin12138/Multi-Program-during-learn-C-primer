//
// Created by libin on 2025/5/13.
//

#ifndef MESSAGESEND_TEST_H
#define MESSAGESEND_TEST_H
#include "EmailSender.h"
#include "NotificationService.h"

void test() {
    // 将具体实现注入到高层模块中
    auto es = std::unique_ptr<EmailSender> (new EmailSender());
    std::unique_ptr<NotificationService> service(new NotificationService(std::move(es)));
    service->notify("alice@example.com", "Your order has shipped!");
}

#endif //MESSAGESEND_TEST_H
