// === Problem Information ===
// Name: Test 2 - 1.2 - Arborele Filogenetic - Usoara
// Statement URL:
// https://www.hackerrank.com/contests/test-practic-pa-2017-v2-meeseeks/challenges/test-2-arborele-filogenetic-medie

// === Solution Information ===
// Copyright (C) 2025 Nicolas Dumitru
// SPDX-License-Identifier: GPL-3.0-or-later
// C++ standard: C++11 or older?
// Submission URL:
// https://www.hackerrank.com/contests/test-practic-pa-2017-v2-meeseeks/challenges/test-2-arborele-filogenetic-medie/submissions/code/1408568932
// Verdict: Accepted

#include <algorithm>
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

template <typename T>
inline auto read_vector(i64 n, std::istream &input = std::cin) -> std::vector<T> {
    std::vector<T> v(n);
    for (auto &&x : v) {
        x = read<T>(input);
    }
    return v;
}

auto read_parents(const i64 num_vertices) -> std::vector<i64> {
    auto parents = read_vector<i64>(num_vertices);
    for (auto &p : parents) {
        p = p == -1 ? -1 : p - 1;
    }
    return parents;
}

auto find_depth(const i64 u, const std::vector<i64> &parents, std::vector<i64> &depth) -> void {
    if (parents[u] == -1) {
        depth[u] = 0;
        return;
    } else if (depth[u] != -1) { // already computed
        return;
    }

    find_depth(parents[u], parents, depth);
    depth[u] = 1 + depth[parents[u]];
};

auto main() -> int {
    // Fast I/O
    // Disable synchronization between C++ and C I/O for faster input/output
    std::ios::sync_with_stdio(false);
    // Untie cin from cout to prevent automatic flushing of cout before each cin
    std::cin.tie(nullptr);

    const auto num_vertices = read<i64>();
    const auto parents = read_parents(num_vertices);

    auto depth = std::vector<i64>(num_vertices, -1);

    auto max_height = i64{0};
    for (auto i = i64{0}; i < num_vertices; i += 1) {
        find_depth(i, parents, depth);
        max_height = std::max(max_height, depth[i]);
    }

    std::cout << max_height + 1 << '\n';

    return 0;
}
