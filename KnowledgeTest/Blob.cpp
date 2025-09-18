//
// Created by libin on 2025/6/7.
//

#include "Blob.h"
#include <stdexcept>

template <typename T>
void Blob<T>::check(Blob::size_type i, const std::string &msg) const {
    if (i >= data->size())
        throw std::out_of_range(msg);
}

template <typename T>
Blob<T>::Blob() : data(std::make_shared<std::vector<T>>()) { }

template <typename T>
Blob<T>::Blob(std::initializer_list<T> il) : data(std::make_shared<std::vector<T>>(il)) { }

template<typename T>
template<typename IT>
Blob<T>::Blob(IT b, IT e) :
        data(std::make_shared<std::vector<T>>(b, e)){ }

template <typename T>
T & Blob<T>::front() {
    check(0, "front on empty Blob");
    return data->front();
}

template <typename T>
T & Blob<T>::front() const {
    check(0, "front on empty Blob");
    return data->front();
}

template <typename T>
T & Blob<T>::back() {
    check(0, "back on empty Blob");
    return data->back();
}

template <typename T>
T & Blob<T>::back() const {
    check(0, "back on empty Blob");
    return data->back();
}

template <typename T>
T & Blob<T>::operator[](Blob::size_type i) {
    // i 太大，check 抛出异常，阻止访问不存在元素
    check(i, "subscript out of range");
    return (*data)[i];
}

template <typename T>
T & Blob<T>::operator[](Blob::size_type i) const {
    // i 太大，check 抛出异常，阻止访问不存在元素
    check(i, "subscript out of range");
    return (*data)[i];
}

template <typename T>
void Blob<T>::pop_back() {
    check(0, "pop_back on empty Blob");
    data->pop_back();
}

template <typename T>
bool operator==(const Blob<T> &lhs, const Blob<T> &rhs) {
    return lhs.data == rhs.data;
}

template <typename T> bool operator!=(const Blob<T> &lhs, const Blob<T> &rhs) {
    return !(lhs == rhs);
}