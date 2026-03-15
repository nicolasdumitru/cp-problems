// === Problem Information ===
// Name: Rectangle Cutting
// Statement URL: https://cses.fi/problemset/task/1744/

// === Solution Information ===
// Copyright (C) 2025 Nicolas Dumitru
// SPDX-License-Identifier: GPL-3.0-or-later
// Submission URL: https://cses.fi/problemset/result/16566158/
// Verdict: ACCEPTED

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <istream>
#include <limits>
#include <utility>
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

auto min_rectangle_cuts(i64 w_max, i64 h_max) -> i64 {
    if (w_max < h_max) {
        std::swap(w_max, h_max);
    }

    if (w_max == h_max || h_max == 0) {
        return i64{0};
    } else if (h_max == 1) {
        return w_max - 1;
    }

    const auto num_rows = w_max + 1;
    const auto num_cols = h_max + 1;
    auto __dp = std::vector<i64>(num_rows * num_cols, std::numeric_limits<i64>::max());
    const auto dp = [&__dp, &num_cols](i64 row, i64 col) -> i64 & {
        if (row < col) {
            std::swap(row, col);
        }
        return __dp[row * num_cols + col];
    };

    for (auto w = i64{0}; w <= w_max; w += 1) {
        // Base cases
        dp(w, 0) = 0;
        dp(w, 1) = w - 1;
        if (w <= h_max) {
            dp(w, w) = 0;
        }

        for (auto h = i64{2}; h < w && h <= h_max; h += 1) {
            // Horizontal cuts
            const auto horizontal_bound = h / 2;
            for (auto i = i64{1}; i <= horizontal_bound; i += 1) {
                dp(w, h) = std::min(dp(w, h), 1 + dp(w, i) + dp(w, h - i));
            }

            // Vertical cuts
            //
            // TODO: Correctness proof? (ACCEPTED on CSES.)
            // const auto vertical_bound = std::min(h, w / 2);
            //
            const auto vertical_bound = w / 2;
            for (auto i = i64{1}; i <= vertical_bound; i += 1) {
                dp(w, h) = std::min(dp(w, h), 1 + dp(i, h) + dp(w - i, h));
            }
        }
    }
    return dp(w_max, h_max);
}

auto main() -> int {
    // Fast I/O
    // Disable synchronization between C++ and C I/O for faster input/output
    std::ios::sync_with_stdio(false);
    // Untie cin from cout to prevent automatic flushing of cout before each cin
    std::cin.tie(nullptr);

    const auto a = read<i64>();
    const auto b = read<i64>();

    std::cout << min_rectangle_cuts(a, b);

    return 0;
}
