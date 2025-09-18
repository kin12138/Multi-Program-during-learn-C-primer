//
// Created by libin on 2025/6/26.
//

#ifndef DATASTRUCTURE_SEQUENCESTACK_H
#define DATASTRUCTURE_SEQUENCESTACK_H
#include <iostream>
#include <stdexcept>

template<typename T>
class SequenceStack{
public:
    SequenceStack(size_t init_capacity = 16) :
                _capacity(init_capacity), _size(0) {
        _data = new T[_capacity];
    }
    ~SequenceStack() {
        delete [] _data;
    }

    void push(const T & val);
    void pop();
    T & top();
    const T & top() const;
    bool empty() const;
    size_t size() const;
private:
    void reserve(size_t new_cap);
private:
    T* _data;
    size_t _size;
    size_t _capacity;
};

template<typename T>
void SequenceStack<T>::reserve(size_t new_cap) {
    T * new_data = new T[new_cap];
    for (int i = 0; i < _size; ++i) {
        new_data[i] = _data[i];
    }
    delete [] _data;
    _data = new_data;
    _capacity = new_cap;
}

template<typename T>
void SequenceStack<T>::push(const T &val) {
    if (_size == _capacity)
        // 扩容为原来的两倍
        reserve(2*_capacity);
    _data[_size++] = val;
}

template<typename T>
void SequenceStack<T>::pop() {
    if (empty())
        throw std::out_of_range("pop from empty stack");
    --_size;
    // 可选的收缩容量
    if(_size > 0 && _size == _capacity / 4)
        reserve(_capacity/2);
}

template<typename T>
T & SequenceStack<T>::top() {
    if (empty())
        throw std::out_of_range("top from empty stack");
    return _data[_size-1];
}

template<typename T>
const T& SequenceStack<T>::top() const {
    if (empty())
        throw std::out_of_range("top from empty stack");
    return _data[_size-1];
}

template<typename T>
bool SequenceStack<T>::empty() const {
    return _size == 0;
}

template<typename T>
size_t SequenceStack<T>::size() const {
    return _size;
}

#endif //DATASTRUCTURE_SEQUENCESTACK_H
