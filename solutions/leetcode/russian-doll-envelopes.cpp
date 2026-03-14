// === Problem Information ===
// Name: 354. Russian Doll Envelopes
// Statement URL: https://leetcode.com/problems/russian-doll-envelopes/description/

// === Solution Information ===
// Copyright (C) 2025 Nicolas Dumitru
// SPDX-License-Identifier: GPL-3.0-or-later
// Submission URL: https://leetcode.com/problems/russian-doll-envelopes/submissions/1948389581/
// Verdict: Accepted

#include <algorithm>
#include <cstdint>
#include <iterator>
#include <vector>

using i32 = std::int32_t;

auto lis_length(const std::vector<i32> &v) -> i32 {
    auto tails = std::vector<i32>();
    tails.reserve(v.size());
    for (const auto x : v) {
        const auto lower = std::lower_bound(tails.begin(), tails.end(), x);
        if (lower == tails.end()) {
            tails.push_back(x);
        } else {
            *lower = x;
        }
    }
    return std::ssize(tails);
}

class Solution {
public:
    auto maxEnvelopes(std::vector<std::vector<i32>> &envelopes) -> i32 {
        std::sort(envelopes.begin(), envelopes.end(), [](const auto &a, const auto &b) -> bool {
            return a[0] != b[0] ? a[0] < b[0] : a[1] > b[1];
        });

        auto heights = std::vector<i32>();
        heights.reserve(envelopes.size());
        for (const auto &env : envelopes) {
            heights.push_back(env[1]);
        }

        return lis_length(heights);
    }
};