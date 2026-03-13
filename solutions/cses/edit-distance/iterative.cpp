// === Problem Information ===
// Name: Edit Distance
// Statement URL: https://cses.fi/problemset/task/1639/

// === Solution Information ===
// Copyright (C) 2025 Nicolas Dumitru
// SPDX-License-Identifier: GPL-3.0-or-later
// Submission URL: https://cses.fi/problemset/result/16548698/
// Verdict: ACCEPTED

#include <algorithm>
#include <cctype>
#include <cstdint>
#include <iostream>
#include <istream>
#include <iterator>
#include <utility>
#include <vector>

using i32 = std::int32_t;

auto levenshtein_distance(const std::vector<char> &a, const std::vector<char> &b) -> i32 {
    const auto [shorter, longer] = (a.size() < b.size()) ? std::tie(a, b) : std::tie(b, a);

    auto prev_row = std::vector<i32>(std::ssize(shorter) + 1);
    auto curr_row = std::vector<i32>(std::ssize(shorter) + 1);

    for (auto j = i32{0}; j <= std::ssize(shorter); j += 1) {
        curr_row[j] = j;
    }

    for (auto i = i32{1}; i <= std::ssize(longer); i += 1) {
        std::swap(curr_row, prev_row);
        curr_row[0] = i;
        for (auto j = i32{1}; j <= std::ssize(shorter); j += 1) {
            curr_row[j] = longer[i - 1] == shorter[j - 1]
                              ? prev_row[j - 1]
                              : 1 + std::min({curr_row[j - 1], prev_row[j - 1], prev_row[j]});
        }
    }

    return curr_row.back();
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
