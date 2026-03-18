// === Problem Information ===
// Name: Array Description
// Statement URL: https://cses.fi/problemset/task/1746/

// === Solution Information ===
// Copyright (C) 2025 Nicolas Dumitru
// SPDX-License-Identifier: GPL-3.0-or-later
// Submission URL: https://cses.fi/problemset/result/16603376/
// Verdict: ACCEPTED

#include <cstdint>
#include <iostream>
#include <istream>
#include <iterator>
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

auto count_arrays(const std::vector<i64> &v, const i64 upper_bound,
                  const i64 modulus = static_cast<i64>(1e9 + 7)) -> i64 {
    auto result = i64{1};
    auto prev = std::vector<i64>(upper_bound + 2, 0);
    auto curr = std::vector<i64>(upper_bound + 2, 0);

    if (v.front() == 0) {
        for (auto j = i64{1}; j <= upper_bound; j += 1) {
            prev[j] = i64{1};
        }
    } else {
        prev[v.front()] = 1;
    }
    for (auto i = i64{1}; i < std::ssize(v); i += 1) {
        if (v[i] == 0) {
            for (auto j = i64{1}; j <= upper_bound; j += 1) {
                curr[j] = (prev[j - 1] + prev[j] + prev[j + 1]) % modulus;
            }
        } else {
            result = result * (prev[v[i] - 1] + prev[v[i]] + prev[v[i] + 1] % modulus) % modulus;

            for (auto j = i64{1}; j <= upper_bound; j += 1) {
                curr[j] = i64{0};
            }
            curr[v[i]] = 1;
        }
        std::swap(curr, prev);
    }

    if (v.back() == 0) {
        auto sum = i64{0};
        for (auto j = i64{1}; j <= upper_bound; j += 1) {
            sum = (sum + prev[j]) % modulus;
        }
        result = result * sum % modulus;
    }

    return result;
}

auto main() -> int {
    // Fast I/O
    // Disable synchronization between C++ and C I/O for faster input/output
    std::ios::sync_with_stdio(false);
    // Untie cin from cout to prevent automatic flushing of cout before each cin
    std::cin.tie(nullptr);

    const auto n = read<i64>();
    const auto m = read<i64>();
    const auto v = read_vector<i64>(n);

    std::cout << count_arrays(v, m);

    return 0;
}
