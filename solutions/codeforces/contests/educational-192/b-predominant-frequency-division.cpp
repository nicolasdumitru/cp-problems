// === Problem Information ===
// Name: B. Predominant Frequency Division
// Statement URL: https://codeforces.com/contest/2242/problem/B

// === Solution Information ===
// Copyright (C) 2025 Nicolas Dumitru
// SPDX-License-Identifier: GPL-3.0-or-later
// C++ standard: C++20
// Submission URL: https://codeforces.com/contest/2242/submission/381498680
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

    const auto num_tests = read<i64>();
    for (auto t = i64{0}; t < num_tests; t += 1) {
        const auto n = read<i64>();
        const auto a = read_vector<i64>(n);
        auto c1 = std::vector<i64>(n);
        c1[0] = 0;
        for (auto i = i64{1}; i < n; i += 1) {
            c1[i] = c1[i - 1] + (a[i - 1] == 1 ? 1 : 0);
        }
        auto possible = false;
        auto count = std::vector<i64>(4, 0);
        for (auto i = i64{n - 2}; i > 0; i -= 1) {
            count[a[i]] += 1;
            if (count[1] + count[2] < count[3]) {
                count[1] = 0;
                count[2] = 0;
                count[3] = 0;
            } else if (2 * c1[i] >= i) {
                possible = true;
                break;
            }
        }
        if (possible) {
            std::cout << "yes\n";
        } else {
            std::cout << "no\n";
        }
    }

    return 0;
}
