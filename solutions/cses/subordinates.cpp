// === Problem Information ===
// Name: Subordinates
// Statement URL: https://cses.fi/problemset/task/1674

// === Solution Information ===
// Copyright (C) 2025 Nicolas Dumitru
// SPDX-License-Identifier: GPL-3.0-or-later
// Submission URL: https://cses.fi/problemset/result/12524039/
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

struct Vertex {
    std::vector<usize> adj; // ids of adjacent nodes
    usize adjacents;

    bool visited;
    usize dfs_size;

    Vertex() : adj(32, 0), adjacents(0), visited(false), dfs_size(0) {}

    auto add_adjacent(usize u) -> void {
        if (adjacents >= adj.size()) adj.resize(adj.size() * 2);
        adj[adjacents] = u;
        adjacents += 1;
    }
};

struct Graph {
    std::vector<Vertex> v;

    Graph(usize n) : v(n + 1, Vertex()) {}

    auto add_edge(usize u, usize w) -> void {
        v[u].add_adjacent(w);
        v[w].add_adjacent(u);
    }

    auto dfs_size(usize u) -> usize {
        if (!v[u].visited) impl_dfs_size(u);
        return v[u].dfs_size;
    }

    auto impl_dfs_size(usize u) -> void {
        v[u].visited = true;
        // This relies on v[u].dfs_size being initialized to 0.
        usize i;
        for (i = 0; i < v[u].adjacents; i += 1) {
            usize w = v[u].adj[i];
            if (!v[w].visited) {
                impl_dfs_size(w);
                v[u].dfs_size += 1 + v[w].dfs_size;
            }
        }
    }
};

auto main() -> int {
    const auto n = read<usize>();
    Graph g(n);

    for (usize u = 2; u <= n; u += 1) {
        const auto w = read<usize>();
        g.add_edge(u, w);
    }

    for (usize u = 1; u <= n; u += 1) {
        cout << g.dfs_size(u) << " ";
    }
    cout.put('\n');

    return 0;
}
