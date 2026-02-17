// === Problem Information ===
// Name: Round Trip II
// Statement URL: https://cses.fi/problemset/task/1678/

// === Solution Information ===
// Copyright (C) 2025 Nicolas Dumitru
// SPDX-License-Identifier: GPL-3.0-or-later
// Submission URL: https://cses.fi/problemset/result/16299080/
// Verdict: ACCEPTED

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <istream>
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
    const auto num_vertices = static_cast<i64>(adj.size() - 1); // 1-indexed vertices
    auto visited = std::vector<bool>(adj.size(), false);
    auto visiting = std::vector<bool>(adj.size(), false);
    auto num_unvisited_vertices = num_vertices;
    auto cycle = std::vector<i64>();

    const auto dfs = [&](auto &&self, i64 u) -> void {
        visited[u] = true;
        visiting[u] = true;
        num_unvisited_vertices -= 1;
        for (const auto v : adj[u]) {
            if (visiting[v] && v != u) { // self-loops don't as "round trips"
                cycle.push_back(v);
                break;
            }
            if (visited[v]) {
                continue;
            }
            self(self, v);
            if (!cycle.empty()) {
                break;
            }
        }
        if (!cycle.empty() && (cycle.size() == 1 || cycle.front() != cycle.back())) {
            cycle.push_back(u);
        }
        visiting[u] = false;
    };

    for (auto u = i64{1}; u <= num_vertices && num_unvisited_vertices > 0 && cycle.empty();
         u += 1) {
        if (!visited[u]) {
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
