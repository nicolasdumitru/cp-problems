// === Problem Information ===
// Name: Fixed-Length Paths I
// Statement URL: https://cses.fi/problemset/task/2080/

// === Solution Information ===
// Copyright (C) 2025 Nicolas Dumitru
// SPDX-License-Identifier: GPL-3.0-or-later
// Submission URL: https://cses.fi/problemset/result/15519688/
// Verdict: ACCEPTED

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <deque>
#include <iostream>
#include <istream>
#include <ranges>
#include <utility>
#include <vector>

using usize = std::size_t;

template <typename T>
inline auto read(std::istream &input = std::cin) -> T {
    T value;
    input >> value;
    return value;
}

template <typename T>
inline auto read_vector(usize n, std::istream &input = std::cin)
    -> std::vector<T> {
    std::vector<T> v(n);
    for (auto &&x : v) {
        x = read<T>(input);
    }
    return v;
}

struct Edge {
    usize u;
    usize v;
    // Edge(usize u, usize v) : u(u), v(v) {}
    friend auto operator>>(std::istream &input, Edge &edge) -> std::istream & {
        input >> edge.u >> edge.v;
        edge.u -= 1;
        edge.v -= 1;
        return input;
    }
};

class Tree {
    std::vector<std::vector<usize>> adj;
    usize count = 0;
    usize k;
    static const usize NIL = SIZE_MAX;

public:
    Tree(std::vector<Edge> &edges) : adj(edges.size() + 1) {
        for (auto e : edges) {
            add_edge(e);
        }
    }

    auto count_paths_of_length(const usize len) -> usize {
        k = len;
        count = 0;
        dfs(0, NIL);
        return count;
    }

private:
    auto dfs(usize v, usize p = NIL) -> std::deque<usize> {
        std::deque<usize> deque;
        for (auto u : adj[v]) {
            if (u == p) {
                continue;
            }
            auto du = dfs(u, v);
            if (du.size() > deque.size()) {
                std::swap(deque, du);
            }
            auto indexes = std::ranges::views::iota(usize{0}, du.size());
            for (const usize i : indexes) {
                const auto j = k - i - 2;
                if (j < std::min(deque.size(), k)) {
                    count += du[i] * deque[j];
                }
            }
            // Update the depth deque here, after counting the paths with LCA v.
            // This ensures that no paths are counted twice.
            for (const usize i : indexes) {
                deque[i] += du[i];
            }
        }
        deque.push_front(1); // The current vertex is the only vertex with depth 0.
        if (deque.size() > k) {
            count += deque[k];
            deque.pop_back();
        }
        return deque;
    }

    auto add_edge(Edge e) -> void {
        adj[e.u].push_back(e.v);
        adj[e.v].push_back(e.u);
    }
};

auto main() -> int {
    std::ios::sync_with_stdio(false); // Disable synchronization between C++ and
                                      // C I/O for faster input/output

    const auto n = read<usize>();
    const auto k = read<usize>();
    auto edges = read_vector<Edge>(n - 1);
    Tree t(edges);
    std::cout << t.count_paths_of_length(k) << "\n";

    return 0;
}
