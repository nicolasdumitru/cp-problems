// === Problem Information ===
// Name: FREQ2
// Statement URL: https://www.spoj.com/problems/FREQ2/

// === Solution Information ===
// Copyright (C) 2024 Nicolas Dumitru
// SPDX-License-Identifier: GPL-3.0-or-later
// Submission URL: https://www.spoj.com/status/ns=33636774
// Verdict: accepted

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <vector>

using usize = std::size_t;
using isize = std::ptrdiff_t;
using u8 = std::uint8_t;
using i8 = std::int8_t;
using u16 = std::uint16_t;
using i16 = std::int16_t;
using u32 = std::uint32_t;
using i32 = std::int32_t;
using u64 = std::uint64_t;
using i64 = std::int64_t;

const usize MAXN = 100'000;

void read_vector(std::vector<u32> &v) {
    for (auto &i : v) {
        std::cin >> i;
    }
}

struct Range {
    usize begin;
    usize end;
};

struct Query {
    usize id;
    usize begin_block;
    Range range;
};

void read_queries(std::vector<Query> &v, usize block_size) {
    for (usize i = 0; i < v.size(); i += 1) {
        v[i].id = i;
        std::cin >> v[i].range.begin >> v[i].range.end;
        v[i].begin_block = v[i].range.begin / block_size;
    }
}

class Sequence {
private:
    const std::vector<u32> seq;
    std::vector<usize> freq;
    std::vector<usize> freq_freq;
    usize max_freq;
    Range range;

    enum Increment { Add = 1, Remove = -1 };
    void freq_update(usize pos, Increment inc) {
        usize &f = freq[seq[pos]];
        freq_freq[f] -= freq_freq[f] > 0 ? 1 : 0;
        f += static_cast<isize>(inc);
        freq_freq[f] += 1;
    }

public:
    Sequence(const std::vector<u32> &v)
        : seq(v), freq(MAXN + 1, 0), freq_freq(MAXN + 1, 0), max_freq(0) {
        range.begin = range.end = 0;
        freq_update(range.begin, Add);
        max_freq = freq[seq[range.begin]];
    }

    usize query(Query q) {
        for (usize b = range.begin; q.range.begin < b; b -= 1) {
            freq_update(b - 1, Add);
            max_freq = std::max(freq[seq[b - 1]], max_freq);
        }

        for (usize e = range.end + 1; e <= q.range.end; e += 1) {
            freq_update(e, Add);
            max_freq = std::max(freq[seq[e]], max_freq);
        }

        for (usize b = range.begin; b < q.range.begin; b += 1) {
            freq_update(b, Remove);
            max_freq = freq_freq[max_freq] > 0 ? max_freq : max_freq - 1;
        }

        for (usize e = range.end; q.range.end < e; e -= 1) {
            freq_update(e, Remove);
            max_freq = freq_freq[max_freq] > 0 ? max_freq : max_freq - 1;
        }

        range = q.range;

        return max_freq;
    }
};

int main() {
    std::ios::sync_with_stdio(false);

    usize n;
    u32 q;
    std::cin >> n >> q;
    usize block_size = std::sqrt(n);

    std::vector<u32> v(n);
    read_vector(v);

    std::vector<Query> queries(q);
    read_queries(queries, block_size);
    std::sort(queries.begin(), queries.end(),
              [](const Query &a, const Query &b) -> bool {
                  if (a.begin_block != b.begin_block) {
                      return a.begin_block < b.begin_block;
                  } else {
                      return a.range.end < b.range.end;
                  }
              });

    Sequence s(v);
    std::vector<usize> ans(q);
    for (auto i : queries) {
        ans[i.id] = s.query(i);
    }
    for (auto i : ans) {
        std::cout << i << '\n';
    }

    return 0;
}
