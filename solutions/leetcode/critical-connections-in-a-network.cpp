// === Problem Information ===
// Name: 1192. Critical Connections in a Network
// Statement URL: https://leetcode.com/problems/critical-connections-in-a-network/description/

// === Solution Information ===
// Copyright (C) 2025 Nicolas Dumitru
// SPDX-License-Identifier: GPL-3.0-or-later
// Submission URL: https://leetcode.com/problems/critical-connections-in-a-network/submissions/
// Verdict: Accepted

#include <algorithm>
#include <vector>

template <typename T>
using AdjList = std::vector<std::vector<T>>;

auto critical_edges(const AdjList<int> &adj) -> std::vector<std::vector<int>> {
    const auto NIL_TIME = int{-1};
    auto t_in = std::vector<int>(adj.size(), NIL_TIME);
    auto low_link = std::vector<int>(adj.size(), NIL_TIME);
    auto t = NIL_TIME;
    auto result = std::vector<std::vector<int>>();
    result.reserve(adj.size() - 1);
    const auto visited = [&t_in](int v) -> bool { return t_in[v] != NIL_TIME; };
    const auto dfs = [&](const auto self, const int v, const int p) -> void {
        t += 1;
        t_in[v] = t;
        low_link[v] = t;
        for (const auto u : adj[v]) {
            if (u == p) {
                continue;
            }

            if (!visited(u)) {
                self(self, u, v);

                // finding a previously visited non-DFS-parent vertex will never yield a critical
                // edge, as that vertex is in a cycle, so we only need to check for vertices that
                // were not previously visited
                if (low_link[u] > t_in[v]) {
                    result.push_back({u, v});
                    // low_link[u] > t_in[v] >= low_link[v], so there is no point in trying to
                    // minimize low_link[v] in this case

                } else {
                    low_link[v] = std::min(low_link[v], low_link[u]);
                }
            } else {
                low_link[v] = std::min(low_link[v], t_in[u]);
            }
        }
    };
    dfs(dfs, 0, -1);
    result.shrink_to_fit();
    return result;
}

class Solution {
public:
    std::vector<std::vector<int>> criticalConnections(int n,
                                                      std::vector<std::vector<int>> &connections) {
        auto adj = AdjList<int>(n);
        for (const auto &e : connections) {
            adj[e.front()].push_back(e.back());
            adj[e.back()].push_back(e.front());
        }
        return critical_edges(adj);
    }
};