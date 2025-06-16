// === Problem Information ===
// Name: G. White-Black Balanced Subtrees
// Statement URL: https://codeforces.com/contest/1676/problem/G

// === Solution Information ===
// Copyright (C) 2025 Nicolas Dumitru
// SPDX-License-Identifier: GPL-3.0-or-later
// Submission URL: https://codeforces.com/contest/1676/submission/324638486
// Verdict: Accepted

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>

using usize = std::size_t;

template <typename T>
inline auto read(std::istream &input = std::cin) -> T {
    T value;
    input >> value;
    return value;
}

const usize NIL = SIZE_MAX;

auto process_tree() -> usize {
    const auto n = read<usize>();
    std::vector<usize> num_children(n, 0);
    std::vector<usize> parent(n, NIL);
    std::vector<usize> black(
        n, 0); // black[u] count of black vertices in vertex u's subtree
    std::vector<usize> white(
        n, 0); // white[u] count of white vertices in vertex u's subtree

    // Read the tree and compute the number of children for each vertex.
    parent[0] = NIL;
    for (usize u = 1; u < n; u += 1) {
        const auto w = read<usize>() - 1;
        parent[u] = w;
        num_children[parent[u]] += 1;
    }

    usize balanced = 0;
    for (usize u = 0; u < n; u += 1) {
        if (read<char>() == 'B') {
            black[u] += 1;
        } else {
            white[u] += 1;
        }
        usize w = u;
        while (w != NIL && num_children[w] == 0) {
            if (black[w] == white[w]) {
                balanced += 1;
            }
            if (parent[w] != NIL) {
                black[parent[w]] += black[w];
                white[parent[w]] += white[w];
                num_children[parent[w]] -= 1;
            }
            w = parent[w];
        }
    }
    return balanced;
}

auto main() -> int {
    std::ios::sync_with_stdio(false);

    const auto t = read<usize>();
    for (usize i = 0; i < t; i += 1) {
        std::cout << process_tree() << '\n';
    }

    return 0;
}
