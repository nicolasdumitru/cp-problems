// === Problem Information ===
// Name: Tree Matching
// Statement URL: https://cses.fi/problemset/task/1130

// === Solution Information ===
// Copyright (C) 2025 Nicolas Dumitru
// SPDX-License-Identifier: GPL-3.0-or-later
// Submission URL: https://cses.fi/problemset/result/12533580/
// Verdict: ACCEPTED

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>

using usize = std::size_t;
using isize = std::ptrdiff_t;
using u8 = std::uint8_t; // std input streams treat this as char
using i8 = std::int8_t;  // std input streams treat this as char
using u16 = std::uint16_t;
using i16 = std::int16_t;
using u32 = std::uint32_t;
using i32 = std::int32_t;
using u64 = std::uint64_t;
using i64 = std::int64_t;

using std::cout;

template <typename T>
inline auto read() -> T {
    T value = (std::cin >> value, value);
    return value;
}

template <typename T>
inline auto read_vector(usize n) -> std::vector<T> {
    std::vector<T> v(n);
    for (auto &&x : v) {
        x = read<T>();
    }
    return v;
}

enum { NIL = 0 }; // node numbering starts from 1
struct Vertex {
    usize adj_begin;
    usize adj_end;

    bool visited;
    bool matched;

    Vertex() : adj_begin(NIL), adj_end(NIL), visited(false), matched(false) {}
};

struct Node {
    usize id;
    usize next;
    Node() : id(NIL), next(NIL) {}
};

class Tree {
    // G = (V, E)
    std::vector<Vertex> v; // V
    std::vector<Node> adj; // E - There is no root node convention, so we need
                           // 2 * (|V| - 1) elements to represent the tree, as
                           // each edge is represented both ways to ensure
                           // graph searching is possible
    usize list_next_free;
    usize max_matching;

public:
    Tree(usize n)
        : v(n + 1), adj(2 * n - 1, Node()), list_next_free(1), max_matching(0) {
    }

    auto add_edge(usize id_u, usize id_w) -> void {
        add_adjacent(id_u, id_w);
        add_adjacent(id_w, id_u);
    }

    auto get_max_matching() -> usize {
        if (!v[1].visited) dfs_matching(1);
        return max_matching;
    }

private:
    auto add_adjacent(usize id_u, usize id_w) -> void {
        auto &u = v[id_u];
        if (u.adj_end == NIL) { // if the adjacency list of the vertex is empty
            u.adj_begin = list_next_free;
        } else {
            adj[u.adj_end].next = list_next_free;
        }
        u.adj_end = list_next_free;
        adj[u.adj_end].id = id_w;
        list_next_free += 1;
    }

    auto dfs_matching(usize id_u) -> void {
        auto &u = v[id_u];
        u.visited = true;
        usize nodes_visited = 0;
        usize nodes_matched = 0;
        usize id_candidate = NIL;
        for (usize i = u.adj_begin; i != NIL; i = adj[i].next) {
            const auto id_w = adj[i].id;
            if (!v[id_w].visited) {
                dfs_matching(id_w);
            }
            nodes_visited += 1;
            if (v[id_w].matched) {
                nodes_matched += 1;
            } else {
                id_candidate = id_w;
            }
        }

        if (!u.matched && nodes_matched == nodes_visited - 1) {
            match(id_u, id_candidate);
        }
    }

    auto match(usize id_u, usize id_w) -> void {
        v[id_u].matched = v[id_w].matched = true;
        max_matching += 1;
    }
};

auto main() -> int {
    // std::ios::sync_with_stdio(false);
    const auto n = read<usize>();
    Tree t(n);

    for (usize i = 1; i < n; i += 1) {
        const auto u = read<usize>();
        const auto w = read<usize>();
        t.add_edge(u, w);
    }

    cout << t.get_max_matching() << "\n";

    return 0;
}
