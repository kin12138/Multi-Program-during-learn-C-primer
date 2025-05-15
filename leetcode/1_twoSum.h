//
// Created by libin on 2025/3/20.
//

#ifndef LEETCODE_1_TWOSUM_H
#define LEETCODE_1_TWOSUM_H

#include <vector>
#include <iostream>

std::vector<int> twoSum(std::vector<int> nums, int target) {
    int n = nums.size();
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (nums[i] + nums[j] == target) {
                return {i, j};
            }
        }
    }
    return {};
}

void test(){
    std::vector<int> nums{2, 7, 11, 15};
    int target = 9;
    std::vector<int> results = twoSum(nums, target);
    std::cout << results.at(0) << " " << results.at(1) << std::endl;
}

#endif //LEETCODE_1_TWOSUM_H
