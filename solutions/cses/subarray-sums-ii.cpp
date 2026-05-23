// === Problem Information ===
// Name: Subarray Sums II
// Statement URL: https://cses.fi/problemset/task/1661/

// === Solution Information ===
// Copyright (C) 2025 Nicolas Dumitru
// SPDX-License-Identifier: GPL-3.0-or-later
// C++ standard: C++20
// Submission URL: https://cses.fi/problemset/result/17273829/
// Verdict: ACCEPTED

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

auto main() -> int {
    // Fast I/O
    // Disable synchronization between C++ and C I/O for faster input/output
    std::ios::sync_with_stdio(false);
    // Untie cin from cout to prevent automatic flushing of cout before each cin
    std::cin.tie(nullptr);

    const auto n = read<i64>();
    const auto x = read<i64>();

    auto count = i64{0};
    auto prev_pref = i64{0};
    if (x == 0) {
        // technically, the general algorithm works for 0 too, but this is likely clearer and faster
        for (auto r = i64{1}; r <= n; r += 1) {
            const auto a = read<i64>();
            const auto pref = prev_pref + a;
            if (pref == 0) {
                count += 1;
            }
        }

        count = count * (count + 1) / 2;
    } else {
        auto freq = std::map<i64, i64>();

        freq[prev_pref] = 1; // avoid checking pref == x for every count update
        for (auto r = i64{1}; r <= n; r += 1) {
            const auto a = read<i64>();
            const auto pref = prev_pref + a;
            count += freq[pref - x];
            freq[pref] += 1;
            prev_pref = pref;
        }
    }

    std::cout << count << '\n';

    return 0;
}
