// === Problem Information ===
// Name: RangeMode
// Statement URL: https://www.infoarena.ro/problema/rangemode

// === Solution Information ===
// Copyright (C) 2025 Nicolas Dumitru
// SPDX-License-Identifier: GPL-3.0-or-later
// Submission URL: https://www.infoarena.ro/job_detail/3301407
// Verdict: Evaluare completa: 100 puncte

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <istream>
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

struct Query {
    usize id;
    usize begin;
    usize end;

    Query() : id(0), begin(0), end(0) {}
};

inline auto read_queries(const usize m, std::istream &input)
    -> std::vector<Query> {
    std::vector<Query> queries(m);
    for (usize i = 0; i < queries.size(); i += 1) {
        queries[i].id = i;
        // Read & convert to 0-indexed [begin, end) queries
        queries[i].begin = read<usize>(input) - 1;
        queries[i].end = read<usize>(input);
    }
    return queries;
}

auto sqrt_decomp(const std::vector<usize> &v, std::vector<Query> &queries)
    -> std::vector<usize> {
    const usize block_size = std::sqrt(v.size()) + 1;

    const auto get_block = [block_size](const usize i) -> usize {
        return i / block_size;
    };

    std::sort(queries.begin(), queries.end(),
              [get_block](const Query &a, const Query &b) -> bool {
                  const usize a_block = get_block(a.begin);
                  const usize b_block = get_block(b.begin);
                  return a_block != b_block ? a_block < b_block : a.end < b.end;
              });

    std::vector<usize> freq(100'000 + 1, 0);
    const auto optimize = [&freq](usize best, usize candidate) -> usize {
        return freq[candidate] > freq[best] ||
                       (freq[candidate] == freq[best] && candidate < best)
                   ? candidate
                   : best;
    };
    const auto update = [&v, &freq, &optimize](usize begin, usize end,
                                               usize base_mode) -> usize {
        usize mode = base_mode;
        for (usize i = begin; i < end; i += 1) {
            freq[v[i]] += 1;
            mode = optimize(mode, v[i]);
        }
        return mode;
    };
    const auto remove = [&v, &freq](usize begin, usize end) -> void {
        for (usize i = begin; i < end; i += 1) {
            freq[v[i]] -= 1;
        }
    };

    usize mode = 0;
    usize begin = 0;
    usize end = 0;
    std::vector<usize> modes(queries.size());
    for (const Query &query : queries) {
        if (begin <= query.begin) {
            begin = block_size * (get_block(query.begin) + 1);
            end = begin;
            std::fill(freq.begin(), freq.end(), 0);
        }
        mode = update(end, query.end, mode);
        end = std::max(end, query.end);
        const usize e = std::min(begin, query.end);
        modes[query.id] = update(query.begin, e, mode);
        remove(query.begin, e);
    }
    return modes;
}

auto main() -> int {
    std::ios::sync_with_stdio(false);
    std::ifstream fin("rangemode.in");

    const auto n = read<usize>(fin);
    const auto m = read<usize>(fin);

    const auto v = read_vector<usize>(n, fin);
    auto queries = read_queries(m, fin);

    std::ofstream fout("rangemode.out");
    const auto results = sqrt_decomp(v, queries);
    for (const auto res : results) {
        fout << res << '\n';
    }

    return 0;
}
