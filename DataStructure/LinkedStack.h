//
// Created by libin on 2025/6/26.
//

#ifndef DATASTRUCTURE_LINKEDSTACK_H
#define DATASTRUCTURE_LINKEDSTACK_H
#include <iostream>
#include <stdexcept>

template<class T>
class LinkedStack{
public:
    LinkedStack() : head(nullptr), size_(0) { }
    ~LinkedStack() { clear();}
    void push(const T& val);
    void pop();
    T & top();
    const T& top() const;
    bool empty() const;
    size_t size() const;
    void clear();
private:
    struct Node{
        T data;
        Node* next;
        Node(const T& val, Node* n) : data(val), next(n) { }
    };
private:
    Node* head;
    size_t size_;
};

template<typename T>
void LinkedStack<T>::push(const T &val) {
    Node * node = new Node(val, head);
    head = node;
    ++size_;
}

template<typename T>
void LinkedStack<T>::pop() {
    if (empty())
        throw std::out_of_range("pop from empty stack");
    Node* to_delete = head;
    head = head->next;
    delete to_delete;
    --size_;
}

template<typename T>
T& LinkedStack<T>::top() {
    if (empty())
        throw std::out_of_range("top from empty stack");
    return head->data;
}

template<typename T>
const T& LinkedStack<T>::top() const {
    if(empty())
        throw std::out_of_range("top from empty stack");
    return head->data;
}

template<typename T>
bool LinkedStack<T>::empty() const {
    return head == nullptr;
}

template<typename T>
size_t LinkedStack<T>::size() const {
    return size_;
}

template<typename T>
void LinkedStack<T>::clear() {
    while (head) {
        Node* next = head->next;
        delete head;
        head = next;
    }
    size_ = 0;
}

#endif //DATASTRUCTURE_LINKEDSTACK_H
