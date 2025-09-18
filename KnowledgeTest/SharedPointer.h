//
// Created by libin on 2025/6/9.
//

#ifndef KNOWLEDGETEST_SHAREDPOINTER_H
#define KNOWLEDGETEST_SHAREDPOINTER_H
#include <functional>
#include "Delete.h"

template<typename T> class SharedPointer;

template<typename T> void swap(SharedPointer<T> & lhs, SharedPointer<T> & rhs) {
    using std::swap;
    swap(lhs.ptr, rhs.ptr);
    swap(lhs.ref_count, rhs.ref_count);
    swap(lhs.deleter, rhs.deleter);
}

template<typename T>
class SharedPointer {
public:
    friend void swap(SharedPointer<T> & lhs, SharedPointer<T> &rhs);
    // default constructor
    SharedPointer() : ptr(nullptr), ref_count{new std::size_t (1)}, deleter{Delete<T>()} { }

    // constructor that takes raw pointer
    SharedPointer(T * p) : ptr(p), ref_count{new std::size_t (1)}, deleter(Delete<T>(ptr)) { }

    // copy constructor
    SharedPointer(const SharedPointer & other)
            : ptr(other.ptr), ref_count(other.ref_count), deleter(other.deleter) {
        ++*ref_count;
    }

    // move ctor
    SharedPointer(SharedPointer && other) noexcept
            : ptr(other.ptr), ref_count(other.ref_count), deleter(other.deleter) {
        other.ptr = other.ref_count = nullptr;
    }

    // copy assignment
    SharedPointer & operator=(const SharedPointer & rhs) {
        if (this == &rhs) {
            return *this;
        }
        decrement_and_destroy();
        ptr = rhs.ptr, ref_count = rhs.ref_count, deleter = rhs.deleter;
        ++*ref_count;
        return *this;
    }

    // move assignment
    SharedPointer & operator=(SharedPointer && rhs) noexcept {
        swap(*this, rhs);
        rhs.decrement_and_destroy();
        return *this;
    }

    // conversion operator
    operator bool() const {
        return ptr ? true : false;
    }

    // dereference operator
    T & operator * () const {
        return *ptr;
    }

    // destructor
    ~SharedPointer() {
        decrement_and_destroy();
    }

    // arrow operator
    T * operator -> () const noexcept{
        return ptr;
    }
    // use count
    auto use_count() const {
        return *ref_count;
    }

    // get underlying pointer
    auto get() const {
        return ptr;
    }

    // check if the unique user
    auto unique() const {
        return 1==*ref_count;
    }

    // swap
    auto swap(SharedPointer & rhs) {
        ::swap(*this, rhs);
    }

    // free the object pointed to, if unique
    auto reset() {
        decrement_and_destroy();
        deleter = Delete<T> ();
    }

    // reset with the new raw pointer
    auto reset(T* pointer) {
        if (ptr != pointer) {
            decrement_and_destroy();
            ptr = pointer;
            ref_count = new std::size_t (1);
            deleter = Delete<T> ();
        }
    }

    // reset with raw pointer and deleter
    auto reset(T * pointer, const std::function<void(T*)> & d) {
        reset(pointer);
        deleter = d;
    }
private:
    void decrement_and_destroy();
private:
    T * ptr;    // 保存指针
    std::size_t * ref_count;    // 引用计数
    std::function<void(T*)> deleter;    // 删除器
};


#endif //KNOWLEDGETEST_SHAREDPOINTER_H
