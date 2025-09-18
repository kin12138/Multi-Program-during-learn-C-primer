//
// Created by libin on 2025/6/7.
//

#include "BlobPtr.h"
#include <stdexcept>

template <typename T>
std::shared_ptr<std::vector<T>> BlobPtr<T>::check(std::size_t i, const std::string &msg) const {
    auto ret = wptr.lock();
    if(!ret)
        throw std::runtime_error("unbound BlobPtr");
    if (i >= ret->size() || i <= 0)
        throw std::out_of_range(msg);
    return ret;
}

template <typename T>
BlobPtr<T> & BlobPtr<T>::operator++() {
    check(curr+1, "next element out of range");
    ++curr;
    return *this;
}

template <typename T>
BlobPtr<T> & BlobPtr<T>::operator--() {
    --curr;
    check(curr, "decrement pass begin of BlobPtr");
    return *this;
}

template <typename T>
BlobPtr<T> BlobPtr<T>::operator++(int) {
    // 此处无需检查；调用前置递增时会进行检查
    BlobPtr ret = *this;    // 保存当前值
    ++*this;        // 前置递增检查是否合法
    return ret;     // 返回保存的状态
}

template <typename T>
BlobPtr<T> BlobPtr<T>::operator--(int) {
    BlobPtr ret = *this;
    --*this;
    return ret;
}

template <typename T>
bool operator==(const BlobPtr<T> &lhs, const BlobPtr<T> &rhs) {
    if (!lhs.wptr.expired() && !rhs.wptr.expired())
        return (lhs.wptr.lock() == rhs.wptr.lock()) && lhs.curr == rhs.curr;
    else
        return false;
}

template <typename T>
bool operator!=(const BlobPtr<T> &lhs, const BlobPtr<T> &rhs){
    return !(lhs == rhs);
}

template <typename T>
bool operator<(const BlobPtr<T> &lhs, const BlobPtr<T> &rhs) {
    return lhs.curr < rhs.curr;
}