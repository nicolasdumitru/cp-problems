// === Problem Information ===
// Name: Dice Combinations
// Statement URL: https://cses.fi/problemset/task/1633/

// === Solution Information ===
// Copyright (C) 2025 Nicolas Dumitru
// SPDX-License-Identifier: GPL-3.0-or-later
// Submission URL: https://cses.fi/problemset/result/17249834/
// Verdict: Accepted

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <istream>
#include <vector>

using i32 = std::int32_t;
using i64 = std::int64_t;

// using u32 = std::uint32_t;
// using u64 = std::uint64_t;

template <typename T>
inline auto read(std::istream &input = std::cin) -> T {
    T value;
    input >> value;
    return value;
}

auto main() -> int {
    // Fast I/O
    // Disable synchronization between C++ and C I/O for faster input/output
    std::ios::sync_with_stdio(false);
    // Untie cin from cout to prevent automatic flushing of cout before each cin
    std::cin.tie(nullptr);

    const auto n = read<i64>();

    const auto MOD = i64{1'000'000'007LL};

    auto dp = std::vector<i64>(n + 1);

    for (auto i = i64{1}; i <= n; i += 1) {
        dp[i] = i <= 6 ? 1 : 0;
        for (auto k = i64{1}; k <= 6 && k < i; k += 1) {
            dp[i] = (dp[i] + dp[i - k] % MOD) % MOD;
        }
    }

    std::cout << dp[n] << '\n';

    return 0;
}
