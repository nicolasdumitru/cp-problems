// === Problem Information ===
// Name: Subarray Divisibility
// Statement URL: https://cses.fi/problemset/task/1662/

// === Solution Information ===
// Copyright (C) 2025 Nicolas Dumitru
// SPDX-License-Identifier: GPL-3.0-or-later
// C++ standard: C++20
// Submission URL: https://cses.fi/problemset/result/17274215/
// Verdict: ACCEPTED

#include <cstdint>
#include <iostream>
#include <istream>
#include <vector>

using i64 = std::int64_t;

template <typename T>
inline auto read(std::istream &input = std::cin) -> T {
    T value;
    input >> value;
    return value;
}

/**
 * Computes `binom(n, 2)`
 */
auto binom2(const i64 n) -> i64 {
    return n * (n - 1) / 2;
}

auto main() -> int {
    // Fast I/O
    // Disable synchronization between C++ and C I/O for faster input/output
    std::ios::sync_with_stdio(false);
    // Untie cin from cout to prevent automatic flushing of cout before each cin
    std::cin.tie(nullptr);

    const auto n = read<i64>();

    auto freq = std::vector<i64>(n, 0);
    auto prev_pref = 0;

    for (auto i = i64{0}; i < n; i += 1) {
        const auto a = read<i64>();
        const auto pref = ((prev_pref + a) % n + n) % n;
        freq[pref] += 1;
        prev_pref = pref;
    }

    auto count = i64{0};
    // When i == 0, we need to add to the count not only the unordered pairs of prefixes which are
    // congruent to 0 modulo n, but also the number of prefixes, as each one, by itself, constitutes
    // a subarray whose sum is divisible by n. This edge case is handled by incrementing freq[0].
    // This works because binom(n, 2) + n == binom(n + 1, 2) for all natural n and, if freq[0]
    // happens to be 0 before incrementing, integer division ensures binom(0 + 1, 2) == 0.
    freq[0] += 1; // n -> n + 1
    for (auto i = i64{0}; i < n; i += 1) {
        count += binom2(freq[i]);
    }

    std::cout << count << '\n';

    return 0;
}
