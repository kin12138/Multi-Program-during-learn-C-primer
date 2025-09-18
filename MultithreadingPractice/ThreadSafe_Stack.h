//
// Created by libin on 2025/6/11.
//

#ifndef MULTITHREADINGPRACTICE_THREADSAFE_STACK_H
#define MULTITHREADINGPRACTICE_THREADSAFE_STACK_H
#include <exception>
#include <memory>
#include <mutex>
#include <stack>

struct empty_stack : std::exception{
    const char *what() const noexcept override {
        return "empty stack";
    }
};

template<typename T>
class ThreadSafe_Stack {
private:
    std::stack<T> data;
    mutable std::mutex m;
public:
    ThreadSafe_Stack() : data(std::stack<int> ()) { }

    ThreadSafe_Stack(const ThreadSafe_Stack & other) {
        std::lock_guard<std::mutex> lock(other.m);
        data = other.data;
    }

    ThreadSafe_Stack & operator=(const ThreadSafe_Stack &) = delete;

    void push(T new_value) {
        std::lock_guard<std::mutex> lock(m);
        data.push(new_value);
    }

    std::shared_ptr<T> pop() {
        std::lock_guard<std::mutex> lock(m);
        if (data.empty()) throw empty_stack();      // 在调用 pop() 前检查栈是否为空

        // 在修改堆栈前，分配出返回值
        std::shared_ptr<T> const ret(std::make_shared<T>(data.top()));
        data.pop();
        return ret;
    }

    void pop(T & value) {
        std::lock_guard<std::mutex> lock(m);
        if (data.empty()) throw empty_stack();

        value = data.top();
        data.pop();
    }

    bool empty() const {
        std::lock_guard<std::mutex> lock(m);
        return data.empty();
    }
};


#endif //MULTITHREADINGPRACTICE_THREADSAFE_STACK_H
