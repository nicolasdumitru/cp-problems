// === Problem Information ===
// Name: 1328E. Tree Queries
// Statement URL: https://codeforces.com/contest/1328/problem/E

// === Solution Information ===
// Copyright (C) 2025 Nicolas Dumitru
// SPDX-License-Identifier: GPL-3.0-or-later
// Submission URL: https://codeforces.com/contest/1328/submission/328557417
// Verdict: Accepted

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
    usize time;
    usize tree_root;
    std::vector<usize> time_in;
    std::vector<usize> time_out;
    std::vector<usize> parent_of;

public:
    Tree(usize vertices)
        : adj(vertices), time(vertices), tree_root(NIL), time_in(vertices),
          time_out(vertices), parent_of(vertices) {}

    inline auto add_edge(const usize u, const usize v) -> void {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    inline auto euler_tour(const usize root) -> void {
        time = 0;
        tree_root = root;
        parent_of[root] = root;
        dfs(root);
    }

    inline auto is_ancestor(const usize a, const usize v) const -> bool {
        return time_in[a] <= time_in[v] && time_out[v] <= time_out[a];
    }

    inline auto parent(const usize v) const -> usize {
        return parent_of[v];
    }

    inline auto root() const -> usize {
        return tree_root;
    }

private:
    auto dfs(const usize v) -> void {
        time += 1;
        time_in[v] = time;
        for (const auto u : adj[v]) {
            if (u == parent_of[v]) continue;
            parent_of[u] = v;
            dfs(u);
        }
        time += 1;
        time_out[v] = time;
    }
};

auto read_tree(const usize n) -> Tree {
    Tree t(n);
    for ([[maybe_unused]] const auto _ : std::views::iota(usize{1}, n)) {
        const auto u = read<usize>() - 1;
        const auto v = read<usize>() - 1;
        t.add_edge(u, v);
    }
    return t;
}

auto process_queries(Tree &t, const usize root, const usize num_queries)
    -> void {
    t.euler_tour(root);
    for ([[maybe_unused]] const auto _ :
         std::views::iota(usize{0}, num_queries)) {
        const auto k = read<usize>();
        auto lowest = read<usize>() - 1;
        lowest = t.parent(lowest);
        bool path_exists = true;
        for ([[maybe_unused]] const auto _ : std::views::iota(usize{1}, k)) {
            auto v = read<usize>() - 1;
            v = t.parent(v);
            if (t.is_ancestor(lowest, v)) {
                lowest = v;
            } else if (!t.is_ancestor(v, lowest)) {
                path_exists = false;
            }
        }
        std::cout << (path_exists ? "YES" : "NO") << '\n';
    }
}

auto main() -> int {
    std::ios::sync_with_stdio(false); // Disable synchronization between C++ and
                                      // C I/O for faster input/output

    const auto n = read<usize>();
    const auto m = read<usize>();
    auto t = read_tree(n);

    process_queries(t, 0, m);

    return 0;
}
