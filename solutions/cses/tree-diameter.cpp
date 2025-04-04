// === Problem Information ===
// Name: Tree Diameter
// Statement URL: https://cses.fi/problemset/task/1131

// === Solution Information ===
// Copyright (C) 2025 Nicolas Dumitru
// SPDX-License-Identifier: GPL-3.0-or-later
// Submission URL: https://cses.fi/problemset/result/12539929/
// Verdict: ACCEPTED

#include <algorithm>
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

// using std::cerr;
using std::cout;

template <typename T>
inline auto read() -> T {
    T value = (std::cin >> value, value);
    return value;
}

enum { NIL = 0 }; // node numbering starts from 1
struct Vertex {
    usize adj_begin;
    usize adj_end;

    bool visited;

    Vertex() : adj_begin(NIL), adj_end(NIL), visited(false) {}
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
    bool computed_tree_diameter;
    usize tree_diameter;

    bool dfs_visited;

public:
    Tree(usize n)
        : v(n + 1), adj(2 * n - 1, Node()), list_next_free(1),
          computed_tree_diameter(false), tree_diameter(0), dfs_visited(false) {}

    auto add_edge(usize id_u, usize id_w) -> void {
        add_adjacent(id_u, id_w);
        add_adjacent(id_w, id_u);
    }

    auto diameter() -> usize {
        if (!computed_tree_diameter) {
            tree_height(1);
            computed_tree_diameter = true;
        }
        return tree_diameter;
    }

    auto tree_height(usize id_root) -> usize {
        auto ans = dfs_subtree_height(id_root);
        dfs_visited = !dfs_visited;
        return ans;
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

    // By adding a single line of code, this function also computes the tree
    // diameter as a side effect.
    auto dfs_subtree_height(usize id_u) -> usize {
        auto &u = v[id_u];
        u.visited = !u.visited;
        usize subtree_height = 0;
        for (usize i = u.adj_begin; i != NIL; i = adj[i].next) {
            const auto id_w = adj[i].id;
            if (!(v[id_w].visited != dfs_visited)) { // != is a logical XOR here
                auto dist = 1 + dfs_subtree_height(id_w);
                tree_diameter = std::max(tree_diameter, dist + subtree_height);
                subtree_height = std::max(subtree_height, dist);
            }
        }

        return subtree_height;
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

    cout << t.diameter() << "\n";

    return 0;
}
