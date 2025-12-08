// === Problem Information ===
// Name: Fixed-Length Paths I
// Statement URL: https://cses.fi/problemset/task/2080/

// === Solution Information ===
// Copyright (C) 2025 Nicolas Dumitru
// SPDX-License-Identifier: GPL-3.0-or-later
// Submission URL: https://cses.fi/problemset/result/15531250/
// Verdict: ACCEPTED

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <deque>
#include <iostream>
#include <istream>
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
        std::deque<usize> result;
        for (auto u : adj[v]) {
            if (u == p) {
                continue;
            }
            auto child_result = dfs(u, v);
            count += merge_small_to_large(result, child_result);
        }
        result.push_front(1); // The current vertex is the only vertex with depth 0.
        if (result.size() > k) {
            count += result[k];
            result.pop_back();
        }
        return result;
    }

    auto merge_small_to_large(std::deque<usize> &large, std::deque<usize> &small) const -> usize {
        usize merge_count = 0;
        if (small.size() > large.size()) {
            std::swap(large, small);
        }
        auto range_begin = k - 1 > large.size() ? k - 1 - large.size() : 0;
        auto range_end = std::min(small.size(), k - 1);
        for (usize i = range_begin; i < range_end; i += 1) {
            const auto j = k - i - 2;
            merge_count += small[i] * large[j];
        }
        // Update the depth large here, after counting the paths with LCA v.
        // This ensures that no paths are counted twice.
        for (usize i = 0; i < small.size(); i += 1) {
            large[i] += small[i];
        }
        return merge_count;
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