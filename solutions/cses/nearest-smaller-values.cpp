// === Problem Information ===
// Name: Nearest Smaller Values
// Statement URL: https://cses.fi/problemset/task/1645/

// === Solution Information ===
// Copyright (C) 2025 Nicolas Dumitru
// SPDX-License-Identifier: GPL-3.0-or-later
// Submission URL: https://cses.fi/problemset/result/16264754/
// Verdict: ACCEPTED

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <stack>
#include <vector>

using usize = std::size_t;
using u32 = std::uint32_t;

template <typename T>
inline auto read(std::istream &input = std::cin) -> T {
    T value;
    input >> value;
    return value;
}

template <typename T>
inline auto read_vector(usize n, std::istream &input = std::cin) -> std::vector<T> {
    std::vector<T> v(n);
    for (auto &&x : v) {
        x = read<T>(input);
    }
    return v;
}

/**
 * For each element `x[i]` in `x`, find the greatest index `j` such that `j < i && x[j] < x[i]`
 */
auto nearest_smaller_values(const std::vector<u32> &x) -> std::vector<usize> {
    auto s = std::stack<usize>();
    auto nsv = std::vector<usize>(x.size());
    for (usize i = 0; i < x.size(); i += 1) {
        while (!s.empty() && x[s.top()] >= x[i]) {
            s.pop();
        }
        nsv[i] = s.empty() ? 0 : s.top() + 1;
        s.push(i);
    }
    return nsv;
}

auto main() -> int {
    // Fast I/O
    // Disable synchronization between C++ and C I/O for faster input/output
    std::ios::sync_with_stdio(false);
    // Untie cin from cout to prevent automatic flushing of cout before each cin
    std::cin.tie(nullptr);

    const auto n = read<usize>();
    const auto x = read_vector<u32>(n);

    const auto results = nearest_smaller_values(x);

    for (auto idx : results) {
        std::cout << idx << ' ';
    }
    std::cout.put('\n');

    return 0;
}