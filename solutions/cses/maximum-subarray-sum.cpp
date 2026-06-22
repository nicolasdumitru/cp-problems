// === Problem Information ===
// Name: Maximum Subarray Sum
// Statement URL: https://cses.fi/problemset/task/1643/

// === Solution Information ===
// Copyright (C) 2025 Nicolas Dumitru
// SPDX-License-Identifier: GPL-3.0-or-later
// C++ standard: C++20
// Submission URL: https://cses.fi/problemset/result/17657080/
// Verdict: ACCEPTED

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <istream>
#include <limits>
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

auto main() -> int {
    // Fast I/O
    // Disable synchronization between C++ and C I/O for faster input/output
    std::ios::sync_with_stdio(false);
    // Untie cin from cout to prevent automatic flushing of cout before each cin
    std::cin.tie(nullptr);

    const auto n = read<i64>();

    const auto pref_sum = [&n]() -> std::vector<i64> {
        auto pref_sum = std::vector<i64>(n + 1);
        pref_sum[0] = 0;
        for (auto i = i64{1}; i <= n; i += 1) {
            const auto x = read<i64>();
            pref_sum[i] = pref_sum[i - 1] + x;
        }
        return pref_sum;
    }();

    auto min_pref = pref_sum[0];
    auto max_sum = std::numeric_limits<i64>::min();
    for (auto r = i64{1}; r <= n; r += 1) {
        max_sum = std::max(max_sum, pref_sum[r] - min_pref);
        min_pref = std::min(min_pref, pref_sum[r]);
    }

    std::cout << max_sum << '\n';

    return 0;
}
