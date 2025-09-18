//
// Created by libin on 2025/6/10.
//

#ifndef MULTITHREADINGPRACTICE_ACCUMULATE_H
#define MULTITHREADINGPRACTICE_ACCUMULATE_H
#include <algorithm>
#include <thread>
#include <numeric>
#include <iterator>
#include <vector>
#include <functional>

template <typename Iterator, typename T>
struct accumulate_block{
    void operator()(Iterator first, Iterator last, T & result) {
        result = std::accumulate(first, last, result);
    }
};

template<typename Iterator, typename T>
T parallel_accumulate(Iterator first, Iterator last, T init) {
    unsigned long const length = std::distance(first, last);

    if (!length)
        return init;    // 如果输入范围为空，就返回 init

    unsigned long const min_per_thread = 25;    // 线程中的最小任务数
    unsigned long const max_threads =
            (length+min_per_thread-1)/min_per_thread; // 元素总数量除以线程块中最小任务数，确定线程最大数量

    unsigned long const hardware_threads =
            std::thread::hardware_concurrency();

    unsigned long const num_threads =               // 计算量的最大值和硬件支持线程数中，较小的值为启动线程的数量
            std::min((hardware_threads != 0 ? hardware_threads : 2), max_threads);

    unsigned long const block_size =  length / num_threads; // 每个线程中处理的元素数量：元素总数除以线程个数

    std::vector<T> results(num_threads);    // 存放中间结果
    std::vector<std::thread> threads(num_threads-1);    // 启动的线程数必须比 num_threads 少 1，因为已经有一个主线程

    Iterator block_start = first;
    for(unsigned long i = 0; i < num_threads-1; ++i) {
        Iterator block_end = block_start;
        std::advance(block_end, block_size);    // block_end 指向当前块的末尾
        threads[i] = std::thread(
                accumulate_block<Iterator, T>(),
                block_start, block_end, std::ref(results[i])
                );
        block_start = block_end;
    }
    accumulate_block<Iterator, T>() (
            block_start, last, results[num_threads-1] );    // 累加最终块的结果

    std::for_each(threads.begin(), threads.end(),
                  std::mem_fn(&std::thread::join));

    return std::accumulate(results.begin(), results.end(), init);
}

#endif //MULTITHREADINGPRACTICE_ACCUMULATE_H
