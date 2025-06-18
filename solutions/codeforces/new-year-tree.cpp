// === Problem Information ===
// Name: New Year Tree
// Statement URL: https://codeforces.com/contest/620/problem/E

// === Solution Information ===
// Copyright (C) 2025 Nicolas Dumitru
// SPDX-License-Identifier: GPL-3.0-or-later
// Submission URL: https://codeforces.com/contest/620/submission/325066438
// Verdict: Accepted

// Note: In this implementation, we distinguish between vertices and nodes by
// convention: vertices refer to elements of graphs proper, while nodes are
// elements of data structures that are represented as graphs (e.g., trees) for
// visualization or conceptual clarity.

#include <bit>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
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
    const usize NIL = SIZE_MAX;

    std::vector<std::vector<usize>>
        adj; // `adj.size()` is the number of vertices in the tree.
    std::vector<usize> visits;
    std::vector<usize> size;

public:
    Tree(const usize n) : adj(n, std::vector<usize>(0)), visits(0), size(n) {}

    auto add_edge(const usize u, const usize v) -> void {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Mapping that gives the position of a given vertex in the flattened tree
    auto flatten() -> std::pair<std::vector<usize>, std::vector<usize>> {
        visits.clear();
        visits.reserve(adj.size()); // Prevent unnecessary future resizing.
        dfs_flatten(0, NIL);

        std::vector<usize> mapping(adj.size());
        for (const auto pos : std::views::iota(usize{0}, adj.size())) {
            mapping[visits[pos]] = pos;
        }
        return std::pair(mapping, size);
    }

private:
    // This method expects `visits` to be of size 0 when called initially.
    auto dfs_flatten(const usize v, const usize p) -> void {
        visits.push_back(v);
        size[v] = 1;
        for (const auto u : adj[v]) {
            if (u == p) continue;
            dfs_flatten(u, v);
            size[v] += size[u];
        }
    }
};

// A segment tree supporting two operations:
//
// * range_set(begin, end, mask)
//   Sets all elements in [begin, end] to mask.
// * range_popcount(begin, end)
//   Returns the number of distinct set bits of all elements in [begin, end].
//
// Contract: tree[i] is the mask of values in i's subtree. If lazy[i] is true,
// then tree[i] needs to be written everywhere in i's subtree.
class SegmentTree {
    const usize root;
    const usize leaf_segments;
    const usize max_leaf_segments;
    const usize aux_segments; // This includes the unused 0 segment
    std::vector<usize> tree;
    std::vector<bool> lazy;

public:
    SegmentTree(std::vector<usize> masks)
        : root(1), leaf_segments(masks.size()),
          max_leaf_segments(1 << std::bit_width(leaf_segments - 1)),
          aux_segments(max_leaf_segments),
          tree(aux_segments + max_leaf_segments), lazy(tree.size()) {
        for (const usize i : std::views::iota(usize{0}, leaf_segments)) {
            tree[aux_segments + i] = masks[i];
        }
        for (const usize i :
             std::views::iota(root, aux_segments) | std::views::reverse) {
            tree[i] = tree[left(i)] | tree[right(i)];
        }
    }

    auto range_set(const usize begin, const usize end, usize mask) -> void {
        usize b = aux_segments + begin;
        usize e = aux_segments + end;
        const usize orig_b = b;
        const usize orig_e = e;
        push_path(b);
        push_path(e);

        while (b <= e) {
            if (!is_left_child(b)) {
                tree[b] = mask;
                lazy[b] = true;
                b += 1;
            }
            b = parent(b);

            if (!is_right_child(e)) {
                tree[e] = mask;
                lazy[e] = true;
                e -= 1;
            }
            e = parent(e);
        }

        pull_path(orig_b);
        pull_path(orig_e);
    }

    auto range_popcount(const usize begin, const usize end) -> usize {
        usize mask = 0;

        usize b = aux_segments + begin;
        usize e = aux_segments + end;
        push_path(b);
        push_path(e);

        while (b <= e) {
            if (is_right_child(b)) {
                mask |= tree[b];
                b += 1;
            }
            b = parent(b);

            if (is_left_child(e)) {
                mask |= tree[e];
                e -= 1;
            }
            e = parent(e);
        }
        return std::popcount(mask);
    }

private:
    auto push_path(const usize node) -> void {
        for (usize h = std::bit_width(node) - 1; h > 0; h -= 1) {
            const usize i = ancestor(node, h);
            if (lazy[i]) {
                tree[left(i)] = tree[i];
                tree[right(i)] = tree[i];

                lazy[left(i)] = lazy[i];
                lazy[right(i)] = lazy[i];
                lazy[i] = false;
            }
        }
    }

    auto pull_path(const usize node) -> void {
        for (usize i = parent(node); i >= root; i = parent(i)) {
            tree[i] = lazy[i] ? tree[i] : tree[left(i)] | tree[right(i)];
        }
    }

    // Various methods that abstract the internal structure of the segment
    // tree for clarity and convenience.
    inline auto left(const usize i) -> usize {
        return i << 1;
    }
    inline auto is_left_child(const usize i) -> bool {
        return (i & 1) == 0;
    }
    inline auto right(const usize i) -> usize {
        return (i << 1) + 1;
    }
    inline auto is_right_child(const usize i) -> bool {
        return (i & 1) == 1;
    }
    inline auto parent(const usize i) -> usize {
        return ancestor(i, 1);
    }
    inline auto ancestor(const usize i, const usize height) -> usize {
        return i >> height;
    }
};

auto main() -> int {
    std::ios::sync_with_stdio(false);

    const auto n = read<usize>();
    const auto m = read<usize>();

    // Read the color of each vertex.
    const auto colors = read_vector<usize>(n);

    // Build the tree and flatten it.
    Tree t(n);
    for (const auto _ : std::views::iota(usize{0}, n - 1)) {
        usize u = read<usize>() - 1;
        usize v = read<usize>() - 1;
        t.add_edge(u, v);
    }
    const auto [indices, subtree_sizes] = t.flatten();

    // Convert the colors to bit masks and map them to their positions in the
    // flattened tree.
    auto color_mask = [](usize c) -> usize { return usize{1} << c; };
    std::vector<usize> mapped_colors(colors.size());
    for (const auto i : std::views::iota(usize{0}, indices.size())) {
        mapped_colors[indices[i]] = color_mask(colors[i] - 1);
    }

    // Use a segment tree to process the updates and queries for the flattened
    // tree.
    SegmentTree st(mapped_colors);
    for (const auto _ : std::views::iota(usize{0}, m)) {
        const auto t = read<usize>();
        const auto vertex = read<usize>() - 1;
        const auto range_begin = indices[vertex];
        const auto range_end = range_begin + subtree_sizes[vertex] - 1;
        if (t == 1) {
            st.range_set(range_begin, range_end, color_mask(read<usize>() - 1));
        } else {
            std::cout << st.range_popcount(range_begin, range_end) << "\n";
        }
    }

    return 0;
}
