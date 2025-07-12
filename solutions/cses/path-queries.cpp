// === Problem Information ===
// Name: Path Queries
// Statement URL: https://cses.fi/problemset/task/1138

// === Solution Information ===
// Copyright (C) 2025 Nicolas Dumitru
// SPDX-License-Identifier: GPL-3.0-or-later
// Submission URL: https://cses.fi/problemset/result/13675629/
// Verdict: ACCEPTED

// Note: In this implementation, we distinguish between vertices and nodes by
// convention: vertices refer to elements of graphs proper, while nodes are
// elements of data structures that are represented as graphs (e.g., trees) for
// visualization or conceptual clarity.

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <ranges>
#include <vector>

using usize = std::size_t;
using u32 = std::uint32_t;
using i64 = std::int64_t;

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

struct VertexTimes {
    usize in;
    usize out;
};

class Tree {
    const usize NIL = SIZE_MAX;
    std::vector<std::vector<usize>> adj;
    std::vector<VertexTimes> vt;
    usize time;

public:
    Tree(usize vertices) : adj(vertices), vt(vertices) {}

    auto add_edge(const usize u, const usize v) -> void {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    inline auto euler_tour(const usize root) -> std::vector<VertexTimes> {
        time = 0;
        dfs(root, NIL);
        return vt;
    }

private:
    auto dfs(const usize v, const usize p) -> void {
        vt[v].in = time;
        time += 1;
        for (const auto u : adj[v]) {
            if (u == p) continue;
            dfs(u, v);
            time += 1;
        }
        vt[v].out = time;
    }
};

auto read_tree(const usize vertices) -> Tree {
    Tree t(vertices);
    for ([[maybe_unused]] const auto _ : std::views::iota(usize{1}, vertices)) {
        const auto u = read<usize>() - 1;
        const auto v = read<usize>() - 1;
        t.add_edge(u, v);
    }
    return t;
}

class FenwickTree {
    std::vector<i64> bit;

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
    FenwickTree(const std::vector<i64> v) : bit(v.size(), 0) {
        for (const usize i : std::views::iota(usize{0}, bit.size())) {
            bit[i] += v[i];
            if (parent(i) < bit.size()) bit[parent(i)] += bit[i];
        }
    }

    auto point_add(const usize index, const i64 delta) -> void {
        for (usize i = index; i < bit.size(); i = parent(i)) {
            bit[i] += delta;
        }
    }

    auto point_set(const usize index, const i64 val) -> void {
        // For even index values, bit[index] stores the exact value of the
        // element at index.
        // Proof:
        // bit[index] = sum [range_begin(index), index].
        // For all natural numbers k, range_begin(2k) == 2k, therefore
        // bit[2k] = sum [2k, 2k] = v[2k].
        const i64 node_val =
            (index & 1) == 0 ? bit[index] : range_sum(index, index + 1);
        point_add(index, val - node_val);
    }

    // [0, index]
    auto prefix_sum(const usize index) const -> i64 {
        i64 sum = 0;
        for (usize i = index + 1; i > 0; i = range_begin(i)) {
            i -= 1;
            sum += bit[i];
        }
        return sum;
    }

    // [begin, end)
    auto range_sum(const usize begin, const usize end) const -> i64 {
        return prefix_sum(end - 1) - (begin > 0 ? prefix_sum(begin - 1) : 0);
    }
};

auto map_vertex_values(const std::vector<i64> &vertex_values,
                       const std::vector<VertexTimes> &vt) -> std::vector<i64> {
    std::vector<i64> mapped(2 * vertex_values.size());
    for (const usize i : std::views::iota(usize{0}, vertex_values.size())) {
        mapped[vt[i].in] = vertex_values[i];
        mapped[vt[i].out] = -vertex_values[i];
    }
    return mapped;
}

auto process_queries(const u32 q, const std::vector<VertexTimes> &vt,
                     const std::vector<i64> &mapped_vertex_values) -> void {
    FenwickTree fentree(mapped_vertex_values);
    for ([[maybe_unused]] const auto _ : std::views::iota(u32{0}, q)) {
        const auto t = read<i64>();
        const auto s = read<usize>() - 1;
        if (t == 1) {
            const auto x = read<i64>();
            fentree.point_set(vt[s].in, x);
            fentree.point_set(vt[s].out, -x);
        } else { // t == 2
            std::cout << fentree.prefix_sum(vt[s].in) << '\n';
        }
    }
}
auto main() -> int {
    std::ios::sync_with_stdio(false); // Disable synchronization between C++ and
                                      // C I/O for faster input/output

    const auto n = read<usize>();
    const auto q = read<u32>();

    const auto vertex_values = read_vector<i64>(n);
    auto t = read_tree(n);

    const auto vt = t.euler_tour(0);
    const auto mapped = map_vertex_values(vertex_values, vt);
    process_queries(q, vt, mapped);

    return 0;
}
