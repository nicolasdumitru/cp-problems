// === Problem Information ===
// Name: Coin Combinations I
// Statement URL: https://cses.fi/problemset/task/1635/

// === Solution Information ===
// Copyright (C) 2025 Nicolas Dumitru
// SPDX-License-Identifier: GPL-3.0-or-later
// Submission URL: https://cses.fi/problemset/result/17250828/
// Verdict: ACCEPTED

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <istream>
#include <vector>

using i64 = std::int64_t;

const auto MOD = i64{1'000'000'007LL};

template <typename T>
inline auto read(std::istream &input = std::cin) -> T {
    T value;
    input >> value;
    return value;
}

template <typename T>
inline auto read_vector(i64 n, std::istream &input = std::cin) -> std::vector<T> {
    std::vector<T> v(n);
    for (auto &&x : v) {
        x = read<T>(input);
    }
    return v;
}

auto main() -> int {
    // Fast I/O
    // Disable synchronization between C++ and C I/O for faster input/output
    std::ios::sync_with_stdio(false);
    // Untie cin from cout to prevent automatic flushing of cout before each cin
    std::cin.tie(nullptr);

    const auto n = read<i64>();
    const auto x = read<i64>();

    const auto coins = read_vector<i64>(n);
    const auto max_coin = *std::max_element(coins.begin(), coins.end());

    auto dp = std::vector<i64>(std::max(x + 1, max_coin), 0);
    for (const auto c : coins) {
        dp[c] = 1;
    }

    for (auto i = i64{1}; i <= x; i += 1) {
        for (const auto c : coins) {
            if (c < i) {
                dp[i] = (dp[i] + dp[i - c] % MOD) % MOD;
            }
        }
    }

    std::cout << dp[x] << '\n';

    return 0;
}
