//
// Created by libin on 2025/4/22.
//

#include "String.h"
#include <cstring>
#include <algorithm>
#include <iostream>

// 初始化静态成员
std::allocator<char> String::alloc;

// 返回一个 pair，first 成员指向拷贝后的首元素，second 成员指向尾元素之后的位置
std::pair<char*, char*> String::alloc_n_copy(const char *b, const char *e) {
    auto newData = alloc.allocate(e-b);
    return {newData, std::uninitialized_copy(b, e, newData)};
}

void String::free() {
    if (elements){
        while (first_free != elements)
            alloc.destroy(--first_free);
        alloc.deallocate(elements, cap - elements);
    }
}

void String::alloc_n_move(size_t newCap) {
    auto newData = alloc.allocate(newCap);  // 申请新内存
    auto dest = newData;    // 指向新内存的首位置
    auto src = elements;   // 指向旧内存的首元素
    // 将旧内存中的元素移动到新内存中
    for (size_t i = 0; i != size(); ++i)
        alloc.construct(dest++, *src++);
    free();     // 释放原内存空间
    // 更新数据结构
    elements = newData;
    first_free = dest;
    cap = newData + newCap;
}

void String::reallocate() {
    auto newCap = size() ? 2 * size() : 1;
    alloc_n_move(newCap);
}

void String::splice(const char *b, const char *e) {
    reserve(size() + (e-b));
    while (b != e)
        alloc.construct(first_free++, *b++);
}

void swap(String &lhs, String &rhs) {
    using std::swap;
    swap(lhs.elements, rhs.elements);
    swap(lhs.first_free, rhs.first_free);
    swap(lhs.cap, rhs.cap);
}

String::String()
            : elements(nullptr), first_free(nullptr), cap(nullptr) {
    auto p = alloc.allocate(1);
    alloc.construct(p, '\0');
    elements = p;
    first_free = cap = p + 1;
}

String::String(const char *cstr)
            : elements(nullptr), first_free(nullptr), cap(nullptr) {
    auto newData = alloc_n_copy(cstr, cstr+std::strlen(cstr));
    elements = newData.first;
    first_free = cap = newData.second;
    std::cout << "String::String(const char *cstr)" << std::endl;
}

String::String(const String &rhs) {
    std::cout << "copy constructor: " << rhs << std::endl;
    auto newData = alloc_n_copy(rhs.begin(),rhs.end());
    elements = newData.first;
    first_free = cap = newData.second;
}

String::String(String &&rhs) noexcept
            : elements(rhs.elements), first_free(rhs.first_free), cap(rhs.cap){
    rhs.elements = rhs.first_free = rhs.cap = nullptr;
    std::cout << "move constructor: " << rhs << std::endl;
}

String & String::operator=(String rhs) {
    std::cout << "copy-assignment operator: String & String::operator=(String rhs) " << std::endl;
    swap(*this, rhs);
    return *this;
}

String::~String() {
    free();
}

void String::reserve(size_t n) {
    // 当 n 大于当前容量时才申请内存，n 小于 当前容量时什么也不做
    if (n > capacity()) {
        alloc_n_move(n);
    }
}

void String::resize(size_t n, char c) {
    if (n > size()){
        if (n > capacity()) reserve(n * 2);
        for (size_t i = size(); i != n; ++i)
            alloc.construct(first_free++, c);
    } else if (n < size()) {
        while (first_free != elements + n)
            alloc.destroy(--first_free);
    }
}

void String::resize(size_t n) {
    resize(n, char());
}

void String::push_back(char c) {
    chk_n_alloc();
    alloc.construct(first_free++, c);
}

void String::push_back(const String &rhs) {
    splice(rhs.begin(), rhs.end());
}

String operator+(const String &lhs, const String &rhs) {
    auto result = lhs;
    result.splice(rhs.begin(), rhs.end());
    return result;
}

void String::pop_back() {
    if (size() > 0)
        alloc.destroy(--first_free);
}

std::ostream & operator<<(std::ostream & os, const String & s) {
    for (char p : s)
        os << p;
    return os;
}

bool operator==(const String & lhs, const String & rhs) {
    if (lhs.size() != rhs.size()) return false;
    return std::memcmp(lhs.elements, rhs.elements, lhs.size()) == 0;
}

bool operator!=(const String & lhs, const String & rhs) {
    return !(lhs == rhs);
}

bool operator<(const String & lhs, const String & rhs) {
    // 使用 std::lexicographical_compare 按字典序逐个字符比较
    // 遇到第一个不同字符，按该字符的 < 关系决定结果
    // 如果所有字符都相同，则长度短的序列 < 长度较长的序列
    return std::lexicographical_compare(lhs.elements, lhs.first_free, rhs.elements, rhs.first_free);
}

bool operator>(const String & lhs, const String & rhs) { return rhs < lhs; }
bool operator<=(const String & lhs, const String & rhs) { return !(rhs < lhs); }
bool operator>=(const String & lhs, const String & rhs) { return !(lhs < rhs); }