// === Problem Information ===
// Name: Forest Queries
// Statement URL: https://cses.fi/problemset/task/1652

// === Solution Information ===
// Copyright (C) 2025 Nicolas Dumitru
// SPDX-License-Identifier: GPL-3.0-or-later
// C++ standard: C++20
// Submission URL: https://cses.fi/problemset/result/17659037/
// Verdict: ACCEPTED

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <initializer_list>
#include <iostream>
#include <istream>
#include <vector>

using i64 = std::int64_t;

template <typename T>
inline auto read(std::istream &input = std::cin) -> T {
    T value;
    input >> value;
    return value;
}

template <class T>
class Tensor {
private:
    std::vector<i64> dims;
    std::vector<i64> stride;
    std::vector<T> data;

    auto flat_index(std::initializer_list<i64> idxs) const -> i64 {
        assert((i64)idxs.size() == (i64)dims.size());

        i64 pos = 0;
        i64 d = 0;

        for (i64 idx : idxs) {
            assert(0 <= idx && idx < dims[d]);
            pos += idx * stride[d];
            d += 1;
        }

        return pos;
    }

public:
    Tensor() = default;

    Tensor(std::vector<i64> dims_, T initial = T()) : dims(dims_) {
        i64 n = (i64)dims.size();
        stride.assign(n, 1);

        i64 total = 1;
        for (i64 i = n - 1; i >= 0; i -= 1) {
            stride[i] = total;
            total *= dims[i];
        }

        data.assign(total, initial);
    }

    auto operator()(std::initializer_list<i64> idxs) -> T & {
        return data[flat_index(idxs)];
    }

    auto operator()(std::initializer_list<i64> idxs) const -> const T & {
        return data[flat_index(idxs)];
    }

    template <class... Args>
    auto operator()(Args... args) -> T & {
        return (*this)({args...});
    }

    template <class... Args>
    auto operator()(Args... args) const -> const T & {
        return (*this)({args...});
    }

    auto size() const -> i64 {
        return (i64)data.size();
    }

    auto shape() const -> std::vector<i64> {
        return dims;
    }

    auto fill(const T &value) -> void {
        std::fill(data.begin(), data.end(), value);
    }

    auto raw() -> std::vector<T> & {
        return data;
    }

    auto raw() const -> const std::vector<T> & {
        return data;
    }
};

auto main() -> int {
    // Fast I/O
    // Disable synchronization between C++ and C I/O for faster input/output
    std::ios::sync_with_stdio(false);
    // Untie cin from cout to prevent automatic flushing of cout before each cin
    std::cin.tie(nullptr);

    const auto n = read<i64>();
    const auto q = read<i64>();

    const auto pref_sum = [&n]() -> Tensor<i64> {
        const auto d = n + 1;
        auto pref_sum = Tensor<i64>({d, d}, 0);
        for (auto y = i64{1}; y < d; y += 1) {
            for (auto x = i64{1}; x < d; x += 1) {
                const auto c = read<char>();
                const auto a = i64{c == '*' ? 1 : 0};
                pref_sum(y, x) =
                    a + pref_sum(y - 1, x) + pref_sum(y, x - 1) - pref_sum(y - 1, x - 1);
            }
        }
        return pref_sum;
    }();

    for (auto i = i64{0}; i < q; i += 1) {
        const auto y1 = read<i64>() - 1;
        const auto x1 = read<i64>() - 1;
        const auto y2 = read<i64>();
        const auto x2 = read<i64>();

        std::cout << pref_sum(y2, x2) - pref_sum(y2, x1) - pref_sum(y1, x2) + pref_sum(y1, x1)
                  << '\n';
    }

    return 0;
}