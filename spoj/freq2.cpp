// Problem: https://www.spoj.com/problems/FREQ2/
// Submission: https://www.spoj.com/status/ns=33631898#
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

bool compare_queries(const Query &a, const Query &b) {
    if (a.begin_block != b.begin_block) {
        return a.begin_block < b.begin_block;
    } else {
        return a.range.end < b.range.end;
    }
}

struct Sequence {
    const std::vector<u32> seq;
    std::vector<usize> freq;
    std::vector<usize> freq_freq;
    usize max_freq;
    Range range;

    Sequence(const std::vector<u32> &v, Range r)
        : seq(v), freq(MAXN + 1, 0), freq_freq(MAXN + 1, 0), max_freq(0),
          range(r) {

        for (usize i = range.begin; i <= range.end; i += 1) {
            update(i, Add);
            max_freq = std::max(freq[seq[i]], max_freq);
        }
    }

    enum Increment { Add = (isize)1, Remove = (isize)-1 };
    void update(usize pos, Increment inc) {
        usize &f = freq[seq[pos]];
        freq_freq[f] -= freq_freq[f] > 0 ? 1 : 0;
        f += inc;
        freq_freq[f] += 1;
    }

    usize query(Query q) {
        for (usize b = range.begin; q.range.begin < b;
             b -= 1) {
            update(b - 1, Add);
            max_freq = std::max(freq[seq[b - 1]], max_freq);
        }

        for (usize e = range.end + 1; e <= q.range.end; e += 1) {
            update(e, Add);
            max_freq = std::max(freq[seq[e]], max_freq);
        }

        for (usize b = range.begin; b < q.range.begin; b += 1) {
            update(b, Remove);
            max_freq = freq_freq[max_freq] > 0 ? max_freq : max_freq - 1;
        }

        for (usize e = range.end; q.range.end < e; e -= 1) {
            update(e, Remove);
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
    std::sort(queries.begin(), queries.end(), compare_queries);

    Sequence s(v, queries[0].range);
    std::vector<usize> ans(q);
    for (auto i : queries) {
        ans[i.id] = s.query(i);
    }
    for (auto i : ans) {
        std::cout << i << '\n';
    }

    return 0;
}
