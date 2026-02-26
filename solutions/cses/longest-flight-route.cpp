// === Problem Information ===
// Name: Longest Flight Route
// Statement URL: https://cses.fi/problemset/task/1680/

// === Solution Information ===
// Copyright (C) 2025 Nicolas Dumitru
// SPDX-License-Identifier: GPL-3.0-or-later
// Submission URL: https://cses.fi/problemset/result/16387586/
// Verdict: ACCEPTED

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <istream>
#include <iterator>
#include <queue>
#include <vector>

using i64 = std::int64_t;

template <typename T>
inline auto read(std::istream &input = std::cin) -> T {
    T value;
    input >> value;
    return value;
}

const auto NIL_VERTEX = -1;

template <typename T>
using AdjLists = std::vector<std::vector<T>>;

auto read_dag(i64 num_vertices, i64 num_edges) -> AdjLists<i64> {
    auto adj = AdjLists<i64>(num_vertices);
    for (auto i = i64{0}; i < num_edges; i += 1) {
        const auto u = read<i64>();
        const auto v = read<i64>();
        adj[u].push_back(v);
    }
    return adj;
}

auto compute_in_degrees(const AdjLists<i64> &adj) -> std::vector<i64> {
    auto in_degrees = std::vector<i64>(adj.size(), 0);
    for (auto u = i64{0}; u < std::ssize(adj); u += 1) {
        for (const auto v : adj[u]) {
            in_degrees[v] += 1;
        }
    }
    return in_degrees;
}

auto topo_sort(const AdjLists<i64> &adj, const i64 first = 0) -> std::vector<i64> {
    auto in_degrees = compute_in_degrees(adj);

    auto queue = std::queue<i64>();
    const auto try_enqueue = [&](const i64 v) -> void {
        if (in_degrees[v] == 0) {
            queue.push(v);
        }
    };

    for (auto u = first; u < std::ssize(adj); u += 1) {
        try_enqueue(u);
    }

    auto topo_sort = std::vector<i64>();
    topo_sort.reserve(adj.size());
    while (!queue.empty()) {
        const auto u = queue.front();
        queue.pop();
        topo_sort.push_back(u);
        for (const auto v : adj[u]) {
            if (in_degrees[v] != 0) {
                in_degrees[v] -= 1;
            }
            try_enqueue(v);
        }
    }

    return std::ssize(topo_sort) == std::ssize(adj) - first ? topo_sort           // sortable
                                                            : std::vector<i64>(); // not sortable
}

auto compute_longest_path_parents(const AdjLists<i64> &adj, const i64 s) -> std::vector<i64> {
    const auto vertices = topo_sort(adj);
    auto lp_dist = std::vector<i64>(vertices.size(), -1);
    auto parents = std::vector<i64>(adj.size(), NIL_VERTEX);

    lp_dist[s] = 0;

    for (const auto u : vertices) {
        if (lp_dist[u] == -1) {
            continue;
        }
        const auto dist = lp_dist[u] + 1;
        for (const auto v : adj[u]) {
            if (dist > lp_dist[v]) {
                lp_dist[v] = dist;
                parents[v] = u;
            }
        }
    }
    return parents;
}

auto reconstruct_path(const std::vector<i64> &parents, i64 u) -> std::vector<i64> {
    auto longest_path = std::vector<i64>();
    while (u != NIL_VERTEX) {
        longest_path.push_back(u);
        u = parents[u];
    }
    std::reverse(longest_path.begin(), longest_path.end());
    return longest_path;
}

auto main() -> int {
    // Fast I/O
    // Disable synchronization between C++ and C I/O for faster input/output
    std::ios::sync_with_stdio(false);
    // Untie cin from cout to prevent automatic flushing of cout before each cin
    std::cin.tie(nullptr);

    const auto n = read<i64>();
    const auto m = read<i64>();

    const auto adj = read_dag(n + 1, m);

    const auto parents = compute_longest_path_parents(adj, 1);

    const auto longest_path = reconstruct_path(parents, n);

    if (longest_path.front() == 1) {
        std::cout << std::ssize(longest_path) << '\n';
        for (const auto v : longest_path) {
            std::cout << v << ' ';
        }
        std::cout.put('\n');
    } else {
        std::cout << "IMPOSSIBLE\n";
    }

    return 0;
}
