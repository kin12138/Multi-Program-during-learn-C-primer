//
// Created by libin on 2025/6/16.
//

#ifndef ATM_TEMPLATEDISPATCHER_H
#define ATM_TEMPLATEDISPATCHER_H

#include "queue.h"

namespace messaging {
    template<typename PreviousDispatcher, typename Msg, typename Func>
    class TemplateDispatcher {
        queue *q;
        PreviousDispatcher *prev;
        Func f;
        bool chained;

        TemplateDispatcher(TemplateDispatcher const &) = delete;
        TemplateDispatcher & operator=(TemplateDispatcher const &) = delete;

        /* 所有特化的 TemplateDispatcher 类型实例都是友元类 */
        template<typename Dispatcher, typename OtherMsg, typename OtherFunc>
        friend class TemplateDispatcher;

        void wait_and_dispatch() {
            for(;;) {
                auto msg = q->wait_and_pop();
                if (dispatch(msg))
                    break;
            }
        }

        bool dispatch(std::shared_ptr<message_base> const & msg) {
            if (wrapped_message<Msg>* wrapper =
                    dynamic_cast<wrapped_message<Msg>*> (msg.get())) {  // 检查消息类型，并且调用函数
                f(wrapper->contents);
                return true;
            } else {
                return prev->dispatch(msg);     // 链接到之前的调度器上
            }
        }

    public:
        TemplateDispatcher(TemplateDispatcher && other) :
                q(other.q), prev(other.prev), f(std::move(other.f)),
                chained(other.chained) {
            other.chained = true;
        }

        TemplateDispatcher(queue *q_, PreviousDispatcher *prev_, Func && f_) :
                q(q_), prev(prev_), f(std::forward<Func>(f_)), chained(false) {
            prev_->chained = true;
        }

        template<typename OtherMsg, typename OtherFunc>
        TemplateDispatcher<TemplateDispatcher, OtherMsg, OtherFunc>
        handle(OtherFunc && of) {       // 可以链接到其他处理器
            return TemplateDispatcher<TemplateDispatcher, OtherMsg, OtherFunc> (
                    q, this, std::forward<OtherFunc>(of)
                    );
        }

        ~TemplateDispatcher() noexcept(false) {
            if (!chained)
                wait_and_dispatch();
        }
    };
}

#endif //ATM_TEMPLATEDISPATCHER_H
