// === Problem Information ===
// Name: Sum of Two Values
// Statement URL: https://cses.fi/problemset/task/1640

// === Solution Information ===
// Copyright (C) 2025 Nicolas Dumitru
// SPDX-License-Identifier: GPL-3.0-or-later
// C++ standard: C++20
// Submission URL: https://cses.fi/problemset/result/17643063/
// Verdict: ACCEPTED

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <istream>
#include <iterator>
#include <utility>
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
    const auto x = read<i64>();

    auto v = std::vector<std::pair<i64, i64>>(n);

    for (auto i = i64{0}; i < std::ssize(v); i += 1) {
        v[i].first = read<i64>();
        v[i].second = i + 1;
    }

    std::sort(v.begin(), v.end());

    auto l = i64{0};
    auto r = i64{std::ssize(v) - 1};
    while (l < r && v[l].first + v[r].first != x) {
        if (v[l].first + v[r].first < x) {
            l += 1;
        } else {
            r -= 1;
        }
    }

    if (l < r) {
        std::cout << v[l].second << ' ' << v[r].second << '\n';
    } else {
        std::cout << "IMPOSSIBLE\n";
    }

    return 0;
}
