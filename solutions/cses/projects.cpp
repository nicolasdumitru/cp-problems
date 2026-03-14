// === Problem Information ===
// Name: Projects
// Statement URL: https://cses.fi/problemset/task/1140

// === Solution Information ===
// Copyright (C) 2025 Nicolas Dumitru
// SPDX-License-Identifier: GPL-3.0-or-later
// Submission URL: https://cses.fi/problemset/result/16558825/
// Verdict: ACCEPTED

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <istream>
#include <iterator>
#include <ranges>
#include <vector>

using i32 = std::int32_t;
using i64 = std::int64_t;

template <typename T>
inline auto read(std::istream &input = std::cin) -> T {
    T value;
    input >> value;
    return value;
}

template <typename T>
inline auto read_vector(i64 n, std::istream &input = std::cin) -> std::vector<T> {
    std::vector<T> v(n);
    for (auto &&x : v) {
        x = read<T>(input);
    }
    return v;
}

struct Project {
    i32 start_day;
    i32 end_day;
    i64 reward;

    friend auto operator>>(std::istream &in, Project &p) -> std::istream & {
        in >> p.start_day >> p.end_day >> p.reward;
        return in;
    }
};

auto max_reward(std::vector<Project> &projects) -> i64 {
    std::sort(projects.begin(), projects.end(),
              [](const Project &a, const Project &b) -> bool { return a.end_day < b.end_day; });

    auto max_rewards = std::vector<i64>();
    max_rewards.reserve(projects.size());
    max_rewards.push_back(projects.front().reward);
    for (const auto &p : projects | std::views::drop(1)) {
        auto lower = std::lower_bound(
            projects.begin(), std::next(projects.begin(), max_rewards.size()), p.start_day,
            [](const auto &proj, const auto day) -> bool { return proj.end_day < day; });
        const auto best_compatible_reward =
            lower == projects.begin()
                ? 0
                : max_rewards[std::distance(projects.begin(), std::prev(lower))];
        max_rewards.push_back(std::max(p.reward + best_compatible_reward, max_rewards.back()));
    }
    return max_rewards.back();
}

auto main() -> int {
    // Fast I/O
    // Disable synchronization between C++ and C I/O for faster input/output
    std::ios::sync_with_stdio(false);
    // Untie cin from cout to prevent automatic flushing of cout before each cin
    std::cin.tie(nullptr);

    const auto num_projects = read<i64>();
    auto projects = read_vector<Project>(num_projects);

    std::cout << max_reward(projects);

    return 0;
}
