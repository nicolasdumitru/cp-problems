// === Problem Information ===
// Name: Investigation
// Statement URL: https://cses.fi/problemset/task/1202/

// === Solution Information ===
// Copyright (C) 2025 Nicolas Dumitru
// SPDX-License-Identifier: GPL-3.0-or-later
// Submission URL: https://cses.fi/problemset/result/16277436/
// Verdict: ACCEPTED

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <istream>
#include <queue>
#include <vector>

using i64 = std::int64_t;

template <typename T>
inline auto read(std::istream &input = std::cin) -> T {
    T value;
    input >> value;
    return value;
}

constexpr i64 INF = 1e18;
constexpr i64 MOD = 1e9 + 7;

struct Edge {
    i64 to;
    i64 weight;

    explicit Edge(const i64 to, const i64 weight) : to(to), weight(weight) {}
};

template <typename T>
using AdjLists = std::vector<std::vector<T>>;

template <typename T>
using min_priority_queue = std::priority_queue<T, std::vector<T>, std::greater<T>>;

auto dijkstra(const AdjLists<Edge> &adj, i64 source)
    -> std::tuple<std::vector<i64>, std::vector<i64>, std::vector<i64>, std::vector<i64>> {
    auto sp_distances = std::vector<i64>(adj.size(), INF);
    auto sp_count = std::vector<i64>(adj.size(), 0);
    auto sp_min_edges = std::vector<i64>(adj.size(), INF);
    auto sp_max_edges = std::vector<i64>(adj.size(), 0);

    sp_distances[source] = 0;
    sp_count[source] = 1;
    sp_min_edges[source] = 0;
    sp_max_edges[source] = 0;

    // Priority queue of (distance, vertex) pairs, ordered by distance
    auto q = min_priority_queue<std::pair<i64, i64>>();
    q.push(std::pair{sp_distances[source], source});

    while (!q.empty()) {
        const auto [distance, u] = q.top();
        q.pop();
        if (distance > sp_distances[u]) {
            continue;
        }
        for (const auto &e : adj[u]) {
            const auto candidate_distance = sp_distances[u] + e.weight;
            if (candidate_distance < sp_distances[e.to]) {
                sp_distances[e.to] = candidate_distance;
                q.push(std::pair{sp_distances[e.to], e.to});

                sp_count[e.to] = sp_count[u];
                sp_min_edges[e.to] = sp_min_edges[u] + 1;
                sp_max_edges[e.to] = sp_max_edges[u] + 1;
            } else if (candidate_distance == sp_distances[e.to]) {
                sp_count[e.to] = (sp_count[e.to] + sp_count[u]) % MOD;
                sp_min_edges[e.to] = std::min(sp_min_edges[e.to], sp_min_edges[u] + 1);
                sp_max_edges[e.to] = std::max(sp_max_edges[e.to], sp_max_edges[u] + 1);
            }
        }
    }

    return {sp_distances, sp_count, sp_min_edges, sp_max_edges};
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
    for (i64 i = 0; i < num_edges; i += 1) {
        const auto from = read<i64>();
        const auto to = read<i64>();
        const auto weight = read<i64>();
        adj[from].push_back(Edge(to, weight));
    }

    const auto &[distances, sp_count, sp_min_edges, sp_max_edges] = dijkstra(adj, 1);

    std::cout << distances[num_vertices] << ' ' << sp_count[num_vertices] << ' '
              << sp_min_edges[num_vertices] << ' ' << sp_max_edges[num_vertices] << '\n';

    return 0;
}
