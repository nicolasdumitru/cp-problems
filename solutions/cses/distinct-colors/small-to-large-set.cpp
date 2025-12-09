// === Problem Information ===
// Name: Distinct Colors
// Statement URL: https://cses.fi/problemset/task/1139

// === Solution Information ===
// Copyright (C) 2025 Nicolas Dumitru
// SPDX-License-Identifier: GPL-3.0-or-later
// Submission URL: https://cses.fi/problemset/result/15542913/
// Verdict: ACCEPTED

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <istream>
#include <set>
#include <vector>

using usize = std::size_t;
using u32 = std::uint32_t;

template <typename T>
inline auto read(std::istream &input = std::cin) -> T {
    T value;
    input >> value;
    return value;
}

template <typename T>
inline auto read_vector(usize n, std::istream &input = std::cin) -> std::vector<T> {
    std::vector<T> v(n);
    for (auto &&x : v) {
        x = read<T>(input);
    }
    return v;
}

struct Edge {
    usize u;
    usize v;
    friend auto operator>>(std::istream &input, Edge &edge) -> std::istream & {
        input >> edge.u >> edge.v;
        edge.u -= 1;
        edge.v -= 1;
        return input;
    }
};

class Tree {
    static const usize NIL = SIZE_MAX;

    const std::vector<std::vector<usize>> adj;
    const std::vector<u32> colors;

public:
    Tree(const std::vector<u32> &vertex_colors, const std::vector<Edge> &edges)
        : adj(build_adj(edges)), colors(vertex_colors) {}

    auto count_subtree_colors() -> std::vector<usize> {
        // results[v] = number of distinct colors in v's subtree
        auto results = std::vector<usize>(colors.size(), 0);
        dfs(0, NIL, results); // Root is always 0 (equivalently, 1 in the problem statement).
        return results;       // Return by value. RVO prevents unnecessary copies here.
    }

private:
    auto dfs(const usize v, const usize p, std::vector<usize> &results) -> std::set<u32> {
        auto color_set = std::set<u32>({colors[v]});
        for (const auto u : adj[v]) {
            if (u == p) {
                continue;
            }
            auto u_color_set = dfs(u, v, results);
            merge_small_to_large(color_set, u_color_set);
        }
        results[v] = color_set.size();
        return color_set;
    }

    auto merge_small_to_large(std::set<u32> &large, std::set<u32> &small) -> void {
        if (small.size() > large.size()) {
            std::swap(small, large);
        }
        large.insert(small.begin(), small.end());
    }

    static auto build_adj(const std::vector<Edge> &edges) -> std::vector<std::vector<usize>> {
        std::vector<std::vector<usize>> adj(edges.size() + 1);

        auto add_edge = [&adj](const Edge &edge) -> void {
            adj[edge.u].push_back(edge.v);
            adj[edge.v].push_back(edge.u);
        };

        for (const auto &edge : edges) {
            add_edge(edge);
        }
        return adj;
    }
};

auto main() -> int {
    std::ios::sync_with_stdio(false); // Disable synchronization between C++ and
                                      // C I/O for faster input/output
    // std::cin.tie(nullptr); // Untie cin from cout to prevent automatic
    //                        // flushing of cout before each cin

    const auto n = read<usize>();
    const auto colors = read_vector<u32>(n);
    const auto edges = read_vector<Edge>(n - 1);

    auto tree = Tree(colors, edges);
    const auto subtree_counts = tree.count_subtree_colors();

    for (const auto count : subtree_counts) {
        std::cout << count << ' ';
    }

    return 0;
}
