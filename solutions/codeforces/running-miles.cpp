// === Problem Information ===
// Name: D. Running Miles
// Statement URL: https://codeforces.com/contest/1826/problem/D

// === Solution Information ===
// Copyright (C) 2025 Nicolas Dumitru
// SPDX-License-Identifier: GPL-3.0-or-later
// C++ standard: C++20
// Submission URL: https://codeforces.com/contest/1826/submission/379432117
// Verdict: Accepted

// Core idea
// Objective: maximize b[l] + b[m] + b[r] - (r - l) for some indices 0 <= l < m < r < n
// b[l] + b[m] + b[r] - (r - l) = (b[l] + l) + b[m] + (b[r] - r)
// It now suffices to choose pref_max[m] = max(b[l] + l for l in range(m)) and
// suf_max[m] = max(b[r] - r for r in range(m + 1, n)) for each m and iterate through the possible
// values of m

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <istream>
#include <iterator>
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

    const auto NEG_INF_i64 = i64{std::numeric_limits<i64>::min()};

    const auto num_tests = read<i64>();

    for (auto t = i64{0}; t < num_tests; t += 1) {
        const auto n = read<i64>();
        const auto b = read_vector<i64>(n);
        auto suf_max = std::vector<i64>(n, NEG_INF_i64);
        for (auto m = i64{n - 2}; m >= 1; m -= 1) {
            suf_max[m] = std::max(suf_max[m + 1], b[m + 1] - (m + 1));
        }
        auto pref_max = NEG_INF_i64;
        auto max_beauty = NEG_INF_i64;
        for (auto m = i64{1}; m < std::ssize(b) - 1; m += 1) {
            pref_max = std::max(pref_max, i64{b[m - 1] + (m - 1)});
            max_beauty = std::max(max_beauty, pref_max + b[m] + suf_max[m]);
        }
        std::cout << max_beauty << '\n';
    }

    return 0;
}
