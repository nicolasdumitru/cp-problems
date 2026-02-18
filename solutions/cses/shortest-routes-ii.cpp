// === Problem Information ===
// Name: Shortest Routes II
// Statement URL: https://cses.fi/problemset/task/1672/

// === Solution Information ===
// Copyright (C) 2025 Nicolas Dumitru
// SPDX-License-Identifier: GPL-3.0-or-later
// Submission URL: https://cses.fi/problemset/result/16308941/
// Verdict: ACCEPTED

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <istream>
#include <iterator>
#include <vector>

using i32 = std::int32_t;
using i64 = std::int64_t;

template <typename T>
inline auto read(std::istream &input = std::cin) -> T {
    T value;
    input >> value;
    return value;
}

const auto INF = static_cast<i64>(1e18);

auto floyd_warshall(std::vector<std::vector<i64>> &distances) {
    const auto first_vertex = i64{1};
    const auto n = std::ssize(distances);
    for (auto w = first_vertex; w < n; w += 1) {
        for (auto u = first_vertex; u < n; u += 1) {
            for (auto v = first_vertex; v < n; v += 1) {
                distances[u][v] = std::min(distances[u][v], distances[u][w] + distances[w][v]);
            }
        }
    }
}

auto main() -> int {
    // Fast I/O
    // Disable synchronization between C++ and C I/O for faster input/output
    std::ios::sync_with_stdio(false);
    // Untie cin from cout to prevent automatic flushing of cout before each cin
    std::cin.tie(nullptr);

    const auto n = read<i64>();
    const auto m = read<i64>();
    const auto q = read<i64>();

    auto distances = std::vector(n + 1, std::vector<i64>(n + 1, INF));

    for (auto u = i64{1}; u < std::ssize(distances); u += 1) {
        distances[u][u] = 0;
    }

    for (auto i = i64{0}; i < m; i += 1) {
        const auto u = read<i64>();
        const auto v = read<i64>();
        const auto weight = read<i64>();

        if (u != v && weight < distances[u][v]) {
            distances[u][v] = weight;
            distances[v][u] = weight;
        }
    }

    floyd_warshall(distances);

    for (auto i = i64{0}; i < q; i += 1) {
        const auto u = read<i64>();
        const auto v = read<i64>();

        std::cout << (distances[u][v] < INF ? distances[u][v] : -1) << '\n';
    }

    return 0;
}
