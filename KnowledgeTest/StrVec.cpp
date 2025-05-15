//
// Created by libin on 2025/4/21.
//

#include "StrVec.h"
#include <algorithm>

std::allocator<std::string> StrVec::alloc;

void StrVec::range_initialize(const std::string *b, const std::string *e) {
    auto newData = alloc_n_copy(b, e);
    elements = newData.first;
    first_free = cap = newData.second;
}

StrVec::StrVec(const std::initializer_list<std::string> &il)
                : elements(nullptr), first_free(nullptr), cap(nullptr) {
    range_initialize(il.begin(), il.end());
}

StrVec::StrVec(const StrVec &rhs) {
    // 调用 alloc_n_copy 分配空间，以容纳与 rhs 中一样多的元素并进行元素的拷贝
    auto newData = alloc_n_copy(rhs.begin(), rhs.end());
    elements = newData.first;
    first_free = cap = newData.second;
}

StrVec & StrVec::operator=(StrVec rhs) {
/*    // 调用 alloc_n_copy 分配内存，大小与 rhs 中元素所占空间一样多
    auto data = alloc_n_copy(rhs.begin(), rhs.end());
    free();
    elements = data.first;
    first_free = cap = data.second;
    return *this;
*/
/* 使用 copy-swap 技术 */
    swap(*this, rhs);
    return *this;
}

void swap(StrVec &lhs, StrVec &rhs) {
    using std::swap;
    swap(lhs.elements, rhs.elements);
    swap(lhs.first_free, rhs.first_free);
    swap(lhs.cap, rhs.cap);
}

StrVec::~StrVec() {
    free();
}

StrVec::StrVec(StrVec &&s) noexcept     // 移动构造函数不应该抛出任何异常
        // 成员初始化器接管 s 中的资源
        :elements(s.elements), first_free(s.first_free), cap(s.cap){
    // 令 s 进入这样一种状态——对其运行析构函数是安全的
    s.elements = s.first_free = s.cap = nullptr;
}

StrVec & StrVec::operator=(StrVec &&rhs) noexcept {
    // 直接进行自赋值检测
    if (this != &rhs) {
        free();     // 释放已有元素
        // 从 rhs 接管资源
        elements = rhs.elements;
        first_free = rhs.first_free;
        cap = rhs.cap;
        // 将 rhs 置于可析构状态
        rhs.elements = rhs.first_free = rhs.cap = nullptr;
    }
    return *this;
}

void StrVec::push_back(const std::string & str) {
    chk_n_alloc();  // 确保有足够空间容纳新元素
    // 在 first_free 指向的内存中构造 str 的副本
    alloc.construct(first_free++, str);
}

void StrVec::push_back(std::string && str) {
    chk_n_alloc();
    alloc.construct(first_free++, std::move(str));
}

std::pair<std::string *, std::string *>
        StrVec::alloc_n_copy(const std::string *b, const std::string *e) {
    // 分配足够的内存空间保存给定范围内的元素
    auto data = alloc.allocate(e-b);
    // 初始化并返回一个 pair, 该 pair 由 data 和 uninitialized_copy 的返回值构成
    return {data, std::uninitialized_copy(b, e, data)};
}

void StrVec::free() {
/*    // 不能传递给 deallocate 一个空指针，如果 elements 为 0，函数什么也不做
    if (elements) {
        // 逆序销毁元素
        for (auto p = first_free; p != elements; )
            alloc.destroy(--p);
        alloc.deallocate(elements, cap - elements);
    }
*/
    if (elements){
        std::for_each(elements, first_free,[this](std::string &elem)
                            { this->alloc.destroy(&elem); });
        alloc.deallocate(elements, cap - elements);
    }
}

void StrVec::alloc_n_move(size_t newCap) {
    // 分配空间
    auto first = alloc.allocate(newCap);
    // 移动元素
    auto last = std::uninitialized_copy(std::make_move_iterator(begin()),
                                        std::make_move_iterator(end()),
                                        first);
    free();     // 释放旧空间
    // 更新指针
    elements = first;
    first_free = last;
    cap = first + newCap;
}

void StrVec::reallocate() {
    // 分配两倍于当前大小的内存空间
    auto newCapacity = size() ? 2 * size() : 1;
    alloc_n_move(newCapacity);
}

void StrVec::reserve(size_t n) {
    // 当 n 大于当前容量，才重新分配内存，n 小于当前容量，函数什么也不做
    if (n > capacity()) {
        alloc_n_move(n);
    }
}

void StrVec::resize(size_t n) {
    resize(n, std::string());
}

void StrVec::resize(size_t n, const std::string &t) {
    if (n > size()) {   // 若要求元素数量大于现有元素数量
        if (n > capacity()) reserve(n * 2);   // 若要求元素数量大于可容纳元素数量，重新申请内存
        for (size_t i = size(); i != n; ++i)
            alloc.construct(first_free++, t);   // 将新元素都初始化为 t
    } else if (n < size()) {    // 若要求元素小于现有元素
        while (first_free != elements + n) {
            alloc.destroy(--first_free);        // 移动尾后指针并销毁元素
        }
    }
}

bool operator==(const StrVec & lhs, const StrVec & rhs) {
    if (lhs.size() != rhs.size()) return false;
    auto lbegin = lhs.elements;
    auto rbegin = rhs.elements;
    for (size_t i = 0; i != lhs.size(); ++i) {
        if(*lbegin++ != *rbegin++) return false;
    }
    return true;
}
bool operator!=(const StrVec & lhs, const StrVec & rhs) {
    return !(lhs == rhs);
}

StrVec & StrVec::operator=(std::initializer_list<std::string> il) {
    auto data = alloc_n_copy(il.begin(), il.end());
    free();
    elements = data.first;
    first_free = cap = data.second;
    return *this;
}