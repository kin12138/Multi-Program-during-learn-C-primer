//
// Created by libin on 2025/6/13.
//

#ifndef MULTITHREADINGPRACTICE_THREADSAFE_QUEUE_H
#define MULTITHREADINGPRACTICE_THREADSAFE_QUEUE_H
#include <mutex>
#include <condition_variable>
#include <queue>
#include <memory>

template<typename T>
class threadsafe_queue {
public:
    threadsafe_queue() = default;
    threadsafe_queue(const threadsafe_queue &);
    threadsafe_queue & operator=(const threadsafe_queue&) = delete;

    void push(T new_value);

    bool try_pop(T & value);
    std::shared_ptr<T> try_pop();

    void wait_for_pop(T & value);
    std::shared_ptr<T> wait_for_pop() ;

    bool empty() const;

private:
    std::queue<T> data_queue;
    mutable std::mutex mut;
    std::condition_variable data_cond;
};


#endif //MULTITHREADINGPRACTICE_THREADSAFE_QUEUE_H
