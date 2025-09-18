//
// Created by libin on 2025/6/16.
//

#ifndef ATM_RECEIVER_H
#define ATM_RECEIVER_H
#include "queue.h"
#include "sender.h"
#include "dispatcher.h"

namespace messaging {
    class receiver {
        queue q;        // 接收者拥有对应队列
    public:
        operator sender() {     // 允许将类中队列隐式转换为 sender 队列
            return sender(&q);
        }

        dispatcher wait() {     // 等待对队列进行调度
            return dispatcher(&q);
        }
    };
}

#endif //ATM_RECEIVER_H
