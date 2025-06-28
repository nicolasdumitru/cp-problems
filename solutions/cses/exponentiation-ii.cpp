// === Problem Information ===
// Name: Exponentiation II
// Statement URL: https://cses.fi/problemset/task/1712

// === Solution Information ===
// Copyright (C) 2025 Nicolas Dumitru
// SPDX-License-Identifier: GPL-3.0-or-later
// Submission URL: https://cses.fi/problemset/result/13489484/
// Verdict: ACCEPTED

#include <cstdint>
#include <iostream>
#include <ranges>

using u32 = std::uint_fast32_t;
using u64 = std::uint_fast64_t;

template <typename T>
inline auto read(std::istream &input = std::cin) -> T {
    T value;
    input >> value;
    return value;
}

inline auto is_odd(const u64 n) -> bool {
    return (n & 1) == 1;
}

const u32 PRIME = 1'000'000'000 + 7; // prime number
auto mod_pow(const u32 base, const u32 exponent, const u32 modulus = PRIME)
    -> u32 {
    const u64 m = modulus;
    u64 b = base % modulus;
    u64 e = exponent;
    u64 res = 1;

    while (e >= 1) {
        if (is_odd(e)) {
            res = res * b % m;
        }
        b = b * b % m;
        e >>= 1;
    }
    return static_cast<u32>(res);
}

auto main() -> int {
    std::ios::sync_with_stdio(false);

    const auto n = read<u32>();

    for ([[maybe_unused]] const auto _ : std::views::iota(u32{0}, n)) {
        const auto a = read<u32>();
        const auto b = read<u32>();
        const auto c = read<u32>();
        std::cout << mod_pow(a, mod_pow(b, c, PRIME - 1), PRIME) << '\n';
    }

    return 0;
}
