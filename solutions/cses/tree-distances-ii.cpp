// === Problem Information ===
// Name: Tree Distances II
// Statement URL: https://cses.fi/problemset/task/1133

// === Solution Information ===
// Copyright (C) 2025 Nicolas Dumitru
// SPDX-License-Identifier: GPL-3.0-or-later
// Submission URL: https://cses.fi/problemset/result/13308319/
// Verdict: ACCEPTED

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <ranges>
#include <vector>

using usize = std::size_t;

template <typename T>
inline auto read(std::istream &input = std::cin) -> T {
    T value;
    input >> value;
    return value;
}

class Tree {
    const usize NIL = SIZE_MAX;

    std::vector<std::vector<usize>> adj;
    std::vector<usize> parent;
    std::vector<usize> sum;
    std::vector<usize> size;
    std::vector<usize> visits;

public:
    Tree(const usize n)
        : adj(n, std::vector<usize>(0)), parent(n), sum(n), size(n), visits(0) {
        // Note: `visits` and each of `adj`'s elements must be initialized with
        // size 0 so that `push_back()` inserts elements predictably.
        visits.reserve(n);
    }

    auto get_distance_sums() -> std::vector<usize> {
        const usize root = 0;
        dfs(root, NIL);

        for (const auto &u : std::views::drop(visits, 1)) {
            sum[u] = sum[parent[u]] + size[root] - 2 * size[u];
        }
        visits.clear();
        return sum;
    }

    auto add_edge(const usize u, const usize v) -> void {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // For each DFS subtree, this method computes its size (number of
    // vertices) and the sum of the distances from the root to all other
    // vertices in the subtree.
    auto dfs(const usize v, const usize p) -> void {
        parent[v] = p;
        visits.push_back(v);
        sum[v] = 0;
        size[v] = 1;
        for (const auto &u : adj[v]) {
            if (u == p) continue;
            dfs(u, v);
            size[v] += size[u];
            sum[v] += sum[u] + size[u];
        }
    }
};

auto main() -> int {
    std::ios::sync_with_stdio(false);

    const auto n = read<usize>();
    Tree t(n);

    // There are n - 1 edges in a tree with n vertices
    for (usize i = 1; i < n; i += 1) {
        // 0-index vertices
        const auto u = read<usize>() - 1;
        const auto v = read<usize>() - 1;
        t.add_edge(u, v);
    }

    std::vector<usize> max = t.get_distance_sums();
    for (auto &&x : max) {
        std::cout << x << " ";
    }
    std::cout.put('\n');

    return 0;
}
