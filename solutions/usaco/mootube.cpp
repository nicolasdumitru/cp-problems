// === Problem Information ===
// Name: MooTube
// Statement URL: https://usaco.org/index.php?page=viewproblem2&cpid=789

// === Solution Information ===
// Copyright (C) 2025 Nicolas Dumitru
// SPDX-License-Identifier: GPL-3.0-or-later
// Verdict: Accepted

#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <istream>
#include <vector>

using i64 = std::int64_t;

template <typename T>
inline auto read(std::istream &input) -> T {
    T value;
    input >> value;
    return value;
}

template <typename T>
inline auto read_vector(i64 n, std::istream &input) -> std::vector<T> {
    std::vector<T> v(n);
    for (auto &&x : v) {
        x = read<T>(input);
    }
    return v;
}

class DisjointSetForest {
public:
    explicit DisjointSetForest(const i64 num_nodes) : parent(num_nodes), size(num_nodes) {
        for (i64 node = 0; node < num_nodes; node += 1) {
            make_set(node);
        }
    }

    inline auto find_set(i64 x) -> i64 {
        if (parent[x] != x) {
            parent[x] = find_set(parent[x]); // Path compression
        }
        return parent[x];
    }

    inline auto unite_sets(i64 x, i64 y) -> void {
        x = find_set(x);
        y = find_set(y);
        if (x == y) return;

        // Union by size
        if (size[x] > size[y]) {
            absorb(x, y);
        } else {
            absorb(y, x);
        }
    }

    inline auto connected(i64 x, i64 y) -> bool {
        return find_set(x) == find_set(y);
    }

    inline auto get_set_size(const i64 x) -> i64 {
        return size[find_set(x)];
    }

private:
    std::vector<i64> parent;
    std::vector<i64> size;

    /**
     * `make_set` is unsafe in this implementation (doesn't check whether the
     * set already exists)
     */
    inline auto make_set(const i64 node) -> void {
        parent[node] = node;
        size[node] = 1;
    }

    /**
     * Contract: Expects both arguments to be distinct tree roots and that
     * `size[larger] >= size[smaller]`. Absorbs the smaller tree in the larger,
     * then updates the size of the larger tree and the maximum size
     * accordingly.
     */
    inline auto absorb(const i64 larger, const i64 smaller) -> void {
        parent[smaller] = larger;
        size[larger] += size[smaller];
    }
};

struct Edge {
    i64 u;
    i64 v;
    i64 weight;

    friend auto operator>>(std::istream &in, Edge &e) -> std::istream & {
        in >> e.u >> e.v >> e.weight;
        return in;
    }
};

struct Query {
    i64 index;
    i64 min_weight;
    i64 vertex;
};

auto read_queries(const i64 num_queries, std::istream &input) -> std::vector<Query> {
    auto queries = std::vector<Query>(num_queries);
    for (i64 i = 0; i < static_cast<i64>(queries.size()); i += 1) {
        queries[i].index = i;
        queries[i].min_weight = read<i64>(input);
        queries[i].vertex = read<i64>(input);
    }
    return queries;
}

auto process_queries(const i64 num_vertices, std::vector<Edge> &edges, std::vector<Query> &queries)
    -> std::vector<i64> {
    auto result = std::vector<i64>(queries.size());

    std::sort(edges.begin(), edges.end(),
              [](const Edge &a, const Edge &b) -> bool { return a.weight > b.weight; });

    std::sort(queries.begin(), queries.end(),
              [](const Query &a, const Query &b) -> bool { return a.min_weight > b.min_weight; });

    auto dsu = DisjointSetForest(num_vertices + 1); // 1-based indexing

    auto edge_idx = i64{0};
    for (const auto &query : queries) {
        while (edge_idx < static_cast<i64>(edges.size()) &&
               edges[edge_idx].weight >= query.min_weight) {
            dsu.unite_sets(edges[edge_idx].u, edges[edge_idx].v);
            edge_idx += 1;
        }
        result[query.index] = dsu.get_set_size(query.vertex) - 1;
    }

    return result;
}

auto main() -> int {
    // Fast I/O
    // Disable synchronization between C++ and C I/O for faster input/output
    std::ios::sync_with_stdio(false);

    auto fin = std::ifstream("mootube.in");

    const auto n = read<i64>(fin);
    const auto q = read<i64>(fin);

    auto edges = read_vector<Edge>(n - 1, fin);
    auto queries = read_queries(q, fin);

    const auto results = process_queries(n, edges, queries);

    auto fout = std::ofstream("mootube.out");
    for (const auto result : results) {
        fout << result << '\n';
    }

    return 0;
}
