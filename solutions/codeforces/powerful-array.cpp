// === Problem Information ===
// Name: D. Powerful array
// Statement URL: https://codeforces.com/contest/86/problem/D

// === Solution Information ===
// Copyright (C) 2025 Nicolas Dumitru
// SPDX-License-Identifier: GPL-3.0-or-later
// Submission URL: https://codeforces.com/contest/86/submission/326528165
// Verdict: Accepted

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <ranges>
#include <vector>

using usize = std::size_t;
using u64 = std::uint64_t;

template <typename T>
inline auto read(std::istream &input = std::cin) -> T {
    T value;
    input >> value;
    return value;
}

template <typename T>
inline auto read_vector(const usize n, std::istream &input = std::cin)
    -> std::vector<T> {
    std::vector<T> v(n);
    for (auto &&x : v) {
        x = read<T>(input);
    }
    return v;
}

struct Query {
    usize id;
    // 0-indexed [begin, end)
    usize begin;
    usize end;

    Query() : id(0), begin(0), end(0) {}
};

inline auto read_queries(const usize n, std::istream &input = std::cin)
    -> std::vector<Query> {
    std::vector<Query> queries(n);
    for (const auto i : std::views::iota(usize{0}, n)) {
        queries[i].id = i;
        queries[i].begin = read<usize>(input) - 1;
        queries[i].end = read<usize>(input);
    }
    return queries;
}

// Mo's algorithm sqrt decomposition
class SqrtDecomp {
    const std::vector<usize> &v;
    const usize block_size;
    usize begin;
    usize end;
    std::vector<usize> freq;
    u64 subarray_power;

public:
    SqrtDecomp(const std::vector<usize> &vec)
        : v(vec), block_size(static_cast<usize>(std::sqrt(v.size())) + 1),
          begin(0), end(0), freq(1'000'000 + 1, 0), subarray_power(0) {}

    auto process_queries(std::vector<Query> &queries) -> std::vector<u64> {
        sort_queries(queries);

        std::vector<u64> results(queries.size());
        for (const auto &q : queries) {
            results[q.id] = process_query(q);
        }
        return results;
    }

    auto process_query(const Query &q) -> u64 {
        if (q.begin < begin) add_range(q.begin, begin);
        if (end < q.end) add_range(end, q.end);
        if (begin < q.begin) remove_range(begin, q.begin);
        if (q.end < end) remove_range(q.end, end);

        begin = q.begin;
        end = q.end;
        return subarray_power;
    }

private:
    inline auto get_block(const usize i) -> usize {
        return i / block_size;
    }

    inline auto sort_queries(std::vector<Query> &queries) -> void {
        std::sort(queries.begin(), queries.end(),
                  [this](const Query &a, const Query &b) -> bool {
                      const auto block_a = get_block(a.begin);
                      const auto block_b = get_block(b.begin);
                      return block_a != block_b ? block_a < block_b
                                                : a.end < b.end;
                  });
    }

    inline auto add_range(const usize b, const usize e) -> void {
        for (const auto i : std::views::iota(b, e)) {
            freq[v[i]] += 1;
            subarray_power +=
                (2 * static_cast<u64>(freq[v[i]]) - 1) * static_cast<u64>(v[i]);
        }
    }
    inline auto remove_range(const usize b, const usize e) -> void {
        for (const auto i : std::views::iota(b, e)) {
            subarray_power -=
                (2 * static_cast<u64>(freq[v[i]]) - 1) * static_cast<u64>(v[i]);
            freq[v[i]] -= 1;
        }
    }
};

auto main() -> int {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    const auto n = read<usize>();
    const auto t = read<usize>();

    const auto v = read_vector<usize>(n);
    auto queries = read_queries(t);

    SqrtDecomp s(v);
    for (const auto power : s.process_queries(queries)) {
        std::cout << power << '\n';
    }

    return 0;
}
