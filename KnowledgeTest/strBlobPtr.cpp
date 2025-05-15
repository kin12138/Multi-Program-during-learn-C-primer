//
// Created by libin on 2025/4/16.
//

#include "strBlobPtr.h"
#include <stdexcept>
#include "strBlob.h"

strBlobPtr::strBlobPtr(const strBlob &a, size_t sz) : wptr(a.data), curr(sz) { }

std::shared_ptr<std::vector<std::string>>
strBlobPtr::check(std::size_t i, const std::string & msg) const {
    auto ret = wptr.lock();
    if(!ret)
        throw std::runtime_error("unbound strBlobPtr");
    if(i >= ret->size())
        throw std::out_of_range(msg);
    return ret;
}

std::string & strBlobPtr::deref() const {
    auto p = check(curr, "dereference past end");
    return (*p)[curr];      // *p 是 shared_ptr 所指向的 vector
}

strBlobPtr & strBlobPtr::incr() {
    // 如果 curr 已经指向容器的尾后位置，就不能递增它
    check(curr, "increment past end of strBlobPtr");
    ++curr; // 推进当前位置
    return *this;
}


bool operator== (const strBlobPtr & lhs, const strBlobPtr & rhs) {
    if(!lhs.wptr.expired() && !rhs.wptr.expired()) {
        return (lhs.wptr.lock() == rhs.wptr.lock()) && (lhs.curr == rhs.curr);
    } else {
        return false;
    }
}

bool operator!= (const strBlobPtr & lhs, const strBlobPtr & rhs) {
    return !(lhs == rhs);
}

strBlobPtr & strBlobPtr::operator++() {
    // 如果 curr 已经指向了尾后位置，则无法递增它
    check(curr, "increment past end of strBlobPtr");
    ++curr;     // 将 curr 在当前状态下向向移动一个元素
    return *this;
}

strBlobPtr & strBlobPtr::operator--() {
    // 如果 curr 是 0，则递减它将产生一个无效下标
    --curr;
    check(curr, "decrement past begin of strBlobPtr");
    return *this;
}

strBlobPtr strBlobPtr::operator++(int) {
    // 此处无需检查有效性，调用前置运算符时才需要检查
    strBlobPtr ret = *this; // 记录当前值
    ++*this;    // 向前移动一个元素，前置++会检查递增的有效性
    return ret; // 返回之前记录的状态
}

strBlobPtr strBlobPtr::operator--(int) {
    // 此处无需检查有效性，调用前置运算符时才需要检查
    strBlobPtr ret = *this;
    --*this;    // 向前移动一个元素，前置++会检查递增的有效性
    return ret;
}

strBlobPtr &strBlobPtr::operator+=(std::size_t n) {
    // 先进行有效性检查
    check(curr + n, "increment past end of strBlobPtr");
    curr += n;
    return *this;
}

strBlobPtr & strBlobPtr::operator-=(std::size_t n) {
    check(curr - n, "decrement past begin of strBlobPtr");
    curr -= n;
    return *this;
}

strBlobPtr & strBlobPtr::operator+(std::size_t n) {
    return (*this += n);      // 检查有效性交给 +=
}

strBlobPtr & strBlobPtr::operator-(std::size_t n) {
    return (*this -= n);    // 检查有效性交给 +=
}

std::size_t operator-(const strBlobPtr & lhs, const strBlobPtr & rhs) {
    if (lhs.curr < rhs.curr)
        return rhs.curr - lhs.curr;
    else if(lhs.curr > rhs.curr)
        return lhs.curr - rhs.curr;
    else
        return 0;
}

bool operator<(const strBlobPtr & lhs, const strBlobPtr & rhs) {
    return lhs.curr < rhs.curr;
}

bool operator<=(const strBlobPtr & lhs, const strBlobPtr & rhs) {
    return !(rhs < lhs);
}

bool operator>(const strBlobPtr & lhs, const strBlobPtr & rhs) {
    return rhs < lhs;
}

bool operator>=(const strBlobPtr & lhs, const strBlobPtr & rhs) {
    return !(lhs < rhs);
}

std::string & strBlobPtr::operator*() const {
    auto p = check(curr, "dereference past end");
    return (*p)[curr];      // *p 是 对象所指的 vector
}

std::string * strBlobPtr::operator->() const {
    return & this->operator*();     // 将实际工作委托给解引用运算符
}