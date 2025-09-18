//
// Created by libin on 2025/6/27.
//

#ifndef DATASTRUCTURE_LINKEDQUEUE_H
#define DATASTRUCTURE_LINKEDQUEUE_H
#include <iostream>
#include <stdexcept>

template<typename T>
class LinkedQueue{
public:
    LinkedQueue() : _head(nullptr), _tail(nullptr), _size(0) {}
    ~LinkedQueue(){ clear(); }
    void enqueue(const T & val);    // 入队，在队尾插入
    void dequeue(); // 出队，删除头结点
    T & front();
    bool empty() const;
    size_t size() const;
    void clear();
private:
    struct Node{
        T data;
        Node * next;
        explicit Node(const T & x): data(x), next(nullptr) { }
    };
private:
    Node* _head;
    Node* _tail;
    size_t _size;
};

template<typename T>
void LinkedQueue<T>::enqueue(const T &val) {
    Node * node = new Node(val);
    if (!_tail)
        _head = _tail = node;
    else {
        _tail->next = node;
        _tail = node;
    }
    ++_size;
}

template<typename T>
void LinkedQueue<T>::dequeue() {
    if (empty())
        throw std::underflow_error("dequeue on empty queue");
    Node* old = _head;
    _head = _head->next;
    if (!_head) _tail = nullptr;    // 删除最后一个更新 tail
    delete old;
    --_size;
}

template<typename T>
T & LinkedQueue<T>::front() {
    if (empty())
        throw std::underflow_error("front on empty queue");
    return _head->data;
}

template<typename T>
bool LinkedQueue<T>::empty() const {
    return _head == _tail;
}

template<typename T>
size_t LinkedQueue<T>::size() const {
    return _size;
}

template<typename T>
void LinkedQueue<T>::clear() {
    while (_head){
        Node* nxt = _head->next;
        delete _head;
        _head = nxt;
    }
    _head = _tail = nullptr;
    _size = 0;
}

#endif //DATASTRUCTURE_LINKEDQUEUE_H
