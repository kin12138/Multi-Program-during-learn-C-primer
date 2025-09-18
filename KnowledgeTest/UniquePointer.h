//
// Created by libin on 2025/6/9.
//

#ifndef KNOWLEDGETEST_UNIQUEPOINTER_H
#define KNOWLEDGETEST_UNIQUEPOINTER_H
#include "DebugDelete.h"

template<typename T, typename D> class UniquePointer;
template<typename T, typename D>
void swap(UniquePointer<T,D> & lhs, UniquePointer<T,D> & rhs);


template<typename T, typename D = DebugDelete>
class UniquePointer {
    friend void swap(UniquePointer<T,D> & lhs, UniquePointer<T,D> & rhs);
public:
    UniquePointer(const UniquePointer &) = delete;
    UniquePointer & operator=(const UniquePointer&) = delete;

    // default ctor and one taking T*
    UniquePointer() = default;
    UniquePointer(T * up) : ptr(up) { }

    // move ctor
    UniquePointer(UniquePointer && up) noexcept
            : ptr(up.ptr){ up.ptr = nullptr; }

    // move assignment
    UniquePointer & operator=(UniquePointer && rhs) noexcept;

    // std::nullptr_t assignment
    UniquePointer & operator=(std::nullptr_t n) noexcept;

    // operator overload : *  -> bool
    T & operator*() const { return *ptr; }
    T * operator-> () const { return &this->operator*(); }
    operator bool () const { return ptr ? true : false; }

    // swap member using swap friend
    void swap(UniquePointer & rhs) { ::swap(this, rhs); }

    // free and make it point to nullptr or p's pointee.
    void reset() noexcept { deleter(ptr); ptr = nullptr; }
    void reset(T * p) noexcept {deleter(ptr); ptr = p; }

    // return ptr and make ptr point to nullptr
    T * release();

    ~UniquePointer(){
        deleter(ptr);
    }

private:
    T * ptr = nullptr;
    D deleter = D();
};


#endif //KNOWLEDGETEST_UNIQUEPOINTER_H
