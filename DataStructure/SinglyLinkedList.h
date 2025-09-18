//
// Created by libin on 2025/6/25.
//

#ifndef DATASTRUCTURE_SINGLYLINKEDLIST_H
#define DATASTRUCTURE_SINGLYLINKEDLIST_H
#include <iostream>

template<typename T>
struct listNode{
    T data; // 数据域
    listNode * next;    // 指向下一个指针
    listNode(const T & val) : data(val), next(nullptr) { }
};

template<typename T>
class SinglyLinkedList {
public:
    template<typename U>
    friend SinglyLinkedList<U> merge(SinglyLinkedList<U> & l1, SinglyLinkedList<U> & l2);
    SinglyLinkedList() : head(nullptr) { }
    ~SinglyLinkedList() { clear(); }
    // 在链表头部插入新节点
    void push_front(const T & value);
    // 在链表尾部插入新结点
    void push_back(const T & value);
    // 在第 pos 位置 后插入新节点
    // 如果 pos < 0 或者链表为空，则等同于 push_front
    void insert_after(int pos, const T & value);
    // 删除值为 value 的第一个节点
    bool remove(const T & value);
    // 删除 pos 位置的节点
    bool remove_pos(int pos);
    // 查找第一个值为 value 的节点，返回指针（未找到返回 nullptr）
    listNode<T> * find(const T & value) const;
    // 遍历打印链表
    void traverse() const;
    // 清空链表，释放所有节点
    void clear();

    // 翻转链表
    void reverse();
private:
    listNode<T> * head; // 链表头结点
};

// 迭代法实现合并两个链表
template<typename T>
listNode<T> * mergeListsByIteration(listNode<T> * l1, listNode<T>* l2) {
    listNode<T> dummy(T{});
    listNode<T> * tail = &dummy;
    while (l1 && l2) {
        if (l1->data < l2->data) {
            tail->next = l1;
            l1 = l1->next;
        } else {
            tail->next = l2;
            l2 = l2->next;
        }
        tail = tail->next;
    }
    // 接上剩余节点
    tail->next = l1 ? l1 : l2;
    return dummy.next;
}

// 递归法合并两个有序链表
template<typename T>
listNode<T>* mergeListsByRecursion(listNode<T>* l1, listNode<T>* l2) {
    if (!l1) return l2;
    if (!l2) return l1;

    if (l1->data < l2->data){
        l1->next = mergeListsByIteration(l1->next, l2);
        return l1;
    } else {
        l2->next = mergeListsByIteration(l1, l2->next);
        return l2;
    }
}

template<typename U>
SinglyLinkedList<U> merge(SinglyLinkedList<U> & l1, SinglyLinkedList<U> & l2) {
    listNode<U> *p1 = l1.head, *p2 = l2.head;
    auto p = mergeListsByIteration(p1, p2); // 这里也可以使用上面的递归方法代替
    SinglyLinkedList<U> result;
    result.head = p;

    // 为避免原链表析构时误删合并后的结点，需要切断 l1,l2 的 _head
    l1.head = nullptr, l2.head = nullptr;
    return result;
}

template<typename T>
void SinglyLinkedList<T>::push_front(const T &value) {
    listNode<T> * node = new listNode<T>(value);
    node->next = head;
    head = node;
}

template<typename T>
void SinglyLinkedList<T>::push_back(const T &value) {
    listNode<T> * node = new listNode<T>(value);
    if(!head){
        head = node;
        return;
    }
    listNode<T> *cur = head;
    while (cur->next) {
        cur = cur->next;
    }
    node->next = cur->next;
    cur->next = node;
}

template<typename T>
void SinglyLinkedList<T>::insert_after(int pos, const T &value) {
    if (pos < 0 || head == nullptr) {
        push_front(value);
        return;
    }
    listNode<T> * cur = head;
    int idx = 0;
    while (cur->next && idx < pos) {
        cur = cur->next;
        ++idx;
    }
    listNode<T>* node = new listNode<T>(value);
    node->next = cur->next;
    cur->next = node;
}

template<typename T>
bool SinglyLinkedList<T>::remove(const T &value) {
    listNode<T>* cur = head;
    listNode<T>* prev = nullptr;
    while (cur) {
        if (cur->data == value) {
            if (prev)
                prev->next = cur->next;
            else
                head = cur->next;
            delete cur;
            return true;
        }
        prev = cur;
        cur = cur->next;
    }
    return false;
}

template<typename T>
bool SinglyLinkedList<T>::remove_pos(int pos) {
    listNode<T> * cur = head;
    listNode<T> * prev = nullptr;
    int idx = 0;
    while (cur->next) {
        if (idx != pos) {
            prev = cur;
            cur = cur->next;
            ++idx;
        } else {
            prev->next = cur->next;
            delete cur;
            return true;
        }
    }
    return false;
}

template <typename T>
listNode<T>* SinglyLinkedList<T>::find(const T &value) const {
    listNode<T>* cur = head;
    while (cur) {
        if (cur->data == value)
            return cur;
        cur = cur->next;
    }
    return nullptr;
}

template<typename T>
void SinglyLinkedList<T>::traverse() const {
    listNode<T>* cur = head;
    while (cur) {
        std::cout << cur->data;
        if (cur->next) std::cout << " -> ";
        cur = cur->next;
    }
    std::cout << "\n";
}

template<typename T>
void SinglyLinkedList<T>::clear() {
    listNode<T> * cur = head;
    while (cur) {
        listNode<T> * nxt = cur->next;
        delete cur;
        cur = nxt;
    }
    head = nullptr;
}

template <typename T>
void SinglyLinkedList<T>::reverse() {
    if (!head->next)
        return;
    listNode<T> * cur = head;
    listNode<T> * prev = nullptr;
    listNode<T> * temp = nullptr;
    while (cur) {
        temp = cur->next;
        cur->next = prev;
        prev = cur;
        cur = temp;
    }
    head = prev;
}



#endif //DATASTRUCTURE_SINGLYLINKEDLIST_H
