// === Problem Information ===
// Name: Removal Game
// Statement URL: https://cses.fi/problemset/task/1097/

// === Solution Information ===
// Copyright (C) 2025 Nicolas Dumitru
// SPDX-License-Identifier: GPL-3.0-or-later
// Submission URL: https://cses.fi/problemset/result/16661202/
// Verdict: ACCEPTED

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <istream>
#include <iterator>
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

template <typename T>
inline auto read_vector(i64 n, std::istream &input = std::cin) -> std::vector<T> {
    std::vector<T> v(n);
    for (auto &&x : v) {
        x = read<T>(input);
    }
    return v;
}

auto max_score(const std::vector<i64> x) -> i64 {
    auto dp = std::vector<std::vector<i64>>(std::ssize(x), std::vector<i64>(std::ssize(x), 0));

    auto sum = i64{0};
    for (auto i = i64{0}; i < std::ssize(x); i += 1) {
        dp[i][i] = x[i];
        sum += x[i];
    }

    for (auto i = i64{std::ssize(x) - 2}; i >= 0; i -= 1) {
        for (auto j = i64{i + 1}; j < std::ssize(x); j += 1) {
            dp[i][j] = std::max(x[i] - dp[i + 1][j], x[j] - dp[i][j - 1]);
        }
    }

    return (sum + dp[0][std::ssize(dp[0]) - 1]) / 2;
}

auto main() -> int {
    // Fast I/O
    // Disable synchronization between C++ and C I/O for faster input/output
    std::ios::sync_with_stdio(false);
    // Untie cin from cout to prevent automatic flushing of cout before each cin
    std::cin.tie(nullptr);

    const auto n = read<i64>();
    const auto x = read_vector<i64>(n);

    std::cout << max_score(x) << '\n';

    return 0;
}
