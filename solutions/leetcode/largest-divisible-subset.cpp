// === Problem Information ===
// Name: 368. Largest Divisible Subset
// Statement URL: https://leetcode.com/problems/largest-divisible-subset/description/

// === Solution Information ===
// Copyright (C) 2025 Nicolas Dumitru
// SPDX-License-Identifier: GPL-3.0-or-later
// Submission URL: https://leetcode.com/problems/largest-divisible-subset/submissions/1947426307/
// Verdict: Accepted

#include <algorithm>
#include <cstdint>
#include <iterator>
#include <vector>

using i32 = std::int32_t;

class Solution {
public:
    auto largestDivisibleSubset(std::vector<i32> &nums) -> std::vector<i32> {
        std::sort(nums.begin(), nums.end());

        auto subset_size = std::vector<i32>(std::ssize(nums), 1);
        auto parent = std::vector<i32>(std::ssize(nums), -1);
        auto lds_rep = i32{0}; // largest number in the largest divisible subset
        for (auto i = i32{0}; i < std::ssize(nums); i += 1) {
            for (auto j = i32{0}; j < i; j += 1) {
                if (nums[i] % nums[j] == 0 && 1 + subset_size[j] > subset_size[i]) {
                    subset_size[i] = 1 + subset_size[j];
                    parent[i] = j;
                }
            }

            if (subset_size[i] > subset_size[lds_rep]) {
                lds_rep = i;
            }
        }

        auto result = std::vector<i32>();
        result.reserve(subset_size[lds_rep]);
        while (lds_rep >= 0) {
            result.push_back(nums[lds_rep]);
            lds_rep = parent[lds_rep];
        }
        return result;
    }
};