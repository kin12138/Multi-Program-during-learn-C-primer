//
// Created by libin on 2025/6/5.
//

#ifndef MULTITHREADINGPRACTICE_THREADBASICS_H
#define MULTITHREADINGPRACTICE_THREADBASICS_H

#include <thread>
#include <iostream>
#include <vector>
#include <atomic>
#include <chrono>
#include <ctime>
#include "TaskQueue.h"

void print_hello() {
    std::cout << "Hello from thread!" << std::endl;
}

void test_thread() {
    std::thread t(print_hello);
    t.join();
    std::cout << "main thread ends." << std::endl;
}

struct func {
    int &i_;
    func(int & i) : i_(i) { }
    void operator()() {
        for (unsigned j = 0; j < 100000; ++j)
            // do something
            ++i_;       // Ǳ�ڷ�����������������
    }
};

void oops() {
    int some_local_state = 0;
    func my_func(some_local_state);
    std::thread my_thread(my_func);
    my_thread.detach();     // �����߳̽���
}                           // ���߳̿��ܻ�������


void f() {
    int some_local_state = 0;
    func my_func(some_local_state);
    std::thread t(my_func);
    try {
        // do_something
    }
    catch (...)
    {
        t.join();
        throw;
    }
    t.join();
}

class thread_guard {
    std::thread & t_;
public:
    explicit thread_guard(std::thread & t) : t_(t) { }
    ~thread_guard() {
        if (t_.joinable())
            t_.join();
    }
    thread_guard(const thread_guard &) = delete;
    thread_guard & operator=(thread_guard &) = delete;
};

struct func;
void f2() {
    int some_local_state = 0;
    func my_func(some_local_state);
    std::thread t(my_func);
    // do something in current threading
}

void hello() {
    std::cout << "Hello from thread, ID = "
              << std::this_thread::get_id()
              << std::endl;
}

void fib_range(int start, int count) {
    long long a = 0, b = 1;
    for (int i = 0; i < start + count; ++i) {
        long long next = a + b;
        a = b;
        b = next;
        if (i >= start)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            std::cout << "Thread " << std::this_thread::get_id()
                      << " computes Fib(" << i << ") = " << a << std::endl;
        }
    }
}

void main_thread() {
    const int num_threads = 4;
    const int per_thread = 5;
    std::vector<std::thread> threads;

    // ���� 4 ���̣߳��ֱ���㲻ͬ����
    for (int i = 0; i < num_threads; ++i) {
        int start_index = i * per_thread;
        threads.emplace_back(fib_range, start_index, per_thread);
    }

    // �ȴ������߳�ִ�н���
    for(auto & t : threads) {
        if (t.joinable()) {
            t.join();
        }
    }
}

void work_with_join() {
    std::cout << "[���߳�] ��ʼִ�У�ID = " << std::this_thread::get_id() << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    std::cout << "[���߳�] ����ִ��\n";
}

void main_work_with_join() {
    std::cout << "[���߳�] �������̲߳��ȴ��������\n";
    std::thread t(work_with_join);

    if (t.joinable())
        t.join();

    std::cout << "[���߳�] ���߳��Ѿ���ɣ�����ִ�У������˳�\n";
}

void work_with_detach() {
    std::cout << "[���߳�](�ػ�) ��ʼִ�У�ID = " << std::this_thread::get_id() << std::endl;
//    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << "[���߳�](�ػ�) ����ִ��\n";
}

void main_work_with_detach() {
    std::cout << "[���߳�] �������̲߳� detach\n";
    std::thread t(work_with_detach);
    if(t.joinable())
        t.detach();
    std::cout << "[���߳�] ����ִ�в��˳�\n";
}

// ȫ��ԭ�ӱ�־������֪ͨ�ػ��߳�ֹͣ
std::atomic<bool> stop_flag{false};

// �ػ���־�̺߳���
void logger_thread() {
    while (!stop_flag.load(std::memory_order_relaxed)) {
        // ��ȡ��ǰʱ���
        auto now = std::chrono::system_clock::now();
        std::time_t t = std::chrono::system_clock::to_time_t(now);

        // ��ӡ��־
        std::cout << "[��־�߳�] " << std::ctime(&t) << " ��¼������־" << std::endl;

        // �ȴ� 1 ��
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    std::cout << "[��־�߳�] ��⵽ֹͣ�źţ��˳��߳�\n";
}

void main_with_logger_thread() {
    // �����ػ��߳�
    std::thread t(logger_thread);
    if (t.joinable())
        t.detach();

    // ���߳�ѭ����ȡ�û�����
    std::string line;
    std::cout << "[���߳�] �����ı������� \"quit\" ���˳�����\n";
    while (std::getline(std::cin, line)) {
        if (line == "quit") {
            stop_flag.store(true, std::memory_order_relaxed);
            break;
        }
        std::cout << "[���߳�] �����룺" << line << std::endl;
    }

    // ���ػ��߳�һЩ�˳�ʱ��
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "[���߳�] ���˳������������\n";
}

/* ���� TaskQueue */
void test_TaskQueue() {
    TaskQueue queue;

    // �����������߳�
    std::thread consumer([&queue]()
                         { queue.run(); });

    // ���Ͷ�������
    queue.push_task([]() {
        std::cout << "Lambda task executed\n";
    });

    queue.push_task(std::bind([](int x)
        { std::cout << "Bind task with x=" << x << std::endl; }
        , 42));
    queue.push_task([]() {
        std::cout << "Another lambda task.\n";
    });

    auto free_func = []() {
        std::cout << "Free function task\n";
    };

    queue.push_task(free_func);

    // ֹͣ���ȴ��������˳�
    queue.stop();
    consumer.join();
}

#endif //MULTITHREADINGPRACTICE_THREADBASICS_H
