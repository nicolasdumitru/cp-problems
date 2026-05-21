// === Problem Information ===
// Name: 787. Cheapest Flights Within K Stops
// Statement URL: https://leetcode.com/problems/cheapest-flights-within-k-stops/description/

// === Solution Information ===
// Copyright (C) 2025 Nicolas Dumitru
// SPDX-License-Identifier: GPL-3.0-or-later
// Submission URL: https://leetcode.com/problems/cheapest-flights-within-k-stops/submissions/2008896225/
// Verdict: Accepted

#include <algorithm>
#include <cstdint>
#include <limits>
#include <utility>
#include <vector>

using i64 = std::int64_t;

class Solution {
public:
    int findCheapestPrice(int n, const std::vector<std::vector<int>> &flights, int src, int dst,
                          int k) {
        const auto INF = std::numeric_limits<i64>::max();
        auto prev = std::vector<i64>(n, INF);
        auto dist = prev;
        dist[src] = prev[src] = 0;
        const auto max_path_edges = static_cast<i64>(k + 1);
        for (auto i = i64{0}; i < max_path_edges; i += 1) {
            std::swap(dist, prev);
            auto changed = false;
            for (const auto &f : flights) {
                const auto from = i64{f[0]};
                const auto to = i64{f[1]};
                const auto price = i64{f[2]};

                if (prev[from] == INF) {
                    continue;
                }
                const auto new_price = price + prev[from];
                if (new_price < dist[to]) {
                    dist[to] = new_price;
                    changed = true;
                }
            }
            if (!changed) {
                break;
            }
        }
        const auto d = dist[dst];
        return d == INF ? -1 : d;
    }
};