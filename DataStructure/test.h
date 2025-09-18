//
// Created by libin on 2025/6/25.
//

#ifndef DATASTRUCTURE_TEST_H
#define DATASTRUCTURE_TEST_H

#include "SinglyLinkedList.h"
#include "DoubleLinkedList.h"
#include "String.h"

void testSinglyLinkedList() {
//    SinglyLinkedList<int> linkedList;
//    for (int i = 0; i < 10; ++i)
//        linkedList.push_front(i);
//    linkedList.traverse();
//    linkedList.reverse();
//    linkedList.traverse();
//    linkedList.insert_after(0, 22);
//    linkedList.traverse();
//    linkedList.find(22);
//    linkedList.push_back(33);
//    linkedList.remove(22);
//    linkedList.traverse();
//    linkedList.remove(22);
//    linkedList.remove_pos(2);
//    linkedList.traverse();
//    linkedList.reverse();
//    linkedList.traverse();
//    linkedList.clear();

//    linkedList.push_back(0);
//    linkedList.traverse();
//    linkedList.reverse();
//    linkedList.traverse();
//    linkedList.push_front(1);
//    linkedList.traverse();
//    linkedList.reverse();
//    linkedList.traverse();

    SinglyLinkedList<int> l1, l2;
    for (int i = 0; i < 30; i += 5)
        l1.push_back(i);
    l1.traverse();
    for (int i = 0; i < 20; i += 2)
        l2.push_back(i);
    l2.traverse();
    auto result = merge(l1,l2);
    result.traverse();
    l1.traverse(), l2.traverse();
}

void testDoubleLinkedList() {
    DoubleLinkedList<int> lst;
    for (int i = 0; i < 10; ++i) {
        lst.push_front(i);
    }
    lst.traverse_forward();
    for (int i = 10; i > 0; --i) {
        lst.push_back(i);
    }
    lst.traverse_forward();
    lst.insert_after(9, 33);
    lst.traverse_forward();
    lst.reverse();
    lst.traverse_forward();
}

void testCircularLinkedList() {

}

void testKMP() {
    std::string str("abcaabbacab");
    auto next = buildNext(str);
//    std::string stc("abaaba");
//    auto nxt = getNext(stc);
}

#endif //DATASTRUCTURE_TEST_H
