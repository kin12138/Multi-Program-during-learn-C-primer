//
// Created by libin on 2025/6/7.
//

#ifndef KNOWLEDGETEST_TEMPLATEPROGRAMING_H
#define KNOWLEDGETEST_TEMPLATEPROGRAMING_H
#include "Sale_data.h"
#include <vector>
#include <list>

template <typename T>
int compare(const T & v1, const T & v2) {
//    if (v1 < v2) return -1;
//    if (v2 < v1) return 1;
    return 0;
}

void _16_3() {
    Sale_data s1, s2;
    auto i = compare(s1, s2);
    std::cout << i << std::endl;
}

template <typename Iterator, typename Value>
Iterator my_find(Iterator first, Iterator last, const Value & v) {
    for (; first != last && *first != v; ++first);
    return first;
}

void _16_4(){
    std::vector<int> vec{1, 3, 4, 5, 6, 7, 89, 89};
    std::list<std::string> lst{"asdf", "a", "cv", "sdfa"};
    auto it = my_find(vec.begin(), vec.end(), 5);
    auto it2 = my_find(lst.begin(), lst.end(), "a");
    std::cout << *it << "\n" << *it2 << std::endl;
}

template <typename Container>
void print(Container & c) {
    /* 使用容器的 size_type 成员和 size 成员控制打印*/
//    for (typename Container::size_type i = 0; i != c.size(); ++i) {
//        std::cout << c[i] << " ";
//    }

    /* 使用begin 和end 返回的迭代器来控制循环*/
    for(auto b = c.begin(); b != c.end(); ++b)
        std::cout << *b << " ";
}

#endif //KNOWLEDGETEST_TEMPLATEPROGRAMING_H
