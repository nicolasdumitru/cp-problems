// === Problem Information ===
// Name: Tree Distances I
// Statement URL: https://cses.fi/problemset/task/1132

// === Solution Information ===
// Copyright (C) 2025 Nicolas Dumitru
// SPDX-License-Identifier: GPL-3.0-or-later
// Submission URL: https://cses.fi/problemset/result/13307044/
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
    std::vector<usize> first_max;
    std::vector<usize> first_max_through;
    std::vector<usize> second_max;
    std::vector<usize> visits;

public:
    Tree(const usize vertex_count)
        : adj(vertex_count), parent(vertex_count), first_max(vertex_count),
          first_max_through(vertex_count), second_max(vertex_count) {
        visits.reserve(vertex_count);
    }

    auto get_max_lengths() -> std::vector<usize> {
        get_child_max_lengths(0, NIL);

        // Update each vertex's max length with the parent's max lengths
        for (auto &&v : std::views::drop(visits, 1)) {
            usize p = parent[v];
            maximize(v, p,
                     first_max_through[p] != v ? first_max[p] : second_max[p]);
        }
        visits.clear();
        return first_max;
    }

    auto add_edge(const usize u, const usize v) -> void {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

private:
    auto get_child_max_lengths(const usize v, const usize p) -> void {
        parent[v] = p;
        first_max[v] = 0;
        first_max_through[v] = NIL;
        second_max[v] = 0;
        visits.push_back(v);
        for (auto &&u : adj[v]) {
            if (u == p) continue;
            get_child_max_lengths(u, v);
            maximize(v, u, first_max[u]);
        }
    }

    auto maximize(const usize v, const usize u, usize length) -> void {
        length += 1;
        if (length > first_max[v]) {
            second_max[v] = first_max[v];
            first_max[v] = length;
            first_max_through[v] = u;
        } else if (length > second_max[v]) {
            second_max[v] = length;
        }
    }
};

auto main() -> int {
    std::ios::sync_with_stdio(false);

    const auto n = read<usize>();
    Tree t(n);

    // There are n - 1 edges in a tree with n vertices
    for (usize i = 1; i < n; i += 1) {
        // 0-index nodes
        const auto u = read<usize>() - 1;
        const auto v = read<usize>() - 1;
        t.add_edge(u, v);
    }

    std::vector<usize> max = t.get_max_lengths();
    for (auto &&x : max) {
        std::cout << x << " ";
    }
    std::cout.put('\n');

    return 0;
}
