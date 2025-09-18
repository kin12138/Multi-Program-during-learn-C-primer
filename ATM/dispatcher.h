//
// Created by libin on 2025/6/16.
//

#ifndef ATM_DISPATCHER_H
#define ATM_DISPATCHER_H

#include "queue.h"
#include "TemplateDispatcher.h"

namespace messaging {
//    template<typename Dispatcher, typename Msg, typename Func>
//    class TemplateDispatcher;
    
    class close_queue {};       // 用于关闭队列的消息

    class dispatcher {
        queue *q;
        bool chained;

        dispatcher(const dispatcher &) = delete;
        dispatcher & operator=(const dispatcher &) = delete;

        template<typename Dispatcher, typename Msg, typename Func>
        friend class TemplateDispatcher;        // 允许 TemplateDispatcher 实例访问内部成员

        void wait_and_dispatch() {
            for(;;) {  // 循环，等待调度消息
                auto msg = q->wait_and_pop();
                dispatch(msg);
            }
        }

        // dispatch() 会检查 close_queue 消息，然后抛出
        bool dispatch(std::shared_ptr<message_base> const & msg) {
            if (dynamic_cast<wrapped_message<close_queue>*> (msg.get())){
                throw close_queue();
            }
            return false;
        }

    public:
        // dispatcher 实例可以移动
        dispatcher(dispatcher && other) :
                q(other.q), chained(other.chained) {
            other.chained = true;       // 源不能等待消息
        }

        explicit dispatcher(queue *q_) :
                q(q_), chained(false) { }

        /* 使用 TemplateDispatcher 处理指定类型的消息 */
        template<typename Message, typename Func>
        TemplateDispatcher<dispatcher, Message, Func>
        handle(Func &&f) {
            return TemplateDispatcher<dispatcher, Message, Func> (
                    q, this, std::forward<Func>(f)
                    );
        }

        // 析构函数可能会抛出异常
        ~dispatcher() noexcept(false) {
            if (!chained)
                wait_and_dispatch();
        }
    };
}
#endif //ATM_DISPATCHER_H
