//
// Created by libin on 2025/6/18.
//

#ifndef THREADPOOL_THREADSAFEQUEUE_H
#define THREADPOOL_THREADSAFEQUEUE_H
#include <mutex>
#include <queue>
#include <condition_variable>
#include <memory>
#include <iostream>

template<typename T>
class ThreadSafeQueue {
public:
    ThreadSafeQueue() = default;
    ThreadSafeQueue(const ThreadSafeQueue &);
    ThreadSafeQueue & operator=(const ThreadSafeQueue & ) = delete;

    void push(T && new_value);

    bool try_pop(T & value);
    std::shared_ptr<T> try_pop();

    bool wait_and_pop(T & value);
    std::shared_ptr<T> wait_and_pop();

    bool empty() const;

    void close();
private:
    mutable std::mutex m;
    std::condition_variable cv;
    std::queue<T> data_queue;
    bool closed = false;
};

template<typename T>
ThreadSafeQueue<T>::ThreadSafeQueue(const ThreadSafeQueue<T> & other) {
    std::lock_guard<std::mutex> lk(other.m);
    data_queue = other.data_queue;
    closed = other.closed;
}

template<typename T>
void ThreadSafeQueue<T>::push(T && new_value) {
//    std::cerr << "[TSQ] push(): trying to lock\n";
    std::unique_lock<std::mutex> lk(m);
//    std::cerr << "[TSQ] push(): locked, closed=" << closed
//              << ", queue_size=" << data_queue.size() << "\n";
    if (closed) {
//        std::cerr << "[TSQ] push(): queue closed, throwing\n";
        throw std::runtime_error("push on closed queue");
    }
    data_queue.push(std::forward<T>(new_value));
//    std::cerr << "[TSQ] push(): pushed, new size=" << data_queue.size() << "\n";

    lk.unlock();
    cv.notify_one();
//    std::cerr << "[TSQ] push(): notify_one done\n";
}

template<typename T>
std::shared_ptr<T> ThreadSafeQueue<T>::wait_and_pop() {
    std::unique_lock<std::mutex> lk(m);
    cv.wait(lk, [this] { return closed || !data_queue->empty(); });
    auto res = std::make_shared<T>(data_queue.front());
    data_queue.pop();
    return res;
}

template<typename T>
bool ThreadSafeQueue<T>::wait_and_pop(T &value) {
    std::unique_lock<std::mutex> lk(m);
//    std::cerr << "[Queue] Thread " << std::this_thread::get_id()
//              << " entering wait, closed = " << (closed ? " ture " : " false ")
//              << "size = " << data_queue.size() << "\n";
    cv.wait(lk, [this] { return closed || !data_queue.empty(); });
//    std::cerr << "[Queue] Thread " << std::this_thread::get_id()
//              << "woke up, closed = " << (closed ? " ture " : " false ")
//              << "size = " << data_queue.size() << "\n";
    if (data_queue.empty()) return false;
    value = std::move(data_queue.front());
    data_queue.pop();
    return true;
}

template <typename T>
bool ThreadSafeQueue<T>::try_pop(T &value) {
    std::unique_lock<std::mutex> lk(m);
    if (data_queue.empty()) return false;
    value = data_queue.front();
    data_queue.pop();
    return true;
}

template<typename T>
std::shared_ptr<T> ThreadSafeQueue<T>::try_pop() {
    std::unique_lock<std::mutex> lk(m);
    if (data_queue.empty())
        return std::make_shared<T>();
    std::shared_ptr<T> res(std::make_shared<T>(data_queue.front()));
    data_queue.pop();
    return res;
}

template <typename T>
bool ThreadSafeQueue<T>::empty() const {
    std::lock_guard<std::mutex> lk(m);
    return data_queue.empty();
}

template<typename T>
void ThreadSafeQueue<T>::close() {
    std::unique_lock<std::mutex> lk(m);
    closed = true;
    lk.unlock();
    cv.notify_all();
}

#endif //THREADPOOL_THREADSAFEQUEUE_H
