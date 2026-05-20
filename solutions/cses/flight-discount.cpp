// === Problem Information ===
// Name: Flight Discount
// Statement URL: https://cses.fi/problemset/task/1195

// === Solution Information ===
// Copyright (C) 2025 Nicolas Dumitru
// SPDX-License-Identifier: GPL-3.0-or-later
// Submission URL: https://cses.fi/problemset/result/17237763/
// Verdict: ACCEPTED

#include <cstdint>
#include <functional>
#include <iostream>
#include <istream>
#include <limits>
#include <queue>
#include <utility>
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

struct Edge {
    i64 to;
    i64 weight;
};

template <typename T>
using AdjLists = std::vector<std::vector<T>>;

auto read_graph(const i64 num_vertices, const i64 num_edges) -> AdjLists<Edge> {
    auto adj = AdjLists<Edge>(num_vertices * 2);
    for (auto i = i64{0}; i < num_edges; i += 1) {
        const auto from = read<i64>() - 1;
        const auto to = read<i64>() - 1;
        const auto weight = read<i64>();
        const auto mirrored_to = to + num_vertices;
        adj[from].push_back({.to = to, .weight = weight});                         // original edge
        adj[from + num_vertices].push_back({.to = mirrored_to, .weight = weight}); // mirrored edge
        adj[from].push_back({.to = mirrored_to, .weight = weight / 2}); // half-weight edge
    }
    return adj;
}

auto dijkstra(const AdjLists<Edge> &adj, const i64 source) -> std::vector<i64> {
    const auto INF = std::numeric_limits<i64>::max();
    auto dist = std::vector<i64>(adj.size(), INF);
    dist[source] = 0;

    using P = std::pair<i64, i64>;
    auto pq = std::priority_queue<P, std::vector<P>, std::greater<P>>();
    pq.push({dist[source], source});
    while (!pq.empty()) {
        const auto [d, v] = pq.top();
        pq.pop();
        if (dist[v] < d) {
            continue;
        }
        for (const auto &e : adj[v]) {
            const auto new_dist = d + e.weight;
            if (new_dist < dist[e.to]) {
                dist[e.to] = new_dist;
                pq.push({new_dist, e.to});
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

    const auto adj = read_graph(num_vertices, num_edges);
    const auto source = 0;
    const auto target = (num_vertices - 1) + num_vertices;
    // This check is not necessary for this problem, we are always going to compute the shortest
    // path distance using Dijkstra's, but it shows how this graph trick code could be use for any
    // arbitrary (source, target) pair.
    if (source == target) {
        std::cout << "0\n";
    } else {
        auto dist = dijkstra(adj, source);
        std::cout << dist[target] << '\n';
    }

    return 0;
}
