// Problem: https://codeforces.com/contest/1354/problem/D
// Submission: https://codeforces.com/contest/1354/submission/282195462
// Status: Accepted

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <istream>
#include <vector>

using usize = std::size_t;
using i8 = std::int8_t;
using i32 = std::int32_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;

using std::istream;
using std::vector;

istream &in = std::cin;

const usize MAX_N = 1'000'000;

class FenwickTree {
private:
    vector<u32> bit;
    u32 n; // The tree contains n elements a[i] and a[i] <= n.
    u32 max_p2;

    // Ranges will be [g(i), i].
    // g(i) <= i
    u32 g(u32 i) {
        return i & (i + 1);
    }

    // h(j) is used to propagate updates in the tree.
    // h(j) > j
    u32 h(u32 j) {
        return j | (j + 1);
    }

    void update(u32 k, i8 delta);
    u32 findStatistic(u32 k);

public:
    FenwickTree(u32 size, const vector<u32> &a);
    void query(i32 k);
    void processQueries(u32 q);

    u32 getFirst() {
        u32 first = findStatistic(1);
        return first <= n ? first : 0;
    }
};

FenwickTree::FenwickTree(u32 size, const vector<u32> &a)
    : n(size), bit(size + 1, 0) {
    for (max_p2 = n; (max_p2 & max_p2 - 1) != 0; max_p2 &= max_p2 - 1) {}
    for (u32 i = 0; i <= n; i += 1) {
        bit[i] += a[i];
        if (h(i) <= n) {
            bit[h(i)] += bit[i];
        }
    }
}

void FenwickTree::query(i32 k) {
    if (k >= 0) {
        update(k, +1); // insert k
    } else {
        update(findStatistic(-k), -1); // remove k'th order statistic
    }
}

void FenwickTree::update(u32 k, i8 delta) {
    for (; k <= n; k = h(k)) {
        bit[k] += delta;
    }
}

u32 FenwickTree::findStatistic(u32 k) {
    u32 pos = 0;
    for (u32 interval = max_p2; interval > 0; interval /= 2) {
        if (pos + interval - 1 <= n && bit[pos + interval - 1] < k) {
            k -= bit[pos + interval - 1];
            pos += interval;
        }
    }
    return pos;
}

void FenwickTree::processQueries(u32 q) {
    for (u32 i = 0; i < q; i += 1) {
        u32 k;
        in >> k;
        query(k);
    }
}

void readFrequencyVector(vector<u32> &a, usize n) {
    for (u32 i = 0; i < n; i += 1) {
        u32 element;
        in >> element;
        a[element] += 1;
    }
}

int main() {
    u32 n, q;
    std::ios::sync_with_stdio(false);
    in >> n >> q;

    vector<u32> a(n + 1, 0);
    readFrequencyVector(a, n);

    FenwickTree bit(n, a);
    bit.processQueries(q);
    std::cout << bit.getFirst() << '\n';

    return 0;
}
