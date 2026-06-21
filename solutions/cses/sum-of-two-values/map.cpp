// === Problem Information ===
// Name: Sum of Two Values
// Statement URL: https://cses.fi/problemset/task/1640

// === Solution Information ===
// Copyright (C) 2025 Nicolas Dumitru
// SPDX-License-Identifier: GPL-3.0-or-later
// Submission URL: https://cses.fi/problemset/result/13409546/
// Verdict: ACCEPTED

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <map>

using usize = std::size_t;
using i32 = std::int32_t;

template <typename T>
inline auto read(std::istream &input = std::cin) -> T {
    T value;
    input >> value;
    return value;
}

auto main() -> int {
    std::ios::sync_with_stdio(false);

    const auto n = read<usize>();
    const auto x = read<i32>();
    std::map<i32, usize> m;

    bool found = false;
    for (usize i = 1; i <= n && !found; i += 1) {
        const auto key = read<i32>();
        auto complement = m.find(x - key);
        if (complement != m.end()) {
            found = true;
            std::cout << i << ' ' << complement->second << '\n';
        } else {
            m[key] = i;
        }
    }

    if (!found) {
        std::cout << "IMPOSSIBLE\n";
    }

    return 0;
}
