// === Problem Information ===
// Name: Distinct Numbers
// Statement URL: https://cses.fi/problemset/task/1621

// === Solution Information ===
// Copyright (C) 2025 Nicolas Dumitru
// SPDX-License-Identifier: GPL-3.0-or-later
// Submission URL: https://cses.fi/problemset/result/13409049/
// Verdict: ACCEPTED

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <ranges>
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
inline auto read_vector(usize n, std::istream &input = std::cin)
    -> std::vector<T> {
    std::vector<T> v(n);
    for (auto &&x : v) {
        x = read<T>(input);
    }
    return v;
}

auto main() -> int {
    std::ios::sync_with_stdio(false);

    const auto n = read<usize>();
    auto v = read_vector<u32>(n);

    std::sort(v.begin(), v.end());
    u32 prev = v[0];
    usize distincts = 1;
    for (const u32 x : std::views::drop(v, 1)) {
        if (x != prev) {
            prev = x;
            distincts += 1;
        }
    }

    std::cout << distincts << '\n';

    return 0;
}
