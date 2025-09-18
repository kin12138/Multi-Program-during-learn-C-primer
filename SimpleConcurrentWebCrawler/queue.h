//
// Created by libin on 2025/6/20.
//

#ifndef SIMPLECONCURRENTWEBCRAWLER_QUEUE_H
#define SIMPLECONCURRENTWEBCRAWLER_QUEUE_H

#include <mutex>
#include <condition_variable>
#include <queue>
#include <memory>
#include <stdexcept>

template<typename T>
class queue {
public:
    queue() = default;
    queue(const queue &);
    queue & operator=(const queue &) = delete;

    void push(T && new_value);
    bool wait_and_pop(T & value);
    std::shared_ptr<T> wait_and_pop();
    bool try_pop(T & value);
    std::shared_ptr<T> try_pop();

    bool empty() const;
    void close();
private:
    mutable std::mutex m;
    std::condition_variable cv;
    std::queue<T> data_queue;
    bool closed = false;
};

template<typename T>
queue<T>::queue(const queue<T> & other) {
    std::lock_guard<std::mutex> lk(other.m);
    data_queue = other.data_queue;
    closed = other.closed;
}

template<typename T>
void queue<T>::push(T &&new_value) {
    {
        std::lock_guard<std::mutex> lk(m);
        if (closed)
            throw std::runtime_error("push on closed queue");
        data_queue.push(std::forward<T>(new_value));
    }
    cv.notify_one();
}

template<typename T>
bool queue<T>::wait_and_pop(T &value) {
    std::unique_lock<std::mutex> lk(m);
    cv.wait(lk, [this] { return closed || !data_queue.empty(); });
    if (data_queue.empty())
        return false;
    value = std::move(data_queue.front());
    data_queue.pop();
    return true;
}

template<typename T>
std::shared_ptr<T> queue<T>::wait_and_pop() {
    std::unique_lock<std::mutex> lk(m);
    cv.wait(lk, [this] { return closed || !data_queue.empty(); });
    if (data_queue.empty())
        return std::make_shared<T>();
    auto res = std::make_shared<T>(std::move(data_queue.front()));
    data_queue.pop();
    return res;
}

template<typename T>
bool queue<T>::try_pop(T &value) {
    std::lock_guard<std::mutex> lk(m);
    if (data_queue.empty()) return false;
    value = std::move(data_queue.front());
    data_queue.pop();
    return true;
}

template<typename T>
std::shared_ptr<T> queue<T>::try_pop() {
    std::lock_guard<std::mutex> lk(m);
    if (data_queue.empty()) return std::make_shared<T>();
    auto res = std::make_shared<T>(std::move(data_queue.front()));
    data_queue.pop();
    return res;
}

template<typename T>
bool queue<T>::empty() const {
    std::lock_guard<std::mutex> lk(m);
    return data_queue.empty();
}

template<typename T>
void queue<T>::close() {
    {
        std::lock_guard<std::mutex> lk(m);
        closed = true;
    }
    cv.notify_all();
}

#endif //SIMPLECONCURRENTWEBCRAWLER_QUEUE_H
