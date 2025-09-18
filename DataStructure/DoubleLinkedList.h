//
// Created by libin on 2025/6/25.
//

#ifndef DATASTRUCTURE_DOUBLELINKEDLIST_H
#define DATASTRUCTURE_DOUBLELINKEDLIST_H
#include <iostream>
#include <list>

template<typename T>
struct ListkNode{
    T data;
    ListkNode * next;
    ListkNode * prev;
    ListkNode (const T & value) : data(value), next(nullptr), prev(nullptr) { }
};

template<typename T>
class DoubleLinkedList {
public:
    template<typename U>
    friend DoubleLinkedList<U> merge(DoubleLinkedList<U> & l1, DoubleLinkedList<U> & l2);
    DoubleLinkedList() : head(nullptr), tail(nullptr) { }
    ~DoubleLinkedList() { clear(); }
    void push_front(const T & value);
    void push_back(const T & value);
    void insert_after(int pos, const T & value);
    bool remove(const T & value);
    bool remove_pos(int pos);
    ListkNode<T>* find(const T & value) const;
    void traverse_forward() const;
    void traverse_backward() const;
    void reverse();
    void clear();
private:
    ListkNode<T> * head;
    ListkNode<T> * tail;
};

template<typename T>
ListkNode<T>* mergeByIteration(ListkNode<T>* l1, ListkNode<T>* l2) {
    ListkNode<T> dummy(T{});
    ListkNode<T>* tmp = &dummy;
    while (l1 && l2) {
        if (l1->data < l2->data) {
            tmp->next = l1;
            l1->prev = tmp;
            l1 = l1->next;
        } else{
            tmp->next = l2;
            l2->prev = tmp;
            l2 = l2->next;
        }
        tmp = tmp->next;
    }
    ListkNode<T>* rem = l1 ? l1 : l2;
    if (rem) {
        tmp->next = rem;
        rem->prev = tmp;
    }
    return dummy.next;
}

template<typename T>
ListkNode<T>* mergeByRecursion(ListkNode<T>* l1, ListkNode<T>* l2) {
    if (!l1) return l2;
    if (!l2) return l1;

    if (l1->data < l2->data){
        l1->next = mergeByRecursion(l1->next, l2);
        return l1;
    } else {
        l2->next = mergeByRecursion(l1, l2->next);
        return l2;
    }
}

template<typename T>
DoubleLinkedList<T> merge(DoubleLinkedList<T> &l1, DoubleLinkedList<T> & l2){
    ListkNode<T>* p1 = l1.head, *p2 = l2.head;
    auto temp = mergeByIteration(p1, p2);
    // 构造结果链表
    DoubleLinkedList<T> result;
    result.head = temp;
    if (result.head) {
        result.head->prev = nullptr;
        ListkNode<T>* cur = result.head;
        while (cur->next) cur = cur->next;
        result.tail = cur;
    } else {
        result.tail = nullptr;
    }
    l1.head = l1.tail = nullptr;
    l2.head = l2.tail = nullptr;
    return result;
}

template<typename T>
void DoubleLinkedList<T>::push_front(const T &value) {
    ListkNode<T>* node = new ListkNode<T>(value);
    node->next = head;
    if (head) head->prev = node;
    head = node;
    if (!tail) tail = node;
}

template<typename T>
void DoubleLinkedList<T>::push_back(const T &value) {
    auto * node = new ListkNode<T>(value);
    node->prev = tail;
    if (tail) tail->next = node;
    tail = node;
    if(!head) head = node;
}

template<typename T>
void DoubleLinkedList<T>::insert_after(int pos, const T &value) {
    if (pos < 0 || !head) {
        push_front(value);
        return;
    }
    ListkNode<T> * cur = head;
    int idx = 0;
    while (cur->next && idx != pos) {
        cur = cur->next;
        ++idx;
    }
    ListkNode<T> * node = new ListkNode<T>(value);
    node->next = cur->next;
    node->prev = cur;
    if (cur->next) cur->next->prev = node;
    cur->next = node;
    if (cur == tail) tail = node;
}

template<typename T>
bool DoubleLinkedList<T>::remove(const T &value) {
    ListkNode<T>* cur = head;
    while (cur) {
        if (cur->data == value) {
            if (cur->prev) cur->prev->next = cur->next;
            else head = cur->next;
            if (cur->next) cur->next->prev = cur->prev;
            else tail = cur->prev;
            delete cur;
            return true;
        }
        cur = cur->next;
    }
    return false;
}

template<typename T>
bool DoubleLinkedList<T>::remove_pos(int pos) {
    if (pos < 0 || !head)
        return false;
    ListkNode<T> * cur = head;
    int idx = 0;
    while (cur->next) {
        if (idx == pos) {
            if (cur->prev) cur->prev->next = cur->next;
            else head = cur->next;
            if (cur->next) cur->next->prev = cur->prev;
            else tail = cur->prev;
            delete cur;
            return true;
        }
        cur = cur->next;
        ++idx;
    }
    return false;
}

template<typename T>
ListkNode<T> * DoubleLinkedList<T>::find(const T &value) const {
    ListkNode<T> * cur = head;
    while (cur) {
        if (cur->data == value) return cur;
        cur = cur->next;
    }
    return nullptr;
}

template<typename T>
void DoubleLinkedList<T>::traverse_forward() const {
    ListkNode<T>* cur = head;
    while (cur) {
        std::cout << cur->data;
        if(cur->next) std::cout<< " -> ";
        cur = cur->next;
    }
    std::cout << "\n";
}

template<typename T>
void DoubleLinkedList<T>::traverse_backward() const {
    ListkNode<T>* cur = tail;
    while (cur) {
        std::cout << cur->data;
        if (cur->prev) std::cout << " -> ";
        cur = cur->prev;
    }
    std::cout << "\n";
}

template<typename T>
void DoubleLinkedList<T>::reverse() {
    ListkNode<T> * cur = head;
    ListkNode<T> * tmp = nullptr;
    while (cur){
        tmp = cur->next;
        cur->next = cur->prev;
        cur->prev = tmp;
        cur = cur->prev;
    }
    tmp = head;
    head = tail;
    tail = tmp;
}

template<typename T>
void DoubleLinkedList<T>::clear() {
    ListkNode<T>* cur = head;
    while (cur) {
        ListkNode<T> * nxt = cur->next;
        delete cur;
        cur = nxt;
    }
    head = tail = nullptr;
}

#endif //DATASTRUCTURE_DOUBLELINKEDLIST_H
