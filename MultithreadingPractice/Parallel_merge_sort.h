//
// Created by libin on 2025/6/20.
//

#ifndef MULTITHREADINGPRACTICE_PARALLEL_MERGE_SORT_H
#define MULTITHREADINGPRACTICE_PARALLEL_MERGE_SORT_H
#include <vector>
#include <future>
#include <algorithm>
#include <iterator>

#include <random>
#include <chrono>
#include <iostream>

namespace parallel_sort_detail {
    template<typename RandomIt>
    void sort_range(RandomIt first, RandomIt last,
                    unsigned depth,
                    size_t min_parallel_size,
                    size_t max_depth)
    {
        auto size = std::distance(first, last);
        if (size < static_cast<decltype(size)> (min_parallel_size)) {     // 排序区间小于设定阈值使用串行排序
            std::sort(first, last);
            return;
        }

        RandomIt mid = first + size / 2;

        if (depth < max_depth) {
            // 并发排序左半部分
            auto future_left = std::async(std::launch::async,
                                          sort_range<RandomIt>,
                                          first, mid,
                                          depth + 1,
                                          min_parallel_size,
                                          max_depth);
            // 主线程并发排序右半部分
            sort_range(mid, last, depth + 1, min_parallel_size, max_depth);
            future_left.get();
        } else {
            // 已到达最大并发深度，串行排序
            std::sort(first, mid);
            std::sort(mid, last);
        }
        // 归并
        std::inplace_merge(first, mid, last);
    }
}

template<typename T>
void parallel_merge_sort(std::vector<T> & data, size_t min_parallel_size = 50000) {
    if (data.empty()) return;
    unsigned int hw_threads = std::thread::hardware_concurrency();
    unsigned int max_depth = hw_threads > 1
                             ? static_cast<unsigned int>(std::log2(hw_threads))
                             : 1u;
    parallel_sort_detail::sort_range(data.begin(), data.end(),
                                     0,
                                     min_parallel_size,
                                     max_depth);
}

void test_parallel_sort() {
    size_t N = 5'000'000;
    std::vector<int> data(N);
    std::mt19937 rng(123);
    std::uniform_int_distribution<int> dist(0, 1'000'000);
    for (auto & v : data) v = dist(rng);

    auto data_copy = data;

    using Clock = std::chrono::high_resolution_clock;

    // 串行 sort
    {
        auto a = data;
        auto t1 = Clock::now();
        std::sort(a.begin(), a.end());
        auto t2 = Clock::now();
        std::cout << "std::sort time: "
                  << std::chrono::duration<double>(t2-t1).count()
                  << "s\n";
    }

    // 并行 sort
    {
        auto a = data_copy;
        auto t1 = Clock ::now();
        parallel_merge_sort(a, 100'000);
        auto t2 = Clock ::now();
        std::cout << "parallel_merge_sort time: "
                  << std::chrono::duration<double>(t2-t1).count()
                  << "s\n";
    }
}

#endif //MULTITHREADINGPRACTICE_PARALLEL_MERGE_SORT_H
