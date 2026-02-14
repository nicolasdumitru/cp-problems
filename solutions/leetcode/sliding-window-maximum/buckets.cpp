// === Problem Information ===
// Name: Sliding Window Maximum
// Statement URL: https://leetcode.com/problems/sliding-window-maximum/description/

// === Solution Information ===
// Copyright (C) 2025 Nicolas Dumitru
// SPDX-License-Identifier: GPL-3.0-or-later
// Submission URL: https://leetcode.com/problems/sliding-window-maximum/submissions/1918852218/
// Verdict: Accepted

#include <algorithm>
#include <vector>
using namespace std;

#pragma clang diagnostic ignored "-Wsign-compare"
#pragma clang diagnostic ignored "-Wsign-conversion"

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int> &nums, int k) {
        auto prefix_max = vector<int>(nums.size());
        auto suffix_max = vector<int>(nums.size());
        for (int i = 0; i < nums.size(); i += 1) {
            if (i % k == 0) {
                prefix_max[i] = nums[i];
            } else {
                prefix_max[i] = max(prefix_max[i - 1], nums[i]);
            }
            
            const auto j = nums.size() - 1 - i;
            if (j == nums.size() - 1 || j % k == k - 1) {
                suffix_max[j] = nums[j];
            } else {
                suffix_max[j] = max(suffix_max[j + 1], nums[j]);
            }
        }

        auto result = vector<int>(nums.size() - k + 1);
        for (int i = 0; i < result.size(); i += 1) {
            result[i] = max(suffix_max[i], prefix_max[i + k - 1]);
        }
        return result;
    }
};