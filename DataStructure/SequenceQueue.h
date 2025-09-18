//
// Created by libin on 2025/6/27.
//

#ifndef DATASTRUCTURE_SEQUENCEQUEUE_H
#define DATASTRUCTURE_SEQUENCEQUEUE_H
#include <iostream>
#include <stdexcept>

template<typename T>
class SequenceQueue{
    SequenceQueue(size_t capacity =  16)
            : _cap(capacity + 1), _data(new T[_cap]), _head(0), _tail(0) {}
    ~SequenceQueue() { delete [] _data; }
    void enqueue(const T& x);
    void dequeue();
    T & front();
    bool empty() const;
    bool full() const;
    size_t size() const;
private:
    size_t _cap; // 实际容量 = 用户设定 + 1；用来区分队满或空
    T * _data;
    size_t _head;
    size_t _tail;
};

template<typename T>
void SequenceQueue<T>::enqueue(const T &x) {
    if(full())
        throw std::overflow_error("enqueue on full queue");
    _data[_tail] = x;
    _tail = (_tail + 1) % _cap;
}

template<typename T>
void SequenceQueue<T>::dequeue() {
    if (empty())
        throw std::underflow_error("dequeue on empty queue");
    _head = (_head+1) % _cap;
}

template<typename T>
T & SequenceQueue<T>::front() {
    if (empty())
        throw std::underflow_error("front on empty queue");
    return _data[_head];
}

template<typename T>
bool SequenceQueue<T>::empty() const {
    return _head == _tail;
}

template<typename T>
bool SequenceQueue<T>::full() const {
    return (_tail+1) % _cap;
}

template<typename T>
size_t SequenceQueue<T>::size() const {
    return (_tail+_cap - _head) % _cap;
}

#endif //DATASTRUCTURE_SEQUENCEQUEUE_H
