// === Problem Information ===
// Name: Road Construction
// Statement URL: https://cses.fi/problemset/task/1676

// === Solution Information ===
// Copyright (C) 2025 Nicolas Dumitru
// SPDX-License-Identifier: GPL-3.0-or-later
// Submission URL: https://cses.fi/problemset/result/13515551/
// Verdict: ACCEPTED

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <ranges>
#include <vector>

using usize = std::size_t;

template <typename T>
inline auto read(std::istream &input = std::cin) -> T {
    T value;
    input >> value;
    return value;
}

class DisjointSetForest {
    std::vector<usize> parent;
    std::vector<usize> size;
    usize components; // connected components
    usize max_size;

public:
    DisjointSetForest(usize nodes)
        : parent(nodes), size(nodes), components(nodes), max_size(1) {
        for (const auto node : std::views::iota(usize{0}, nodes)) {
            make_set(node);
        }
    }

    auto find_set(const usize node) -> usize {
        if (parent[node] != node) {
            parent[node] = find_set(parent[node]); // Path compression
        }
        return parent[node];
    }

    auto union_sets(usize x, usize y) -> void {
        x = find_set(x);
        y = find_set(y);
        if (x == y) return;

        components -= 1;
        // Union by size
        if (size[x] > size[y]) {
            absorb(x, y);
        } else {
            absorb(y, x);
        }
    }

    inline auto num_sets() const -> usize {
        return components;
    }
    inline auto max_set_size() const -> usize {
        return max_size;
    }

private:
    // make_set is unsafe in this implementation and hence private
    inline auto make_set(const usize node) -> void {
        parent[node] = node;
        size[node] = 1;
    }

    // Contract: Expects both argument to be distinct tree roots and that
    // size[larger] >= size[smaller]. Absorbs the smaller tree in the larger,
    // then updates the size of the larger tree and the maximum size
    // accordingly.
    inline auto absorb(const usize larger, const usize smaller) -> void {
        parent[smaller] = larger;
        size[larger] += size[smaller];
        max_size = std::max(max_size, size[larger]);
    }
};

auto main() -> int {
    std::ios::sync_with_stdio(false); // Disable synchronization between C++ and
                                      // C I/O for faster input/output

    const auto n = read<usize>();
    const auto m = read<usize>();

    DisjointSetForest dsf(n);

    for ([[maybe_unused]] const auto _ : std::views::iota(usize{0}, m)) {
        const usize x = read<usize>() - 1;
        const usize y = read<usize>() - 1;
        dsf.union_sets(x, y);
        std::cout << dsf.num_sets() << ' ' << dsf.max_set_size() << '\n';
    }

    return 0;
}
