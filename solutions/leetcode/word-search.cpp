// === Problem Information ===
// Name: 79. Word Search
// Statement URL: https://leetcode.com/problems/word-search/description/

// === Solution Information ===
// Copyright (C) 2025 Nicolas Dumitru
// SPDX-License-Identifier: GPL-3.0-or-later
// Submission URL: https://leetcode.com/problems/word-search/submissions/1969992853/
// Verdict: Accepted

#include <array>
#include <cstdint>
#include <iterator>
#include <utility>
#include <vector>

using i64 = std::int64_t;

class Solution {
public:
    static constexpr auto direction =
        std::array<std::pair<i64, i64>, 4>{{{0, 1}, {-1, 0}, {0, -1}, {1, 0}}};

    bool exist(const std::vector<std::vector<char>> &board, const std::string word) {
        auto visited = std::vector<std::vector<bool>>(
            board.size(), std::vector<bool>(board.front().size(), false));
        const auto back = [&](const auto &self, const i64 i, const i64 j, const i64 k) -> bool {
            if (board[i][j] != word[k]) {
                return false;
            }
            if (k + 1 >= static_cast<i64>(word.length())) {
                return true;
            }

            visited[i][j] = true;
            auto result = false;
            for (const auto &[delta_row, delta_col] : direction) {
                const auto i_prime = i + delta_row;
                const auto j_prime = j + delta_col;
                if (i_prime < 0 || i_prime >= std::ssize(board) || j_prime < 0 ||
                    j_prime >= std::ssize(board[i_prime])) {
                    continue;
                }
                result =
                    result || (!visited[i_prime][j_prime] && self(self, i_prime, j_prime, k + 1));
                if (result) {
                    break;
                }
            }
            visited[i][j] = false;
            return result;
        };

        for (auto i = i64{0}; i < std::ssize(board); i += 1) {
            for (auto j = i64{0}; j < std::ssize(board[i]); j += 1) {
                if (back(back, i, j, 0)) {
                    return true;
                }
            }
        }
        return false;
    }
};