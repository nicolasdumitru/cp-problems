// === Problem Information ===
// Name: A. Bigrams
// Statement URL: https://codeforces.com/contest/2242/problem/A

// === Solution Information ===
// Copyright (C) 2025 Nicolas Dumitru
// SPDX-License-Identifier: GPL-3.0-or-later
// C++ standard: C++20
// Submission URL: https://codeforces.com/contest/2242/submission/381474008
// Verdict: Accepted

// Note: This solution was submitted during the contest.

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
    
    const auto t = read<i64>();
    for (auto test_case = i64{0}; test_case < t; test_case += 1) {
        const auto k = read<i64>();
        auto three = i64{0};
        auto two_or_more = i64{0};
        for (auto i = i64{1}; i <= k; i += 1) {
            const auto c = read<i64>();
            if (c >= 2) {
                two_or_more += 1;
                if (c >= 3) {
                    three += 1;
                }
            }
        }
        if (two_or_more >= 2 || three >= 1) {
            std::cout << "yes\n";
        } else {
            std::cout << "no\n";
        }
    }

    return 0;
}
