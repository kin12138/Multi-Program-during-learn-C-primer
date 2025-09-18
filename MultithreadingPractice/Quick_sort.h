//
// Created by libin on 2025/6/15.
//

#ifndef MULTITHREADINGPRACTICE_QUICK_SORT_H
#define MULTITHREADINGPRACTICE_QUICK_SORT_H
#include <list>
#include <algorithm>
#include <future>
#include <thread>

template<typename T>
std::list<T> sequential_quick_sort(std::list<T> input) {
    if (input.empty())
        return input;

    std::list<T> result;
    result.splice(result.begin(), input, input.begin());        // 将 input 的首元素作为“中间值”放到结果列表中
    T const & pivot = *result.begin();      // 将中间值进行标记

    auto divide_point = std::partition(input.begin(), input.end(),  // 将序列中的值分成小于中间值和大于中间值的两部分
                                       [&](T const & t) { return t < pivot; } ); // 返回一个不小于 pivot 元素的迭代器

    std::list<T> lower_part;
    lower_part.splice(lower_part.end(), input, input.begin(), divide_point);    // 将 input 中小于 divide_point 的值移动到新列表

    auto new_lower(sequential_quick_sort(std::move(lower_part)));
    auto new_higher(sequential_quick_sort(std::move(input)));

    result.splice(result.end(), new_higher);    // new_higher 指向的值放在中间值的后面
    result.splice(result.begin(), new_lower);   // new_lower 指向的值放在中间值的前面
    return result;
}

template<typename T>
std::list<T> parallel_quick_sort(std::list<T> input) {
    if(input.empty())
        return input;
    std::list<T> result;
    result.splice(result.begin(), input, input.begin());
    T const & pivot = *result.begin();

    auto divide_point = std::partition(input.begin(), input.end(),
                                       [&](T const & t) { return t < pivot; });

    std::list<T> lower_part;
    lower_part.splice(lower_part.end(), input, input.begin(), divide_point);

    std::future<std::list<T>> new_lower(        // 在另一个线程对小于中间值的部分进行排序
            std::async(&parallel_quick_sort<T>, std::move(lower_part)) );

    auto new_higher(parallel_quick_sort(std::move(input))); // 对大于中间值的部分使用递归进行排序

    result.splice(result.end(), new_higher);
    result.splice(result.begin(), new_lower.get());
    return result;
}

template<typename F, typename A>
std::future<typename std::result_of<F(A&&)>::type>
        spawn_task(F &&f, A &&a)  {
            using result_type = typename std::result_of<F(A&&)>::type;
            std::packaged_task<result_type (A&&)>
                    task(std::move(f));
            std::future<result_type > res(task.get_future());
            std::thread t(std::move(f), std::move(a));
            t.detach();
            return  res;
        }

#endif //MULTITHREADINGPRACTICE_QUICK_SORT_H
