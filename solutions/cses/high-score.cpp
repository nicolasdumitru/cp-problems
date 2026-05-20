// === Problem Information ===
// Name: High Score
// Statement URL: https://cses.fi/problemset/task/1673/

// === Solution Information ===
// Copyright (C) 2025 Nicolas Dumitru
// SPDX-License-Identifier: GPL-3.0-or-later
// Submission URL: https://cses.fi/problemset/result/17233044/
// Verdict: ACCEPTED

#include <cstdint>
#include <iostream>
#include <istream>
#include <optional>
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

struct Edge {
    i64 from;
    i64 to;
    i64 weight;
};

auto read_graph(const i64 num_vertices, const i64 num_edges)
    -> std::pair<std::vector<Edge>, AdjLists<i64>> {
    auto edges = std::vector<Edge>(num_edges);
    auto adj_transp = AdjLists<i64>(num_vertices);
    for (auto i = i64{0}; i < num_edges; i += 1) {
        const auto from = read<i64>() - 1;
        const auto to = read<i64>() - 1;
        const auto weight = -read<i64>();
        edges[i] = {.from = from, .to = to, .weight = weight};
        adj_transp[to].push_back(from);
    }
    return {edges, adj_transp};
}

auto filter_edges(std::vector<Edge> &edges, const AdjLists<i64> &adj_transp, const i64 &target)
    -> void {
    auto visited = std::vector<bool>(adj_transp.size(), false);
    const auto dfs = [&](auto &self, const i64 v) -> void {
        visited[v] = true;
        for (const auto &u : adj_transp[v]) {
            if (!visited[u]) {
                self(self, u);
            }
        }
    };
    dfs(dfs, target);
    std::erase_if(edges,
                  [&visited](const Edge &e) -> bool { return !visited[e.from] || !visited[e.to]; });
}

auto bellman_ford(const auto num_vertices, const std::vector<Edge> &edges, const i64 source)
    -> std::optional<std::vector<i64>> {
    const auto INF = i64{5'000'000'000'000};
    auto dist = std::vector<i64>(num_vertices, INF);
    dist[source] = 0;
    const auto n = num_vertices - 1;
    for (auto i = i64{0}; i < num_vertices; i += 1) {
        for (const auto &[from, to, weight] : edges) {
            if (dist[from] == INF) {
                continue;
            }
            const auto new_dist = dist[from] + weight;
            if (new_dist < dist[to]) {
                dist[to] = new_dist;
                if (i == n) {
                    return std::nullopt;
                }
            }
        }
    }
    return dist;
}

auto main() -> int {
    // Fast I/O
    // Disable synchronization between C++ and C I/O for faster input/output
    std::ios::sync_with_stdio(false);
    // Untie cin from cout to prevent automatic flushing of cout before each cin
    std::cin.tie(nullptr);

    const auto num_vertices = read<i64>();
    const auto num_edges = read<i64>();

    auto [edges, adj_transp] = read_graph(num_vertices, num_edges);

    const auto n = num_vertices - 1;
    filter_edges(edges, adj_transp, n);

    if (auto opt = bellman_ford(num_vertices, edges, 0); opt.has_value()) {
        auto dist = std::move(*opt);
        std::cout << -dist[n] << '\n';
    } else {
        std::cout << -1 << '\n';
    }

    return 0;
}
