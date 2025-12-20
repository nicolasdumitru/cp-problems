// === Problem Information ===
// Name:
// Statement URL:

// === Solution Information ===
// Copyright (C) 2025 Nicolas Dumitru
// SPDX-License-Identifier: GPL-3.0-or-later
// Submission URL:
// Verdict:

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <map>
#include <vector>

using usize = std::size_t;
using isize = std::ptrdiff_t;
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

class FenwickTree {
    std::vector<isize> bit;

    // Returns the index where node i's range begins. Every node i stores the
    // result of the query operation on the range [node_begin(i), i].
    inline auto range_begin(const usize node) const -> usize {
        return node & (node + 1);
    }
    // Returns the index of node i's parent node.
    inline auto parent(const usize node) const -> usize {
        return node | (node + 1);
    }

public:
    FenwickTree(const usize size) : bit(size, 0) {}

    auto point_add(const usize index, const isize delta) -> void {
        for (usize i = index; i < bit.size(); i = parent(i)) {
            bit[i] += delta;
        }
    }

    // [0, index]
    auto prefix_sum(const usize index) const -> isize {
        isize sum = 0;
        for (usize i = index + 1; i > 0; i = range_begin(i)) {
            i -= 1;
            sum += bit[i];
        }
        return sum;
    }
};

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
    usize time;

public:
    Tree(const std::vector<u32> &vertex_colors, const std::vector<Edge> &edges)
        : adj(build_adj(edges)), colors(vertex_colors) {}

    auto count_subtree_colors() -> std::vector<isize> {
        // results[v] will be the number of distinct colors in v's subtree
        auto results = std::vector<isize>(colors.size(), 0);
        auto latest = std::map<u32, usize>();
        // Because Fenwick trees conventionally support prefix sum operations. In order to use the
        // prefix sum operation to count distinct colors in each subtree, vertex entry time is going
        // to decrease for each subsequent vertex, i.e. vertices visited earlier by the DFS
        // will have greater vtime than those visited later. This is functionally equivalent to
        // using overall increasing time and simulating suffix sum operations.
        time = adj.size() - 1;
        auto fentree = FenwickTree(adj.size());
        const auto dfs = [&](auto &&self, const usize v, const usize p) -> void {
            const auto vtime = time; // vertex entry time
            for (const auto u : adj[v]) {
                if (u == p) {
                    continue;
                }
                time -= 1;
                self(self, u, v);
            }
            auto [it, inserted] = latest.insert({colors[v], vtime});
            if (!inserted) {
                auto &color_latest = it->second;
                // subtract 1 from the suffix sum for vertex w in the Fenwick tree
                fentree.point_add(color_latest, -1);
                color_latest = vtime;
            }
            fentree.point_add(vtime, 1);
            results[v] = fentree.prefix_sum(vtime); // Simulate suffix sums by starting with
        };
        dfs(dfs, 0, NIL);
        return results; // Return by value. RVO prevents unnecessary copies here.
    }

private:
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
