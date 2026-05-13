// === Problem Information ===
// Name: Planets and Kingdoms
// Statement URL: https://cses.fi/problemset/task/1683/

// === Solution Information ===
// Copyright (C) 2025 Nicolas Dumitru
// SPDX-License-Identifier: GPL-3.0-or-later
// Submission URL: https://cses.fi/problemset/result/17158513/
// Verdict: ACCEPTED

// https://cp-algorithms.com/graph/strongly-connected-components.html

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <istream>
#include <iterator>
#include <map>
#include <ostream>
#include <set>
#include <stack>
#include <tuple>
#include <vector>

using i64 = std::int64_t;

template <typename T>
inline auto read(std::istream &input = std::cin) -> T {
    T value;
    input >> value;
    return value;
}

template <typename T>
using AdjList = std::vector<std::vector<T>>;

auto read_graph(const i64 num_vertices, const i64 num_edges) -> AdjList<i64> {
    auto adj = AdjList<i64>(num_vertices);
    for (auto i = i64{0}; i < num_edges; i += 1) {
        const auto u = read<i64>() - 1;
        const auto v = read<i64>() - 1;
        adj[u].push_back(v);
    }
    return adj;
}

auto strongly_connected_components(const AdjList<i64> &adj) -> std::tuple<i64, std::vector<i64>> {
    const auto NIL = -1;
    auto t = i64{0};
    auto t_in = std::vector<i64>(adj.size(), NIL);
    auto t_low = std::vector<i64>(adj.size(), NIL);
    auto labels = std::vector<i64>(adj.size(), NIL);
    auto s = std::stack<i64>();
    auto num_labels = i64{0};
    const auto dfs = [&](const auto &self, const i64 v) -> void {
        t += 1;
        t_in[v] = t;
        t_low[v] = t;
        s.push(v);
        for (const auto &u : adj[v]) {
            if (t_in[u] == NIL) { // u is unvisited
                self(self, u);
            }
            if (labels[u] == NIL) {
                t_low[v] = std::min(t_low[v], t_low[u]);
            }
        }

        if (t_in[v] == t_low[v]) { // found an SCC root
            num_labels += 1;
            labels[v] = num_labels;
            while (s.top() != v) {
                labels[s.top()] = num_labels;
                s.pop();
            }
            s.pop();
        }
    };

    for (auto v = i64{0}; v < std::ssize(adj); v += 1) {
        if (t_in[v] == NIL) {
            dfs(dfs, v);
        }
    }

    return {num_labels, labels};
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

    const auto [num_labels, labels] = strongly_connected_components(adj);

    std::cout << num_labels << '\n';
    for (auto &l : labels) {
        std::cout << l << ' ';
    }
    std::cout.put('\n');

    return 0;
}
