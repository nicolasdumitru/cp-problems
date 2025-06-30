// === Problem Information ===
// Name: Subtree Queries
// Statement URL: https://cses.fi/problemset/task/1137/

// === Solution Information ===
// Copyright (C) 2025 Nicolas Dumitru
// SPDX-License-Identifier: GPL-3.0-or-later
// Submission URL: https://cses.fi/problemset/result/13519142/
// Verdict: ACCEPTED

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <ranges>
#include <vector>

using usize = std::size_t;
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

class Tree {
    const usize NIL;
    std::vector<std::vector<usize>> adj;
    std::vector<usize> subtree_size;
    std::vector<usize> flattened;
    usize time;

public:
    Tree(const usize vertices)
        : NIL(SIZE_MAX), adj(vertices), subtree_size(vertices),
          flattened(vertices) {}

    auto add_edge(const usize u, const usize v) -> void {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    auto flatten(const usize root)
        -> std::pair<std::vector<usize>, std::vector<usize>> {
        time = 0;
        dfs(root, NIL);
        return std::pair(flattened, subtree_size);
    }

private:
    auto dfs(const usize v, const usize p) -> void {
        flattened[v] = time;
        time += 1;
        subtree_size[v] = 1;
        for (const auto u : adj[v]) {
            if (u == p) continue;
            dfs(u, v);
            subtree_size[v] += subtree_size[u];
        }
    }
};

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
        for (const usize i : std::views::iota(usize{0}, v.size())) {
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
    auto range_sum(const usize begin, const usize end) -> i64 {
        return prefix_sum(end - 1) - (begin > 0 ? prefix_sum(begin - 1) : 0);
    }
};

auto main() -> int {
    std::ios::sync_with_stdio(false); // Disable synchronization between C++ and
                                      // C I/O for faster input/output

    const auto n = read<usize>();
    const auto q = read<usize>();
    const auto v = read_vector<i64>(n);

    Tree t(n);
    for ([[maybe_unused]] const auto _ : std::views::iota(usize{0}, n - 1)) {
        const auto u = read<usize>() - 1;
        const auto w = read<usize>() - 1;
        t.add_edge(u, w);
    }

    const auto &[pos, range] = t.flatten(0);
    std::vector<i64> mapped_values(v.size());
    for (const usize i : std::views::iota(usize{0}, v.size())) {
        mapped_values[pos[i]] = v[i];
    }

    FenwickTree bit(mapped_values);
    for ([[maybe_unused]] const auto _ : std::views::iota(usize{0}, q)) {
        const auto qt = read<i64>();
        const auto s = read<usize>() - 1;
        if (qt == 1) {
            const auto x = read<i64>();
            bit.point_set(pos[s], x);
        } else {
            std::cout << bit.range_sum(pos[s], pos[s] + range[s]) << '\n';
        }
    }

    return 0;
}
