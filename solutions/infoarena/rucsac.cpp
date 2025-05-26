// === Problem Information ===
// Name: Problema rucsacului (en. 0-1 knapsack problem)
// Statement URL: https://www.infoarena.ro/problema/rucsac

// === Solution Information ===
// Copyright (C) 2025 Nicolas Dumitru
// SPDX-License-Identifier: GPL-3.0-or-later
// Submission URL: https://www.infoarena.ro/job_detail/3298076
// Verdict: Evaluare completa: 100 puncte

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <istream>
#include <ostream>
#include <utility>
#include <vector>

using usize = std::size_t;
using u32 = std::uint_fast32_t;

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

struct Item {
    usize weight;
    u32 value;

    Item() : weight(0), value(0) {}

    friend std::istream &operator>>(std::istream &input, Item &item) {
        input >> item.weight >> item.value;

        return input;
    }
};

auto knapsack(std::vector<Item> &items, usize max_weight) -> u32 {
    std::vector<std::vector<u32>> val(2, std::vector<u32>(max_weight + 1, 0));
    usize prev = 1;
    usize curr = 0;

    for (usize i = 0; i < items.size(); i += 1, std::swap(prev, curr)) {
        const auto w = items[i].weight;
        const auto v = items[i].value;
        for (usize cw = 0; cw <= max_weight; cw += 1) {
            val[curr][cw] = w <= cw
                                ? std::max(val[prev][cw], val[prev][cw - w] + v)
                                : val[prev][cw];
        }
    }

    return val[prev][max_weight];
}

auto main() -> int {
    std::ios::sync_with_stdio(false);

    std::ifstream knapsack_in("rucsac.in");

    const auto n = read<usize>(knapsack_in);
    const auto w = read<usize>(knapsack_in);

    auto items = read_vector<Item>(n, knapsack_in);

    std::ofstream knapsack_out("rucsac.out");
    knapsack_out << knapsack(items, w) << std::endl;

    return 0;
}
