//
// Created by libin on 2025/6/19.
//

#ifndef CONCURRENTLOGGER_THREADSAFEQUEUE_H
#define CONCURRENTLOGGER_THREADSAFEQUEUE_H

#include <mutex>
#include <condition_variable>
#include <memory>
#include <queue>
#include <stdexcept>

template<typename T>
class ThreadSafeQueue {
public:
    ThreadSafeQueue() = default;
    ThreadSafeQueue(const ThreadSafeQueue &);
    ThreadSafeQueue & operator=(const ThreadSafeQueue &) = delete;

    void push(T && new_value);

    bool wait_and_pop(T & value);
    std::shared_ptr<T> wait_and_pop();

    bool try_pop(T & value);
    std::shared_ptr<T> try_pop();

    bool empty() const;
    void close();
private:
    mutable std::mutex mutex;
    std::condition_variable cond;
    std::queue<T> data_queue;
    bool closed = false;
};

template<typename T>
ThreadSafeQueue<T>::ThreadSafeQueue(const ThreadSafeQueue<T> & other) {
    std::lock_guard<std::mutex> lk(other.mutex);
    data_queue = other.data_queue;
    closed = other.closed;
}

template<typename T>
void ThreadSafeQueue<T>::push(T &&new_value) {
    {
        std::unique_lock<std::mutex> lk(mutex);
        if(closed)
            throw std::runtime_error("push on closed queue");
        data_queue.push(std::forward<T>(new_value));
    }
    cond.notify_one();
}

template<typename T>
bool ThreadSafeQueue<T>::wait_and_pop(T &value) {
    std::unique_lock<std::mutex> lk(mutex);
    cond.wait(lk, [this] { return closed || !data_queue.empty();});
    if (data_queue.empty())
        return false;
    value = std::move(data_queue.front());
    data_queue.pop();
    return true;
}

template<typename T>
std::shared_ptr<T> ThreadSafeQueue<T>::wait_and_pop() {
    std::lock_guard<std::mutex> lk(mutex);
    cond.wait(lk, [this] { return closed || !data_queue.empty(); });
    auto res = std::make_shared<T>(std::move(data_queue.front()));
    data_queue.pop();
    return res;
}

template<typename T>
bool ThreadSafeQueue<T>::try_pop(T &value) {
    std::lock_guard<std::mutex> lk(mutex);
    if (data_queue.empty()) return false;
    value = std::move(data_queue.front());
    data_queue.pop();
    return true;
}

template<typename T>
std::shared_ptr<T> ThreadSafeQueue<T>::try_pop() {
    std::lock_guard<std::mutex> lk(mutex);
    if (data_queue.empty()) return std::make_shared<T>();
    auto res = std::make_shared<T>(std::move(data_queue.front()));
    data_queue.pop();
    return res;
}

template<typename T>
bool ThreadSafeQueue<T>::empty() const {
    std::lock_guard<std::mutex> lk(mutex);
    return data_queue.empty();
}

template <typename T>
void ThreadSafeQueue<T>::close() {
    {
        std::lock_guard<std::mutex> lk(mutex);
        closed = true;
    }
    cond.notify_all();
}
#endif //CONCURRENTLOGGER_THREADSAFEQUEUE_H
