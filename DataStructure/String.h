//
// Created by libin on 2025/6/28.
//

#ifndef DATASTRUCTURE_STRING_H
#define DATASTRUCTURE_STRING_H
#include <vector>
#include <string>

// KMP 算法

std::vector<int> buildNext(const std::string & p) {
    int m = p.size();
    std::vector<int> next(m);
    next[0] = 0;
    int len = 0;

    // 逐步计算 i=1..m-1
    for (int i = 1; i < m; ++i) {
         // 如果 p[i] 和“当前匹配位置” p[len] 不同，则尝试回退 len
        while (len > 0 && p[i] != p[len]) {
            // 回退到上一次最长匹配的前缀末尾
            len = next[len - 1];
        }
        // 如果 p[i] 和 p[len] 匹配，则可以延长前缀匹配长度 len
        if (p[len] == p[i]) {
            ++len;
        }
        next[i] = len;
    }
    return next;
}

std::vector<int> getNext(const std::string & p) {
    auto m = p.size();
    std::vector<int> next(m);
    int i = 1, j = 0;
    next[1] = 0;
    while (i < m) {
        if (j == 0 || p[i] == p[j]) {
            ++i; ++j;
            next[i] = j;    // 若 Pi = Pj, 则 next[j+1] = next[j]+1
        } else {
            j = next[j];    // 否则令 j = next[j]，循环继续
        }
    }
}


#endif //DATASTRUCTURE_STRING_H
