#include <iostream>
#include "ThreadPool.h"
#include <chrono>

int main() {
    ThreadPool pool(4);
    std::vector<std::future<int>> results;

    for (int i = 0; i < 8; ++i) {
        results.emplace_back(
            pool.enqueue([i] {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                return i * i;
            })
        );
    }

    for (auto & fut : results) {
        std::cout << fut.get() << std::endl;
    }
//    ThreadPool pool(2);
//    auto f1 = pool.enqueue([]{ std::cout << "Task 1\n"; });
//    auto f2 = pool.enqueue([]{ std::cout << "Task 2\n"; });
//
//    f1.get(); f2.get();
//    std::cout << "All done\n";
//    return 0;
}
