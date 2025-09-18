//
// Created by libin on 2025/6/10.
//

#ifndef MULTITHREADINGPRACTICE_SCOPED_THREAD_H
#define MULTITHREADINGPRACTICE_SCOPED_THREAD_H
#include <thread>
#include <stdexcept>

class Scoped_Thread {
public:
    explicit Scoped_Thread(std::thread t) : t_(std::move(t)){
        if(!t_.joinable())
            throw std::logic_error("No thread");
    }

    ~Scoped_Thread(){
        t_.join();
    }
    Scoped_Thread(const Scoped_Thread&) = delete;
    Scoped_Thread & operator=(const Scoped_Thread &) = delete;
private:
    std::thread  t_;
};
#endif //MULTITHREADINGPRACTICE_SCOPED_THREAD_H
