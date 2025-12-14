// === Problem Information ===
// Name: 1900D. Small GCD
// Statement URL: https://codeforces.com/contest/1900/problem/D

// === Solution Information ===
// Copyright (C) 2025 Nicolas Dumitru
// SPDX-License-Identifier: GPL-3.0-or-later
// Submission URL: https://codeforces.com/contest/1900/submission/353390235
// Verdict: Accepted

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

using u64 = std::uint_fast64_t;

template <typename T>
inline auto read(std::istream &input = std::cin) -> T {
    T value;
    input >> value;
    return value;
}

template <typename T>
inline auto read_vector(u64 n, std::istream &input = std::cin) -> std::vector<T> {
    std::vector<T> v(n);
    for (auto &&x : v) {
        x = read<T>(input);
    }
    return v;
}

auto compute_frequencies(const std::vector<u64> &v) -> std::vector<u64> {
    const auto max = *std::max_element(v.begin(), v.end());
    auto freq = std::vector<u64>(max + 1, 0);
    for (const auto x : v) {
        freq[x] += 1;
    }
    return freq;
}

// r[i] is the sum of the frequencies of numbers strictly greater than i
auto compute_r(const std::vector<u64> &freq) -> std::vector<u64> {
    auto r = std::vector<u64>(freq.size(), 0);
    u64 count = 0;
    for (u64 i = 0; i < freq.size(); i += 1) {
        const u64 j = freq.size() - 1 - i;
        r[j] += count;
        count += freq[j];
    }
    return r;
}

inline constexpr auto n_choose_2(const u64 n) -> u64 {
    return n * (n - 1) / 2;
}

inline constexpr auto n_choose_3(const u64 n) -> u64 {
    return n * (n - 1) * (n - 2) / 6;
}

// Compute the sum of f(a, b, c) for all triples (a[i], a[j], a[k]) with i < j < k as the sum of
// x * t[x] over all relevant x, where t[x] is the number of triples satisfying f == x.
auto sum_small_gcd(const std::vector<u64> &a) -> u64 {
    const auto freq = compute_frequencies(a);
    const auto r = compute_r(freq);
    auto t = std::vector<u64>(freq.size(), 0);
    u64 sum = 0;
    for (u64 x = freq.size() - 1; x >= 1; x -= 1) {
        u64 l = 0; // number of multiples of x strictly less than b
        // Let t'[x] be the number of triples satisfying f == k * x for all natural k.
        // Then t[x] = t'[x] - t[2 * x] - t[3 * x] - ...
        for (u64 b = x; b < freq.size(); b += x) {
            t[x] -= t[b];
            // 4 cases for (a, b, c) triples:
            // 1. a < b < c => l * freq[b] * r triples
            // 2. a == b < c => (freq[b] choose 2) * r triples
            // 3. a < b == c => l * (freq[b] choose 2) triples
            // 4. a == b == c => (freq[b] choose 3) triples
            const auto freq_b_choose_2 = n_choose_2(freq[b]);
            t[x] +=
                (l * freq[b] + freq_b_choose_2) * r[b] + l * freq_b_choose_2 + n_choose_3(freq[b]);
            l += freq[b];
        }
        sum += x * t[x];
    }
    return sum;
}

auto main() -> int {
    std::ios::sync_with_stdio(false); // Disable synchronization between C++ and
                                      // C I/O for faster input/output
    std::cin.tie(nullptr);            // Untie cin from cout to prevent automatic
                                      // flushing of cout before each cin
    const auto t = read<u64>();
    for (u64 i = 0; i < t; i++) {
        const auto n = read<u64>();
        auto a = read_vector<u64>(n);
        std::cout << sum_small_gcd(a) << "\n";
        std::cout.flush();
    }

    return 0;
}
