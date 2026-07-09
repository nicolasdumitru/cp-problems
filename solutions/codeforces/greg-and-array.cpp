// === Problem Information ===
// Name: Greg and Array
// Statement URL: https://codeforces.com/contest/295/problem/A

// === Solution Information ===
// Copyright (C) 2025 Nicolas Dumitru
// SPDX-License-Identifier: GPL-3.0-or-later
// C++ standard: C++23
// Submission URL: https://codeforces.com/contest/295/submission/381838202
// Verdict: Accepted

#include <cstdint>
#include <iostream>
#include <istream>
#include <iterator>
#include <ranges>
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

struct Operation {
    i64 l;
    i64 r;
    i64 d;
};

auto main() -> int {
    // Fast I/O
    // Disable synchronization between C++ and C I/O for faster input/output
    std::ios::sync_with_stdio(false);
    // Untie cin from cout to prevent automatic flushing of cout before each cin
    std::cin.tie(nullptr);

    const auto n = read<i64>();
    const auto m = read<i64>();
    const auto k = read<i64>();

    const auto a = read_vector<i64>(n);

    const auto ops = [&m]() -> std::vector<Operation> {
        auto ops = std::vector<Operation>(m);
        for (auto i = i64{0}; i < m; i += 1) {
            ops[i].l = read<i64>() - 1;
            ops[i].r = read<i64>();
            ops[i].d = read<i64>();
        }

        ops.push_back(Operation{0, 0, 0});

        return ops;
    }();

    const auto op_freqs = [&ops, k]() -> std::vector<i64> {
        auto op_freqs = std::vector<i64>(ops.size(), 0);

        for (auto i = i64{0}; i < k; i += 1) {
            const auto x = read<i64>() - 1;
            const auto y = read<i64>();

            op_freqs[x] += 1;
            op_freqs[y] -= 1;
        }

        for (auto i = i64{1}; i < std::ssize(op_freqs); i += 1) {
            op_freqs[i] += op_freqs[i - 1];
        }

        return op_freqs;
    }();

    const auto diffs = [&a, &ops, &op_freqs]() -> std::vector<i64> {
        auto diffs = std::vector<i64>(a.size() + 1, 0);

        for (const auto [op, freq] : std::views::zip(ops, op_freqs)) {
            const auto delta = freq * op.d;
            diffs[op.l] += delta;
            diffs[op.r] -= delta;
        }

        for (auto i = i64{1}; i < std::ssize(diffs); i += 1) {
            diffs[i] += diffs[i - 1];
        }

        return diffs;
    }();

    for (auto i = i64{0}; i < std::ssize(a); i += 1) {
        std::cout << a[i] + diffs[i] << ' ';
    }
    std::cout.put('\n');

    return 0;
}
