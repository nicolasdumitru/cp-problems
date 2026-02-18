// === Problem Information ===
// Name: Round Trip II
// Statement URL: https://cses.fi/problemset/task/1678/

// === Solution Information ===
// Copyright (C) 2025 Nicolas Dumitru
// SPDX-License-Identifier: GPL-3.0-or-later
// Submission URL: https://cses.fi/problemset/result/16303093/
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

template <typename T>
using AdjLists = std::vector<std::vector<T>>;

auto read_directed_graph(const i64 num_vertices, const i64 num_edges) -> AdjLists<i64> {
    auto adj = AdjLists<i64>(num_vertices + 1); // 1-indexed
    auto in_degrees = std::vector<i64>(adj.size(), 0);
    for (auto i = i64{0}; i < num_edges; i += 1) {
        const auto from = read<i64>();
        const auto to = read<i64>();
        adj[from].push_back(to);
        in_degrees[to] += 1;
    }
    return adj;
}

/**
 * Returns a non-empty vector of vertices if a cycle exists; otherwise, returns an empty vector.
 */
auto find_cycle(const AdjLists<i64> &adj) -> std::vector<i64> {
    enum class VertexState { Unvisited, Visiting, Visited };
    using enum VertexState;

    auto vertex_states = std::vector<VertexState>(adj.size(), Unvisited);
    auto cycle = std::vector<i64>();

    const auto dfs = [&](auto &&self, i64 u) -> void {
        vertex_states[u] = Visiting;
        for (const auto v : adj[u]) {
            // Skip vertices based on 2 criteria:
            // 1. If a vertex is already visited and a cycle has not yet been found, that vertex
            //    cannot be part of a cycle.
            // 2. For this particular problem, self-loops don't count as "round trips".
            if (vertex_states[v] == Visited || v == u) {
                continue;
            }

            if (vertex_states[v] == Visiting) {
                cycle.push_back(v);
                cycle.push_back(u);
                vertex_states[v] = Visited; // pedantic
                vertex_states[u] = Visited; // pedantic
                return;
            }

            self(self, v);
            if (!cycle.empty()) {
                if (cycle.front() != cycle.back()) {
                    cycle.push_back(u);
                }
                break;
            }
        }
        vertex_states[u] = Visited;
    };

    for (auto u = i64{0}; u < std::ssize(adj) && cycle.empty(); u += 1) {
        if (vertex_states[u] == Unvisited) {
            dfs(dfs, u);
        }
    }

    if (!cycle.empty()) {
        std::reverse(cycle.begin(), cycle.end());
    }
    return cycle;
}

auto main() -> int {
    // Fast I/O
    // Disable synchronization between C++ and C I/O for faster input/output
    std::ios::sync_with_stdio(false);
    // Untie cin from cout to prevent automatic flushing of cout before each cin
    std::cin.tie(nullptr);

    const auto n = read<i64>();
    const auto m = read<i64>();

    const auto adj = read_directed_graph(n, m);

    const auto result = find_cycle(adj);
    if (result.empty()) {
        std::cout << "IMPOSSIBLE\n";
    } else {
        std::cout << result.size() << '\n';
        for (const auto u : result) {
            std::cout << u << ' ';
        }
        std::cout.put('\n');
    }

    return 0;
}
