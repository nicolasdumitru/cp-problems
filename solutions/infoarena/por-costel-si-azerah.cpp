// === Problem Information ===
// Name: Por Costel si Azerah
// Statement URL: https://www.infoarena.ro/problema/azerah

// === Solution Information ===
// Copyright (C) 2025 Nicolas Dumitru
// SPDX-License-Identifier: GPL-3.0-or-later
// C++ standard: C++14
// Submission URL: https://www.infoarena.ro/job_detail/3355455
// Verdict: 100/100

#include <cstdint>
#include <fstream>
#include <iostream>
#include <istream>

using i64 = std::int64_t;

const auto MOD = i64{1'000'000'007};

auto fin = std::ifstream("azerah.in");

template <typename T>
inline auto read(std::istream &input = fin) -> T {
    T value;
    input >> value;
    return value;
}

auto main() -> int {
    const auto num_tests = read<i64>();

    auto fout = std::ofstream("azerah.out");
    for (auto t = i64{0}; t < num_tests; t += 1) {
        const auto n = read<i64>();
        auto num_evens = i64{0};
        auto num_odds = i64{0};
        auto prev_evens = i64{0};
        auto prev_odds = i64{0};
        for (auto i = i64{0}; i < n; i += 1) {
            const auto x = read<i64>();
            // odd + odd = even
            if ((x & 1) == 0) {
                num_evens = ((prev_evens << 1) % MOD + 1) %
                            MOD;                   // even + even = even; the last is even by itself
                num_odds = (prev_odds << 1) % MOD; // odd + even = odd
            } else {
                num_evens = (prev_evens + prev_odds) % MOD; // odd + odd = even
                num_odds = (num_odds + (prev_evens + 1) % MOD) %
                           MOD; // even + odd = odd; the last is odd by itself
            }
            prev_evens = num_evens;
            prev_odds = num_odds;
        }
        fout << num_evens << '\n';
    }

    return 0;
}
