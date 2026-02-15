// === Problem Information ===
// Name: Unionfind
// Statement URL: https://judge.yosupo.jp/problem/unionfind

// === Solution Information ===
// Copyright (C) 2025 Nicolas Dumitru
// SPDX-License-Identifier: GPL-3.0-or-later
// Submission URL: https://judge.yosupo.jp/submission/353119
// Submission URL: https://judge.yosupo.jp/submission/353115
// Verdict: AC

#include <cstdint>
#include <iostream>
#include <istream>
#include <vector>

using i32 = std::int32_t;

template <typename T>
inline auto read(std::istream &input = std::cin) -> T {
    T value;
    input >> value;
    return value;
}

class DisjointSetForest {
public:
    explicit DisjointSetForest(const i32 num_nodes) : parent(num_nodes), size(num_nodes) {
        for (i32 node = 0; node < num_nodes; node += 1) {
            make_set(node);
        }
    }

    inline auto find_set(i32 x) -> i32 {
        return recursive_find_set(x);
        // return iterative_find_set(x);
    }

    inline auto unite_sets(i32 x, i32 y) -> void {
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

    inline auto connected(i32 x, i32 y) -> bool {
        return find_set(x) == find_set(y);
    }

private:
    std::vector<i32> parent;
    std::vector<i32> size;

    /**
     * `make_set` is unsafe in this implementation (doesn't check whether the
     * set already exists)
     */
    inline auto make_set(const i32 node) -> void {
        parent[node] = node;
        size[node] = 1;
    }

    /**
     * Contract: Expects both arguments to be distinct tree roots and that
     * `size[larger] >= size[smaller]`. Absorbs the smaller tree in the larger,
     * then updates the size of the larger tree and the maximum size
     * accordingly.
     */
    inline auto absorb(const i32 larger, const i32 smaller) -> void {
        parent[smaller] = larger;
        size[larger] += size[smaller];
    }

    auto recursive_find_set(const i32 node) -> i32 {
        if (parent[node] != node) {
            parent[node] = find_set(parent[node]); // Path compression
        }
        return parent[node];
    }

    inline auto iterative_find_set(i32 x) -> i32 {
        const auto root = [&]() {
            auto root = x;
            while (root != parent[root]) {
                root = parent[root];
            }
            return root;
        }();

        // Path compression
        while (x != root) {
            const auto next = parent[x];
            parent[x] = root;
            x = next;
        }
        
        return root;
    }
};

auto main() -> int {
    // Fast I/O
    // Disable synchronization between C++ and C I/O for faster input/output
    std::ios::sync_with_stdio(false);
    // Untie cin from cout to prevent automatic flushing of cout before each cin
    std::cin.tie(nullptr);

    const auto n = read<i32>();
    const auto q = read<i32>();

    auto dsf = DisjointSetForest(n);
    for (i32 i = 0; i < q; i += 1) {
        const auto t = read<i32>();
        const auto u = read<i32>();
        const auto v = read<i32>();

        if (t == 0) {
            dsf.unite_sets(u, v);
        } else if (t == 1) {
            std::cout << (dsf.connected(u, v) ? '1' : '0') << '\n';
        }
    }

    return 0;
}
