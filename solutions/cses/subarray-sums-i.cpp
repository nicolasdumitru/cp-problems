// === Problem Information ===
// Name: Subarray Sums I
// Statement URL: https://cses.fi/problemset/task/1660/

// === Solution Information ===
// Copyright (C) 2025 Nicolas Dumitru
// SPDX-License-Identifier: GPL-3.0-or-later
// C++ standard: C++20
// Submission URL: https://cses.fi/problemset/result/17272066/
// Verdict: ACCEPTED

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

auto main() -> int {
    // Fast I/O
    // Disable synchronization between C++ and C I/O for faster input/output
    std::ios::sync_with_stdio(false);
    // Untie cin from cout to prevent automatic flushing of cout before each cin
    std::cin.tie(nullptr);

    const auto n = read<i64>();
    const auto x = read<i64>();
    const auto a = read_vector<i64>(n);
    auto pref = std::vector<i64>(a.size() + 1, 0);

    auto l = i64{0};
    auto count = i64{0};
    for (auto r = i64{1}; r < std::ssize(pref); r += 1) {
        pref[r] = pref[r - 1] + a[r - 1];
        while (pref[r] - pref[l] >= x) {
            if (pref[r] - pref[l] == x) {
                count += 1;
            }
            l += 1;
        }
    }

    std::cout << count << '\n';

    return 0;
}
