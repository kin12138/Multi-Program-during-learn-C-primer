//
// Created by libin on 2025/6/9.
//

#include "UniquePointer.h"

// swap
template<typename T, typename D>
void swap(UniquePointer<T, D> & lhs, UniquePointer<T, D> & rhs) {
    using std::swap;
    swap(lhs.ptr, rhs.ptr);
    swap(lhs.deleter, rhs.deleter);
}

// move assignment
template<typename T, typename D>
UniquePointer<T, D> & UniquePointer<T, D>::operator=(UniquePointer<T, D> && rhs) noexcept {
    if (this != & rhs) {
        deleter(ptr);
        ptr = nullptr;
        ::swap(*this, rhs);
    }
    return *this;
}

// std::nullptr_t assignment
template<typename T, typename D>
UniquePointer<T, D> & UniquePointer<T, D>::operator=(std::nullptr_t n) noexcept {
    deleter(ptr); ptr = nullptr;
    return *this;
}

// relinquish control by returning ptr and make ptr point to nullptr
template<typename T, typename D>
T * UniquePointer<T, D>::release() {
    T * ret = ptr;
    ptr = nullptr;
    return ret;
}