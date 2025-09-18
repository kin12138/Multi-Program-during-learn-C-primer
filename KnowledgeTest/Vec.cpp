//
// Created by libin on 2025/6/8.
//

#include "Vec.h"
#include <algorithm>

template <typename T>
std::pair<T*, T*> Vec<T>::alloc_n_copy(const T * b, const T * e) {
    auto data = alloc.allocate(e - b);
    return  {data, std::uninitialized_copy(b, e, data)};
}

template<typename T>
void Vec<T>::free() {
    if (first_element)
        std::for_each(first_element, first_free, [this]( T & elem)
                    {  alloc.destroy(&elem); });
    alloc.deallocate(first_element, cap-first_element);
}

template<typename T>
void Vec<T>::alloc_n_move(size_t newCap) {
    auto first = alloc.allocate(newCap);
    auto last = std::uninitialized_copy(std::make_move_iterator(begin()),
                                        std::make_move_iterator(end()),
                                        first);
    free();
    first_element = first;
    first_free = last;
    cap = first + newCap;
}

template<typename T>
void Vec<T>::reallocate() {
    // 分配两倍于当前大小的内存空间
    auto newCap = size() ? 2 * size() : 1;
    alloc_n_move(newCap);
}

template<typename T>
void Vec<T>::range_initialize(const T *b, const T *e) {
    auto newData = alloc_n_copy(b, e);
    first_element = newData.first;
    first_free = cap = newData.second;
}

template<typename T>
Vec<T>::Vec(std::initializer_list<T> il) :
        first_element(nullptr), first_free(nullptr), cap(nullptr){
    range_initialize(il.begin(), il.end());
}

template<typename T>
Vec<T>::Vec(const Vec<T> &rhs) {
    auto newData = alloc_n_copy(rhs.cbegin(), rhs.cend());
    first_element = newData.first;
    first_free = = cap = newData.second;
}

template<typename T>
Vec<T> & Vec<T>::operator=(const Vec<T> &rhs) {
    if (this != &rhs) {
        auto newData = alloc_n_copy(rhs.cbegin(), rhs.cend());
        free();
        first_element = newData.first;
        first_free = cap = newData.second;
    }
    return *this;

    // 或者用 swap 技术
}

template<typename T>
Vec<T>::Vec(Vec<T> &&rhs) noexcept :
            first_element(rhs.first_element),
            first_free(rhs.first_free),
            cap(rhs.cap){
    rhs.first_element = rhs.first_free = rhs.cap = nullptr;
}

template<typename T>
Vec<T> & Vec<T>::operator=(Vec<T> &&rhs) noexcept {
    if (this != &rhs) {
        free();
        first_element = rhs.first_element;
        first_free = rhs.first_free;
        cap = rhs.cap;
        rhs.first_element = rhs.first_free = rhs.cap = nullptr;
    }
    return *this;
}

template<typename T>
Vec<T>::~Vec() {
    free();
}

template<typename T>
Vec<T> & Vec<T>::operator=(std::initializer_list<T> il) {
    auto newData = alloc_n_copy(il.begin(), il.end());
    free();
    first_element = newData.first;
    first_free = cap = newData.second;
    return *this;
}

template<typename T>
void Vec<T>::reserve(size_t n) {
    // 当 n 大于当前容量，才重新分配内存
    // 当 n 小于当前容量，什么也不做
    if (n > capacity())
        alloc_n_move(n);
}

template<typename T>
void Vec<T>::resize(size_t n, const T &t) {
    if (n > size()) {   // 要求的元素数量大于现有的元素数量
        if (n > capacity()) reserve(2 * n); // 要求的元素数量大于容量，重新申请更大的内存
        for (size_t i = size(); i != n; ++i)
            alloc.construct(first_free++, t);
    } else if (n < size()) {    // 要求的元素数量小于当前元素数量
        while (first_free != first_element + n){    // 逆序销毁多余的元素
            alloc.destroy(--first_free);        // 移动尾后指针并销毁元素
        }
    }
}

template<typename T>
void Vec<T>::resize(size_t n) {
    resize(n, T());
}

template<typename T>
void Vec<T>::push_back(const T & t) {
    check_n_alloc();
    alloc.construct(first_free++, t);
}

template<typename T>
void Vec<T>::push_back(T && t) {
    check_n_alloc();
    alloc.construct(first_free++, std::move(t));
}

template<typename T>
void swap(Vec<T> & lhs, Vec<T> & rhs) {
    using std::swap;
    swap(lhs.first_element, rhs.first_element);
    swap(lhs.first_free, rhs.first_free);
    swap(lhs.cap, rhs.cap);
}

template<typename T>
bool operator==(const Vec<T> & lhs, const Vec<T> & rhs) {
    if (lhs.size() != rhs.size()) return false;
    auto lbegin = lhs.first_element;
    auto rbegin = rhs.first_element;
    while (lbegin != lhs.first_free) {
        if (*lbegin++ != *rbegin++) return false;
    }
    return true;
}

template<typename T>
bool operator!=(const Vec<T> & lhs, const Vec<T> & rhs) {
    return !(lhs == rhs);
}