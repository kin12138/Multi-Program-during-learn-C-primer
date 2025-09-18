//
// Created by libin on 2025/6/16.
//

#ifndef ATM_SENDER_H
#define ATM_SENDER_H
#include "queue.h"

namespace messaging {
    class sender{
        queue *q;   // sender 是一个队列指针的包装类
    public:
        sender() :  // sender 无队列，默认构造函数
            q(nullptr) { }

        explicit sender(queue *q_) :        // 从指向队列的指针进行构造
                q(q_) { }

        template<typename Message>
        void send(Message const & msg) {
            if(q)
                q->push(msg);       // 将发送消息推送给队列
        }
    };
}
#endif //ATM_SENDER_H
