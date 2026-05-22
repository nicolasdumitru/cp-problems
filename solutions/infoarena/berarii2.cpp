// === Problem Information ===
// Name: Berarii2
// Statement URL: https://infoarena.ro/problema/berarii2

// === Solution Information ===
// Copyright (C) 2025 Nicolas Dumitru
// SPDX-License-Identifier: GPL-3.0-or-later
// C++ standard: C++14
// Submission URL: https://infoarena.ro/job_detail/3355287
// Verdict: 100/100

#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <istream>
#include <queue>
#include <vector>

using i32 = std::int32_t;
using i64 = std::int64_t;

auto fin = std::ifstream("berarii2.in");

template <typename T>
inline auto read(std::istream &input = fin) -> T {
    T value;
    input >> value;
    return value;
}

template <typename T>
inline auto read_vector(i64 n, std::istream &input = fin) -> std::vector<T> {
    std::vector<T> v(n);
    for (auto &&x : v) {
        x = read<T>(input);
    }
    return v;
}

template <typename T>
using AdjLists = std::vector<std::vector<T>>;

auto read_adj_transp(const i64 num_vertices, const i64 num_edges) -> AdjLists<i64> {
    auto adj_transp = AdjLists<i64>(num_vertices);

    for (auto i = i64{0}; i < num_edges; i += 1) {
        const auto from = read<i64>() - 1;
        const auto to = read<i64>() - 1;
        adj_transp[to].push_back(from);
    }

    return adj_transp;
}

auto read_sources(const i64 num_sources) -> std::vector<i64> {
    auto sources = read_vector<i64>(num_sources);
    std::transform(sources.begin(), sources.end(), sources.begin(),
                   [](const i64 x) -> i64 { return x - 1; });
    return sources;
}

auto bfs(const AdjLists<i64> &adj, const std::vector<i64> &sources) -> std::vector<bool> {
    auto visited = std::vector<bool>(adj.size(), false);
    auto q = std::queue<i64>();
    for (const auto s : sources) {
        q.push(s);
        visited[s] = true;
    }

    while (!q.empty()) {
        const auto u = q.front();
        q.pop();

        for (const auto v : adj[u]) {
            if (!visited[v]) {
                q.push(v);
                visited[v] = true;
            }
        }
    }

    return visited;
}

auto main() -> int {
    const auto num_vertices = read<i64>();
    const auto num_edges = read<i64>();
    const auto num_sources = read<i64>();

    const auto adj_transp = read_adj_transp(num_vertices, num_edges);
    const auto sources = read_sources(num_sources);

    auto visited = bfs(adj_transp, sources);

    auto fout = std::ofstream("berarii2.out");

    fout << std::count(visited.begin(), visited.end(), false) << "\n";

    for (auto i = i64{0}; i < num_vertices; i += 1) {
        if (!visited[i]) {
            fout << i + 1 << "\n";
        }
    }

    return 0;
}
