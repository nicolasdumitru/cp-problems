// === Problem Information ===
// Name: 312. Burst Balloons
// Statement URL: https://leetcode.com/problems/burst-balloons/description/

// === Solution Information ===
// Copyright (C) 2025 Nicolas Dumitru
// SPDX-License-Identifier: GPL-3.0-or-later
// Submission URL: https://leetcode.com/problems/burst-balloons/submissions/1959060624/
// Verdict: ACCEPTED

#include <algorithm>
#include <cstdint>
#include <deque>
#include <iterator>
#include <vector>

using i64 = std::int64_t;

auto max_coins(const std::vector<i64> &nums) -> i64 {
    const auto n = std::ssize(nums);
    auto dp = std::vector<std::vector<i64>>(n, std::vector<i64>(n, 0));
    for (auto l = i64{3}; l <= n; l += 1) {
        for (auto i = i64{0}; i <= n - l; i += 1) {
            const auto j = i + l - 1;
            // compute dp[i][j] = max for interval [i, j]
            for (auto k = i + 1; k < j; k += 1) {
                dp[i][j] = std::max(dp[i][j], dp[i][k] + (nums[i] * nums[k] * nums[j]) + dp[k][j]);
            }
        }
    }
    return dp[0][n - 1];
}

class Solution {
public:
    i64 maxCoins(std::vector<int> &nums) {
        auto aux = std::vector<i64>(std::ssize(nums) + 1);
        aux[0] = 1;
        for (auto i = i64{std::ssize(aux) - 1}; i >= 1; i -= 1) {
            aux[i] = nums[i - 1];
        }
        aux.push_back(1);
        return max_coins(aux);
    }
};
