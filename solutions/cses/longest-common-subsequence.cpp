// === Problem Information ===
// Name: Longest Common Subsequence
// Statement URL: https://cses.fi/problemset/task/3403/

// === Solution Information ===
// Copyright (C) 2025 Nicolas Dumitru
// SPDX-License-Identifier: GPL-3.0-or-later
// C++ standard: C++20
// Submission URL: https://cses.fi/problemset/result/17252540/
// Verdict: ACCEPTED

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <istream>
#include <iterator>
#include <tuple>
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

template <typename T>
using Matrix = std::vector<std::vector<T>>;

template <typename T>
auto mat_new(i64 rows, i64 cols, T val) -> Matrix<T> {
    return Matrix<T>(rows, std::vector<T>(cols, val));
}

auto lcs_helper(const std::vector<i64> &a, const std::vector<i64> &b) -> std::vector<i64> {
    const auto rows = std::ssize(a) + 1;
    const auto cols = std::ssize(b) + 1;
    auto dp = mat_new<i64>(rows, cols, 0);
    for (auto i = i64{1}; i < rows; i += 1) {
        for (auto j = i64{1}; j < cols; j += 1) {
            dp[i][j] =
                a[i - 1] == b[j - 1] ? 1 + dp[i - 1][j - 1] : std::max(dp[i - 1][j], dp[i][j - 1]);
        }
    }

    auto [i, j] = std::pair{std::ssize(a), std::ssize(b)};
    auto res = std::vector<i64>();
    res.reserve(dp.back().back());
    while (i > 0 && j > 0) {
        if (a[i - 1] == b[j - 1]) {
            res.push_back(a[i - 1]);
            i -= 1;
            j -= 1;
        } else if (dp[i - 1][j] >= dp[i][j - 1]) {
            i -= 1;
        } else {
            j -= 1;
        }
    }
    std::reverse(res.begin(), res.end());
    return res;
}

auto lcs(const std::vector<i64> &a, const std::vector<i64> &b) -> std::vector<i64> {
    return std::ssize(a) <= std::ssize(b) ? lcs_helper(a, b) : lcs_helper(b, a);
}

auto main() -> int {
    // Fast I/O
    // Disable synchronization between C++ and C I/O for faster input/output
    std::ios::sync_with_stdio(false);
    // Untie cin from cout to prevent automatic flushing of cout before each cin
    std::cin.tie(nullptr);

    const auto n = read<i64>();
    const auto m = read<i64>();

    const auto a = read_vector<i64>(n);
    const auto b = read_vector<i64>(m);

    const auto res = lcs(a, b);
    std::cout << std::ssize(res) << '\n';
    for (const auto x : res) {
        std::cout << x << ' ';
    }
    std::cout.put('\n');

    return 0;
}
