// === Problem Information ===
// Name: FENTREE - Fenwick Trees
// Statement URL: https://www.spoj.com/problems/FENTREE/

// === Solution Information ===
// Copyright (C) 2025 Nicolas Dumitru
// SPDX-License-Identifier: GPL-3.0-or-later
// Submission URL: https://www.spoj.com/status/FENTREE,bqp/
// Verdict: accepted

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>

using usize = std::size_t;
using isize = std::ptrdiff_t;
using i64 = std::int_fast64_t;

template <typename T>
inline auto read(std::istream &input = std::cin) -> T {
    T value;
    input >> value;

    return value;
}

template <typename T>
inline auto read_vector(usize n, std::istream &input = std::cin)
    -> std::vector<T> {
    std::vector<T> v(n);
    for (auto &&x : v) {
        x = read<T>(input);
    }

    return v;
}

class FenwickTree {
    std::vector<i64> bit;

    inline auto g(const usize i) -> usize {
        return i & (i + 1);
    }

    inline auto h(const usize i) -> usize {
        return i | (i + 1);
    }

public:
    FenwickTree(const std::vector<i64> &v) : bit(v.size(), 0) {
        for (usize i = 0; i < bit.size(); i += 1) {
            bit[i] += v[i];
            if (h(i) < v.size()) {
                bit[h(i)] += bit[i];
            }
        }
    }

    auto update(const usize pos, i64 delta) -> void {
        for (auto i = pos; i < bit.size(); i = h(i)) {
            bit[i] += delta;
        }
    }

    auto query(const usize pos) -> i64 {
        i64 sum = 0;
        for (auto i = pos + 1; i > 0; i = g(i)) {
            i -= 1;
            sum += bit[i];
        }

        return sum;
    }

    auto query(const usize begin, const usize end) -> i64 {
        return query(end) - (begin > 0 ? query(begin - 1) : 0);
    }
};

auto main() -> int {
    std::ios::sync_with_stdio(false);

    const auto n = read<usize>();
    const auto v = read_vector<i64>(n);

    FenwickTree bit(v);

    const auto q = read<usize>();
    for (usize i = 0; i < q; i += 1) {
        const auto op = read<char>(); // read<T>() will ignore whitespace

        if (op == 'u') { // update operation
            const auto pos = read<usize>() - 1;
            const auto x = read<i64>();

            bit.update(pos, x);
        } else { // query operation
            const auto begin = read<usize>() - 1;
            const auto end = read<usize>() - 1;

            std::cout << bit.query(begin, end) << '\n';
        }
    }

    return 0;
}
