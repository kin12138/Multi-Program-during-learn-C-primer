//
// Created by libin on 2025/6/26.
//

#ifndef DATASTRUCTURE_CIRCULARLINKEDLIST_H
#define DATASTRUCTURE_CIRCULARLINKEDLIST_H
#include <iostream>

template<typename T>
struct ListNode {
    T data;
    ListNode* next;
    ListNode(const T & value) : data(value), next(nullptr) { }
};

template<typename T>
class CircularLinkedList{
    CircularLinkedList() : tail(nullptr) { }
    ~CircularLinkedList() { clear(); }
    void push_back(const T & val);
    void push_front(const T & val);
    void insert_after(int pos, const T & val);
    bool remove(const T &val);
    ListNode<T> * find(const T& val) const;
    void traverse() const;
    bool empty() const;
    void clear();
private:
    // 为了 O(1) 访问头结点和尾结点，一般保存尾指针 _head = _tail->next
    ListNode<T>* tail;
};

template<typename T>
void CircularLinkedList<T>::push_back(const T &val) {
    ListNode<T>* node = new ListNode<T>(val);
    if (tail){
        node->next = tail->next;
        tail->next = node;
        tail = node;
    } else {
        // 空链表
        node->next = node;
        tail = node;
    }
}

template<typename T>
void CircularLinkedList<T>::push_front(const T &val) {
    ListNode<T>* node = new ListNode<T>(val);
    if (tail) {
        node->next = tail->next;
        tail->next = node;
    } else {
        node->next = node;
        tail = node;
    }
}

template<typename T>
void CircularLinkedList<T>::insert_after(int pos, const T &val) {
    if (pos < 0 || !tail){
        push_front(val);
        return;
    }
    ListNode<T>* cur = tail->next;
    int idx = 0;
    while (idx != pos && cur != tail) {
        cur = cur->next;
        ++idx;
    }
    ListNode<T>* node = new ListNode<T>(val);
    node->next = cur->next;
    cur->next = node;
    if (cur == tail)        // 如果插在队尾，更新 _tail
        tail = node;
}

template<typename T>
bool CircularLinkedList<T>::remove(const T &val) {
    if (!tail) return false;
    ListNode<T>* prev = tail;
    ListNode<T>* cur = tail->next;
    do {
        if (cur->data == val) {
            if (cur == prev){   // 只有一个结点
                delete cur;
                tail = nullptr;
            } else {
                prev->next = cur->next;
                if (cur == tail) tail = prev;
                delete cur;
            }
        }
        prev = cur;
        cur = cur->next;
    }  while (cur != tail->next);
    return false;
}

template<typename T>
ListNode<T>* CircularLinkedList<T>::find(const T &val) const {
    ListNode<T>* cur = tail->next;
    do {
        if (cur->data == val) return cur;
        cur = cur->next;
    } while (cur != tail->next);
    return nullptr;
}

template<typename T>
void CircularLinkedList<T>::traverse() const {
    if (!tail) {
        std::cout << "empty\n";
        return;
    }
    ListNode<T>* cur = tail->next;
    do {
        std::cout << cur->data << " -> ";
        cur = cur->next;
    } while (cur != tail->next);
    std::cout << "back to _head\n";
}

template<typename T>
bool CircularLinkedList<T>::empty() const {
    return tail == nullptr;
}

template<typename T>
void CircularLinkedList<T>::clear() {
    if (!tail) return;
    ListNode<T>* cur = tail->next;
    while (cur != tail) {
        ListNode<T>*nxt = cur->next;
        delete cur;
        cur = nxt;
    }
    delete tail;
    tail = nullptr;
}

#endif //DATASTRUCTURE_CIRCULARLINKEDLIST_H
