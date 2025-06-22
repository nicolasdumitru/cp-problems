// === Problem Information ===
// Name: Distinct Numbers
// Statement URL: https://cses.fi/problemset/task/1621

// === Solution Information ===
// Copyright (C) 2025 Nicolas Dumitru
// SPDX-License-Identifier: GPL-3.0-or-later
// Submission URL: https://cses.fi/problemset/result/13409118/
// Verdict: ACCEPTED

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <ranges>
#include <set>

using usize = std::size_t;
using u32 = std::uint32_t;

template <typename T>
inline auto read(std::istream &input = std::cin) -> T {
    T value;
    input >> value;
    return value;
}

auto main() -> int {
    std::ios::sync_with_stdio(false);

    const auto n = read<usize>();
    std::set<usize> s;

    for ([[maybe_unused]] const usize _ : std::views::iota(usize{0}, n)) {
        s.insert(read<u32>());
    }

    std::cout << s.size() << '\n';

    return 0;
}
