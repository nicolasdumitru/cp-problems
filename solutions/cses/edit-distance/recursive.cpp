// === Problem Information ===
// Name: Edit Distance
// Statement URL: https://cses.fi/problemset/task/1639/

// === Solution Information ===
// Copyright (C) 2025 Nicolas Dumitru
// SPDX-License-Identifier: GPL-3.0-or-later
// Submission URL: https://cses.fi/problemset/result/16477420/
// Verdict: ACCEPTED

#include <algorithm>
#include <cctype>
#include <cstdint>
#include <iostream>
#include <istream>
#include <vector>

using i32 = std::int32_t;

auto levenshtein_distance(const std::vector<char> a, const std::vector<char> b) -> i32 {
    auto dist = std::vector<std::vector<i32>>(a.size(), std::vector<i32>(b.size(), -1));

    const auto dp = [&](const auto &self, const i32 i, const i32 j) -> i32 {
        if (i < 0 || j < 0) {
            return std::max(i, j) + 1;
        }

        if (dist[i][j] >= 0) {
            return dist[i][j];
        }

        if (a[i] == b[j]) {
            dist[i][j] = self(self, i - 1, j - 1);
        } else {
            dist[i][j] = 1 + std::min(self(self, i - 1, j - 1),
                                      std::min(self(self, i, j - 1), self(self, i - 1, j)));
        }

        return dist[i][j];
    };

    return dp(dp, a.size() - 1, b.size() - 1);
}

auto main() -> int {
    // Fast I/O
    // Disable synchronization between C++ and C I/O for faster input/output
    std::ios::sync_with_stdio(false);
    // Untie cin from cout to prevent automatic flushing of cout before each cin
    std::cin.tie(nullptr);

    const auto read_word = []() -> std::vector<char> {
        auto word = std::vector<char>();
        char c = std::cin.get();
        while (std::isalpha(c)) {
            word.push_back(std::toupper(c));
            c = std::cin.get();
        }
        return word;
    };

    const auto a = read_word();
    const auto b = read_word();

    std::cout << levenshtein_distance(a, b);

    return 0;
}
