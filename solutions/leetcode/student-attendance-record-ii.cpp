// === Problem Information ===
// Name: 552. Student Attendance Record II
// Statement URL: https://leetcode.com/problems/student-attendance-record-ii/description/

// === Solution Information ===
// Copyright (C) 2025 Nicolas Dumitru
// SPDX-License-Identifier: GPL-3.0-or-later
// Submission URL: https://leetcode.com/problems/student-attendance-record-ii/submissions/1952841060/
// Verdict: Accepted

#include <algorithm>
#include <cstdint>
#include <vector>

using i64 = std::int64_t;

auto count_valid_strings(const i64 length, const i64 modulus = 1'000'000'000 + 7) -> i64 {
    auto dp = std::vector<i64>(std::max(length, i64{2}) + 1, 0);

    dp[0] = 1; // {""}
    dp[1] = 2; // {"P", "L"}
    dp[2] = 4; // {"PP", "PL", "LP", "LL"}

    for (auto i = i64{3}; i <= length; i += 1) {
        dp[i] = (dp[i - 1] +  // ending in "P"
                 dp[i - 2] +  // ending in "PL"
                 dp[i - 3]) % // ending in "PLL"
                modulus;
    }

    i64 total = dp[length];

    for (int i = 0; i < length; i += 1) {
        const i64 combinations = (dp[i] * dp[length - 1 - i]) % modulus;
        total = (total + combinations) % modulus;
    }
    
    return total;
}

class Solution {
public:
    int checkRecord(int n) {
        return count_valid_strings(n);
    }
};