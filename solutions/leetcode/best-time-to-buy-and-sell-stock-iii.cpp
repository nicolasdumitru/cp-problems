// === Problem Information ===
// Name: 123. Best Time to Buy and Sell Stock III
// Statement URL: https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/description/

// === Solution Information ===
// Copyright (C) 2025 Nicolas Dumitru
// SPDX-License-Identifier: GPL-3.0-or-later
// Submission URL:
// https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/submissions/1946142065/
// Verdict: Accepted

#include <algorithm>
#include <cstdint>
#include <iterator>
#include <vector>

using i32 = std::int32_t;

class Solution {
public:
    auto maxProfit(std::vector<i32> &prices) -> i32 {
        auto min_price = prices.front();
        auto prefix_profit = std::vector<i32>(std::ssize(prices) + 1);
        prefix_profit[0] = 0;
        for (auto i = i32{1}; i <= std::ssize(prices); i += 1) {
            min_price = std::min(min_price, prices[i - 1]);
            prefix_profit[i] = std::max(prefix_profit[i - 1], prices[i - 1] - min_price);
        }

        auto profit = prefix_profit.back();
        auto max_price = prices.back();
        for (auto i = std::ssize(prices) - 1; i > 1; i -= 1) {
            max_price = std::max(max_price, prices[i]);
            profit = std::max(profit, prefix_profit[i] + max_price - prices[i]);
        }
        return profit;
    }
};