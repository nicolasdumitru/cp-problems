// === Problem Information ===
// Name: Sliding Window Maximum
// Statement URL: https://leetcode.com/problems/sliding-window-maximum/description/

// === Solution Information ===
// Copyright (C) 2025 Nicolas Dumitru
// SPDX-License-Identifier: GPL-3.0-or-later
// Submission URL: https://leetcode.com/problems/sliding-window-maximum/submissions/1918811062/
// Verdict: Accepted

#include <deque>
#include <vector>
using namespace std;

#pragma clang diagnostic ignored "-Wsign-compare"
#pragma clang diagnostic ignored "-Wsign-conversion"

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int> &nums, int k) {
        auto d = deque<int>();
        auto result = vector<int>(nums.size() - k + 1);
        for (int i = 0; i < nums.size(); i += 1) {
            while (!d.empty() && nums[d.back()] <= nums[i]) {
                d.pop_back();
            }
            d.push_back(i);
            const auto swf = i - k + 1; // index of the sliding window's first element
            if (swf >= 0) {
                if (d.front() < swf) {
                    d.pop_front();
                }
                result[swf] = nums[d.front()];
            }
        }
        return result;
    }
};