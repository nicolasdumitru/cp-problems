// === Problem Information ===
// Name: Rfinv
// Statement URL: https://infoarena.ro/problema/rfinv

// === Solution Information ===
// Copyright (C) 2025 Nicolas Dumitru
// SPDX-License-Identifier: GPL-3.0-or-later
// C++ standard: C++14
// Submission URL: https://infoarena.ro/job_detail/3355277
// Verdict: 100/100

#include <cstdint>
#include <fstream>
#include <iostream>
#include <istream>
#include <vector>

using i32 = std::int32_t;

auto fin = std::ifstream("rfinv.in");

template <typename T>
inline auto read(std::istream &input = fin) -> T {
    T value;
    input >> value;
    return value;
}

template <typename T>
inline auto read_vector(i32 n, std::istream &input = fin) -> std::vector<T> {
    std::vector<T> v(n);
    for (auto &&x : v) {
        x = read<T>(input);
    }
    return v;
}

template <typename T>
using Matrix = std::vector<std::vector<T>>;

template <typename T>
auto mat_new(const i32 rows, const i32 cols, T val) -> Matrix<T> {
    return Matrix<T>(rows, std::vector<T>(cols, val));
}

auto read_dist_matrix(const i32 n) -> Matrix<i32> {
    auto mat = Matrix<i32>();
    for (auto i = i32{0}; i < n; i += 1) {
        mat.push_back(read_vector<i32>(n));
    }

    return mat;
}

auto read_adj_matrix(const i32 num_vertices, const i32 num_edges) -> Matrix<bool> {
    auto adj_mat = mat_new(num_vertices, num_vertices, false);
    for (auto i = i32{0}; i < num_edges; i += 1) {
        const auto v = read<i32>() - 1;
        const auto u = read<i32>() - 1;
        adj_mat[u][v] = adj_mat[v][u] = true;
    }
    return adj_mat;
}

auto check_dist_matrix(const Matrix<i32> &dist, const Matrix<bool> &adj_mat) -> bool {
    const auto n = static_cast<i32>(dist.size());
    auto necessary_edge = mat_new<bool>(n, n, true);
    for (auto i = i32{0}; i < n; i += 1) {
        necessary_edge[i][i] = false;
    }
    for (auto k = i32{0}; k < n; k += 1) {
        for (auto i = i32{0}; i < n; i += 1) {
            for (auto j = i32{0}; j < n; j += 1) {
                // Skip when i == j because dist[i][i] = 0 and the problem statement guarantees
                // edges have positive weights.
                // Skip when k == i || k == j because otherwise every edge will be marked as not
                // necessary, rendering the final check useless.
                if (i == j || k == i || k == j) {
                    continue;
                }
                const auto new_dist = dist[i][k] + dist[k][j];
                if (new_dist < dist[i][j]) {
                    return false;
                } else if (new_dist == dist[i][j]) {
                    necessary_edge[i][j] = false;
                }
            }
        }
    }
    for (auto i = i32{0}; i < n; i += 1) {
        for (auto j = i32{0}; j < n; j += 1) {
            if (necessary_edge[i][j] && !adj_mat[i][j]) {
                return false;
            }
        }
    }
    return true;
}

auto main() -> int {
    auto fout = std::ofstream("rfinv.out");

    const auto t = read<i32>();
    for (auto i = i32{0}; i < t; i += 1) {
        const auto n = read<i32>();
        const auto m = read<i32>();
        const auto adj_mat = read_adj_matrix(n, m);
        const auto dist = read_dist_matrix(n);
        fout << (check_dist_matrix(dist, adj_mat) ? "DA" : "NU") << '\n';
    }

    return 0;
}
