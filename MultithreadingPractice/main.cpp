#include <iostream>
#include "ThreadBasics.h"
#include "Parallel_merge_sort.h"

int main() {
//    std::thread t(hello);
//    if (t.joinable())
//        t.join();
//    std::cout << "Hello from main thread, ID = "
//              << std::this_thread::get_id()
//              << std::endl;
    test_parallel_sort();
    return 0;
}
