// === Problem Information ===
// Name: A - Frog 1
// Statement URL: https://atcoder.jp/contests/dp/tasks/dp_a

// === Solution Information ===
// Copyright (C) 2025 Nicolas Dumitru
// SPDX-License-Identifier: GPL-3.0-or-later
// Submission URL: https://atcoder.jp/contests/dp/submissions/73358427
// Verdict: AC

#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <istream>
#include <vector>

using i32 = std::int32_t;
using i64 = std::int64_t;

template <typename T>
inline auto read(std::istream &input = std::cin) -> T {
    T value;
    input >> value;
    return value;
}

template <typename T>
inline auto read_vector(i64 n, std::istream &input = std::cin) -> std::vector<T> {
    auto v = std::vector<T>();
    v.reserve(n);
    for (auto i = i64{0}; i < n; i += 1) {
        v.push_back(read<T>(input));
    }
    return v;
}

auto compute_minimum_costs(const std::vector<i32> &heights) -> std::vector<i32> {
    auto costs = std::vector<i32>(heights.size());
    costs[0] = 0;
    const auto delta = [&](const i32 i, const i32 j) -> i32 {
        return std::abs(heights[i] - heights[j]);
    };
    costs[1] = delta(1, 0);
    for (auto i = i32{2}; i < static_cast<i32>(costs.size()); i += 1) {
        costs[i] = std::min(costs[i - 2] + delta(i, i - 2), costs[i - 1] + delta(i, i - 1));
    }
    return costs;
}

auto main() -> int {
    // Fast I/O
    // Disable synchronization between C++ and C I/O for faster input/output
    std::ios::sync_with_stdio(false);
    // Untie cin from cout to prevent automatic flushing of cout before each cin
    std::cin.tie(nullptr);

    const auto n = read<i32>();
    const auto heights = read_vector<i32>(n);
    
    std::cout << compute_minimum_costs(heights).back() << '\n';

    return 0;
}
