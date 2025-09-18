//
// Created by libin on 2025/6/16.
//

#ifndef ATM_QUEUE_H
#define ATM_QUEUE_H
#include <mutex>
#include <condition_variable>
#include <queue>
#include <memory>

namespace messaging{
    /* 队列项的基础类*/
    struct message_base {
        virtual ~message_base() = default;
    };

    template<typename Msg>
    struct wrapped_message : message_base {     // 每个消息类型都需要特化
        Msg contents;
        explicit wrapped_message(Msg const & contents_) :
                    contents(contents_) { }
    };


    class queue {
        std::mutex m;
        std::condition_variable c;
        std::queue<std::shared_ptr<message_base>> q;        // 实际存储指向 message_base 类指针的队列

    public:
        template<typename T>
        void push(T const & msg) {
            std::lock_guard<std::mutex> lk(m);
            q.push(std::make_shared<wrapped_message<T>>(msg));
            c.notify_all();
        }

        std::shared_ptr<message_base> wait_and_pop() {
            std::unique_lock<std::mutex> lk(m);
            c.wait(lk, [&]{return !q.empty(); });       // 当队列为空时阻塞
            auto res = q.front();
            q.pop();
            return res;
        }
    };

}
#endif //ATM_QUEUE_H
