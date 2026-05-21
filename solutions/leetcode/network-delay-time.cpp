// === Problem Information ===
// Name: 743. Network Delay Time
// Statement URL: https://leetcode.com/problems/network-delay-time/description/

// === Solution Information ===
// Copyright (C) 2025 Nicolas Dumitru
// SPDX-License-Identifier: GPL-3.0-or-later
// Submission URL: https://leetcode.com/problems/network-delay-time/submissions/2008965447/
// Verdict: Accepted

#include <algorithm>
#include <cstdint>
#include <functional>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

using i64 = std::int64_t;

struct Edge {
    i64 to;
    i64 weight;
};

template <typename T>
using AdjLists = std::vector<std::vector<T>>;

const auto INF = std::numeric_limits<i64>::max();

auto dijkstra(const AdjLists<Edge> &adj, const i64 source) -> std::vector<i64> {
    auto dist = std::vector<i64>(adj.size(), INF);
    dist[source] = 0;

    using P = std::pair<i64, i64>;
    auto pq = std::priority_queue<P, std::vector<P>, std::greater<P>>();
    pq.push({dist[source], source});

    while (!pq.empty()) {
        const auto [d, v] = pq.top();
        pq.pop();

        if (d > dist[v]) {
            continue;
        }

        for (const auto &e : adj[v]) {
            const auto new_dist = e.weight + dist[v];
            if (new_dist < dist[e.to]) {
                dist[e.to] = new_dist;
                pq.push({new_dist, e.to});
            }
        }
    }
    return dist;
}

class Solution {
public:
    int networkDelayTime(std::vector<std::vector<int>> &times, int n, int k) {
        auto adj = AdjLists<Edge>(n);
        for (const auto &t : times) {
            adj[t[0] - 1].push_back({.to = t[1] - 1, .weight = t[2]});
        }
        
        const auto dist = dijkstra(adj, k - 1);
        const auto d = *std::max_element(dist.begin(), dist.end());
        return d == INF ? -1 : d;
    }
};