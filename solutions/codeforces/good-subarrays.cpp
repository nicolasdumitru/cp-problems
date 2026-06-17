// === Problem Information ===
// Name: C. Good Subarrays
// Statement URL: https://codeforces.com/contest/1398/problem/C

// === Solution Information ===
// Copyright (C) 2025 Nicolas Dumitru
// SPDX-License-Identifier: GPL-3.0-or-later
// C++ standard: C++20
// Submission URL: https://codeforces.com/contest/1398/submission/379427915
// Verdict: Accepted

// Core idea
// Notation: where l:r is the range l, l + 1, ... r - 1
// Definition (good subarray): sum(a[l:r]) = r - l
// Notation (prefix sum): p[i] = sum(a[0:i])
// sum(a[l:r]) = p[r] - p[l]
// Idea:
// p[r] - p[l] = r - l iff
// p[r] - r = p[l] - l.
// Therefore, we compute the frequencies of all the values p[i] - i for all indices i. With these,
// we can compute the number of unordered pairs of distinct indexes (l, r) such that r != l and
// p[r] - r = p[l] - l.
// Note: the formula n * (n - 1) / 2 will compute the needed number of unordered pairs (even when
// the binomial coefficient is technically not defined) because it uses integer division.

#include <cstdint>
#include <iostream>
#include <istream>
#include <map>

using i32 = std::int32_t;
using i64 = std::int64_t;

template <typename T>
inline auto read(std::istream &input = std::cin) -> T {
    T value;
    input >> value;
    return value;
}

auto read_digit() -> i64 {
    const auto c = read<char>();
    return i64{c - '0'};
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
        auto freq = std::map<i64, i64>();
        auto pref_sum = i64{0};
        freq[0] = 1;
        for (auto i = i64{1}; i <= n; i += 1) {
            const auto a = read_digit();
            pref_sum += a;
            if (auto [it, inserted] = freq.try_emplace(pref_sum - i, 1); !inserted) {
                auto &[_, f] = *it;
                f += 1;
            }
        }
        auto count = i64{0};
        for (const auto &[_, f] : freq) {
            count += f * (f - 1) / 2;
        }
        std::cout << count << '\n';
    }

    return 0;
}
