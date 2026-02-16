// === Problem Information ===
// Name: Course Schedule
// Statement URL: https://cses.fi/problemset/submit/1679/

// === Solution Information ===
// Copyright (C) 2025 Nicolas Dumitru
// SPDX-License-Identifier: GPL-3.0-or-later
// Submission URL: https://cses.fi/problemset/result/16285066/
// Verdict: ACCEPTED

#include <cstdint>
#include <iostream>
#include <istream>
#include <queue>
#include <utility>
#include <vector>

using i64 = std::int64_t;

template <typename T>
inline auto read(std::istream &input = std::cin) -> T {
    T value;
    input >> value;
    return value;
}

template <typename T>
using AdjLists = std::vector<std::vector<T>>;

auto read_directed_graph(const i64 num_vertices, const i64 num_edges)
    -> std::pair<AdjLists<i64>, std::vector<i64>> {
    auto adj = AdjLists<i64>(num_vertices + 1); // 1-indexed
    auto in_degrees = std::vector<i64>(adj.size(), 0);
    for (auto i = i64{0}; i < num_edges; i += 1) {
        const auto from = read<i64>();
        const auto to = read<i64>();
        adj[from].push_back(to);
        in_degrees[to] += 1;
    }
    return {adj, in_degrees};
}

/**
 * Kahn's algorithm (BFS based topological sorting)
 */
auto topo_sort_kahn(const AdjLists<i64> &adj, std::vector<i64> &in_degrees) -> std::pair<bool, std::vector<i64>> {
    const auto num_vertices = static_cast<i64>(adj.size() - 1);
    auto sorted_vertices = std::vector<i64>();
    sorted_vertices.reserve(num_vertices);
    auto queue = std::queue<i64>();
    const auto try_enqueue = [&](const i64 v) -> void {
        if (in_degrees[v] == 0) {
            queue.push(v);
        }
    };
    for (auto u = i64{1}; u <= num_vertices; u += 1) {
        try_enqueue(u);
    }
    while (!queue.empty()) {
        const auto u = queue.front();
        queue.pop();
        sorted_vertices.push_back(u);
        for (const auto v : adj[u]) {
            in_degrees[v] -= 1;
            try_enqueue(v);
        }
    }
    if (std::cmp_equal(sorted_vertices.size(), num_vertices)) {
        return {true, sorted_vertices};
    } else {
        return {false, std::vector<i64>()};
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
    
    auto [adj, in_degrees] = read_directed_graph(n, m);
    const auto [is_valid, sorted_vertices] = topo_sort_kahn(adj, in_degrees);
    if (is_valid) {
        for (const auto u : sorted_vertices) {
            std::cout << u << ' ';
        }
        std::cout.put('\n');
    } else {
        std::cout << "IMPOSSIBLE\n";
    }

    return 0;
}
