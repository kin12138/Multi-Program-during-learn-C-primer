//
// Created by libin on 2025/3/28.
//

#ifndef LEETCODE_283_MOVEZEROES_H
#define LEETCODE_283_MOVEZEROES_H

#include <vector>
#include <iostream>



void swap(int & a, int & b) {
    int temp = a;
    a = b;
    b = temp;
}
/* 冒泡法 */
//void moveZeroes(std::vector<int> &nums) {
//    for (int i = 0; i < nums.size() - 1; ++i) {
//        for (int j = nums.size() - 1; j > i; --j) {
//            if (nums.at(j) == 0)
//        }
//    }
//}

/* 快慢指针 */
void moveZeroes(std::vector<int> & nums) {
    int n = nums.size(), left = 0, right = 0;
    while (right < n) {
        if (nums.at(right)) {
            swap(nums.at(left), nums.at(right));
            ++left;
        }
        ++right;
    }
}

void moveZeroes2(std::vector<int> & nums) {
    auto n = nums.size();
    int index = 0, travel = 0;
    while (travel < n) {
        if (nums.at(travel)) {
            nums.at(index) = nums.at(travel);
            ++index;
        }
        ++travel;
    }
    while (index < n) {
        nums.at(index) = 0;
        ++index;
    }
}

void test283() {
    std::vector<int> vec{50,23,34,2,3,4,0,0,0,4,0};
    moveZeroes2(vec);

    for (auto & item : vec) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
}
#endif //LEETCODE_283_MOVEZEROES_H
