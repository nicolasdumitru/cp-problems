// === Problem Information ===
// Name: Nezzar and Binary String
// Statement URL: https://codeforces.com/contest/1478/problem/E

// === Solution Information ===
// Copyright (C) 2025 Nicolas Dumitru
// SPDX-License-Identifier: GPL-3.0-or-later
// Submission URL: https://codeforces.com/contest/1478/submission/325687686
// Verdict: Accepted

#include <bit>
#include <cstddef>
#include <iostream>
#include <ranges>
#include <string>
#include <vector>

using usize = std::size_t;

template <typename T>
inline auto read(std::istream &input = std::cin) -> T {
    T value;
    input >> value;
    return value;
}

inline auto read_queries(const usize q)
    -> std::vector<std::pair<usize, usize>> {
    std::vector<std::pair<usize, usize>> queries(q);
    for (auto &&query : queries) {
        query.first = read<usize>() - 1;
        query.second = read<usize>() - 1;
    }
    return queries;
}

// A segment tree supporting three operations:
//
// * range_set(begin, end, val)
//   Sets all elements in [begin, end] to val.
// * range_sum(begin, end)
//   Returns the sum of all elements in [begin, end].
// * operator==(s)
//   Compares the binary string encoded by the segment tree with string s.
//
// Invariant:
// - tree[i] stores the sum of values in the subtree rooted at index i.
// - If lazy[i] is true, then the subtree under i needs to be updated to reflect
//   tree[i].
//
// Notes:
// - Although optimized for operating on binary strings (0s and 1s),
//   range_sum and range_set are rather general-purpose and reusable.
// - The segment tree uses `usize` because internal nodes count actual elements
//   in memory, and this avoids the need for external type conversions.
class SegmentTree {
    const usize root;
    const usize leaf_segments;
    const usize max_leaf_segments;
    const usize aux_segments; // This includes the unused 0 segment
    std::vector<usize> tree;
    std::vector<bool> lazy;

public:
    SegmentTree(const std::string &binary_string)
        : root(1), leaf_segments(binary_string.size()),
          max_leaf_segments(1 << std::bit_width(leaf_segments - 1)),
          aux_segments(max_leaf_segments),
          tree(aux_segments + max_leaf_segments, 0), lazy(tree.size(), false) {
        for (const usize i : std::views::iota(usize{0}, leaf_segments)) {
            tree[aux_segments + i] = binary_string[i] == '1' ? 1 : 0;
        }
        for (const usize i :
             std::views::iota(usize{1}, aux_segments) | std::views::reverse) {
            tree[i] = tree[left(i)] + tree[right(i)];
        }
    }

    auto range_set(const usize begin, const usize end, const usize val)
        -> void {
        usize b = aux_segments + begin;
        usize e = aux_segments + end;

        push_path(b);
        push_path(e);

        usize h = 0;
        while (b <= e) {
            if (is_right_child(b)) {
                tree[b] = val << h;
                lazy[b] = true;
                b += 1;
            }
            b = parent(b);

            if (is_left_child(e)) {
                tree[e] = val << h;
                lazy[e] = true;
                e -= 1;
            }
            e = parent(e);
            h += 1;
        }

        pull_path(aux_segments + begin);
        pull_path(aux_segments + end);
    }

    auto range_sum(const usize begin, const usize end) -> usize {
        usize sum = 0;
        usize b = aux_segments + begin;
        usize e = aux_segments + end;

        push_path(b);
        push_path(e);

        while (b <= e) {
            if (is_right_child(b)) {
                sum += tree[b];
                b += 1;
            }
            b = parent(b);

            if (is_left_child(e)) {
                sum += tree[e];
                e -= 1;
            }
            e = parent(e);
        }
        return sum;
    }

    auto operator==(const std::string &s) -> bool {
        push_all();

        bool result = true;
        for (usize i = 0; i < leaf_segments && result; i += 1) {
            result = s[i] == static_cast<char>('0' + tree[aux_segments + i]);
        }
        return result;
    }

private:
    auto push_path(const usize node) -> void {
        for (usize h = std::bit_width(node) - 1; h > 0; h -= 1) {
            const usize i = ancestor(node, h);
            push(i);
        }
    }

    auto push_all() -> void {
        for (const usize i : std::views::iota(root, aux_segments)) {
            push(i);
        }
    }
    auto push(const usize node) -> void {
        if (!lazy[node]) return;

        tree[left(node)] = tree[node] >> 1;
        tree[right(node)] = tree[node] >> 1;

        lazy[left(node)] = true;
        lazy[right(node)] = true;
        lazy[node] = false;
    }

    auto pull_path(const usize node) -> void {
        for (usize i = parent(node); i >= root; i = parent(i)) {
            tree[i] = lazy[i] ? tree[i] : tree[left(i)] + tree[right(i)];
        }
    }

    // Various methods that abstract the internal structure of the segment
    // tree for clarity and convenience.
    inline auto left(const usize node) -> usize {
        return node << 1;
    }
    inline auto is_left_child(const usize node) -> bool {
        return (node & 1) == 0;
    }
    inline auto right(const usize node) -> usize {
        return (node << 1) + 1;
    }
    inline auto is_right_child(const usize node) -> bool {
        return (node & 1) == 1;
    }
    inline auto parent(const usize node) -> usize {
        return ancestor(node, 1);
    }
    inline auto ancestor(const usize node, const usize height) -> usize {
        return node >> height;
    }
};

auto main() -> int {
    std::ios::sync_with_stdio(false);

    const auto t = read<usize>();
    for ([[maybe_unused]] const usize _ : std::views::iota(usize{0}, t)) {
        [[maybe_unused]] const auto n = read<usize>();
        const auto q = read<usize>();
        const auto s = read<std::string>();
        const auto f = read<std::string>();

        const auto queries = read_queries(q);
        SegmentTree st(f);
        bool valid = true;
        for (usize i = queries.size(); i >= 1 && valid; i -= 1) {
            const auto &query = queries[i - 1];
            const usize sum = st.range_sum(query.first, query.second);
            const usize range_size = query.second - query.first + 1;
            if (2 * sum > range_size) {
                st.range_set(query.first, query.second, 1);
            } else if (2 * sum < range_size) {
                st.range_set(query.first, query.second, 0);
            } else {
                std::cout << "NO\n";
                valid = false;
            }
        }

        if (valid) {
            std::cout << (st == s ? "YES" : "NO") << '\n';
        }
    }

    return 0;
}
