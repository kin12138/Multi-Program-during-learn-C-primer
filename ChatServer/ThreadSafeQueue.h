//
// Created by libin on 2025/6/22.
//

#ifndef CHATSERVER_THREADSAFEQUEUE_H
#define CHATSERVER_THREADSAFEQUEUE_H

#include <queue>
#include <mutex>
#include <condition_variable>

template<typename T>
class queue {
public:
    queue() = default;
    queue(const queue &);
    queue & operator=(const queue &) = delete;

    template<typename U>
    void push(U && new_value) {
        {
            std::lock_guard<std::mutex> lk(m);
            data_queue.push(std::forward<U>(new_value));
        }
        cv.notify_one();
    }

    bool wait_and_pop(T & value);
    bool try_pop(T & value);
    bool empty() const;
    void close();
private:
    std::queue<T> data_queue;
    mutable std::mutex m;
    std::condition_variable cv;
    bool closed = false;
};

template<typename T>
queue<T>::queue(const queue<T> & other) {
    std::lock_guard<std::mutex> lk(other.m);
    data_queue = other.data_queue;
    closed = other.closed;
}

template<typename T>
bool queue<T>::wait_and_pop(T &value) {
    std::unique_lock<std::mutex> lk(m);
    cv.wait(lk, [this] { return closed || !data_queue.empty(); });
    if (data_queue.empty()) return false;
    value = std::move(data_queue.front());
    data_queue.pop();
    return true;
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

#endif //CHATSERVER_THREADSAFEQUEUE_H
