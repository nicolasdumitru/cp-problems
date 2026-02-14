// === Problem Information ===
// Name: Shortest Routes I
// Statement URL: https://cses.fi/problemset/task/1671/

// === Solution Information ===
// Copyright (C) 2025 Nicolas Dumitru
// SPDX-License-Identifier: GPL-3.0-or-later
// Submission URL: https://cses.fi/problemset/result/16270659/
// Verdict: ACCEPTED

#include <cstdint>
#include <iostream>
#include <istream>
#include <queue>
#include <ranges>
#include <utility>
#include <vector>

using namespace std;

using i32 = std::int32_t;
using i64 = std::int64_t;

template <typename T>
inline auto read(std::istream &input = std::cin) -> T {
    T value;
    input >> value;
    return value;
}

constexpr i64 INF = 1e18;

struct Edge {
    i64 to;
    i64 weight;

    explicit Edge(const i64 to, const i64 weight) : to(to), weight(weight) {}
};

template <typename T>
using AdjLists = vector<vector<T>>;

template <typename T>
using min_priority_queue = priority_queue<T, vector<T>, greater<T>>;

auto dijkstra(const AdjLists<Edge> &adj, i64 source) -> vector<i64> {
    auto q = min_priority_queue<pair<i64, i64>>();
    auto dist = std::vector<i64>(adj.size(), INF);
    dist[source] = 0;
    q.push(pair{0, source});
    while (!q.empty()) {
        const auto [d, u] = q.top();
        q.pop();
        if (d > dist[u]) {
            continue;
        }
        for (const auto &e : adj[u]) {
            if (dist[u] + e.weight < dist[e.to]) {
                dist[e.to] = dist[u] + e.weight;
                q.push(pair{dist[e.to], e.to});
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
    auto adj = AdjLists<Edge>(num_vertices + 1);
    for (i32 i = 0; i < num_edges; i += 1) {
        const auto from = read<i64>();
        const auto to = read<i64>();
        const auto weight = read<i64>();
        adj[from].push_back(Edge(to, weight));
    }

    const auto results = dijkstra(adj, 1);

    for (const auto dist : results | views::drop(1)) {
        std::cout << dist << ' ';
    }

    return 0;
}
