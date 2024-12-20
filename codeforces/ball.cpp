// Name: 12D Ball
// Problem: https://codeforces.com/contest/12/problem/D
// Submission: https://codeforces.com/contest/12/submission/296906704
// Verdict: Accepted

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>

using usize = std::size_t;
using isize = std::ptrdiff_t;
using u8 = std::uint8_t; // std input streams treat this as char
using i8 = std::int8_t;  // std input streams treat this as char
using u16 = std::uint16_t;
using i16 = std::int16_t;
using u32 = std::uint32_t;
using i32 = std::int32_t;
using u64 = std::uint64_t;
using i64 = std::int64_t;

using std::cerr;
using std::cout;

template <typename T>
inline auto read() -> T {
    T value = (std::cin >> value, value);
    return value;
}

// "Ladies" are represented as triples/3d points
struct Point {
    u32 x, y, z;
};

struct FenwickTree {
    std::vector<u32> bit;

    FenwickTree(usize n) : bit(n, 0) {}

    // g defines the ranges [g(i), i] used when querying
    auto g(usize i) -> usize {
        return i & (i + 1); // unset the trailing 1 bits
    }
    // h helps us propagate updates in the tree
    // h(i) is the parent of node i
    auto h(usize i) -> usize {
        return i | (i + 1); // set the least significant unset bit
    }

    auto update(usize i, u32 x) -> void {
        for (; i < bit.size() && x > bit[i]; i = h(i)) {
            bit[i] = x;
        }
    }
    // Queries return the greatest element of the prefix bit[0], ... bit[i]
    auto query(usize i) -> u32 {
        u32 ans = 0;
        for (i += 1; i > 0; i = g(i)) {
            i -= 1;
            ans = std::max(ans, bit[i]);
        }
        return std::max(ans, bit[0]);
    }
};

auto read_points(std::vector<Point> &points) -> void {
    for (auto &&p : points) {
        p.x = read<u32>();
    }
    for (auto &&p : points) {
        p.y = read<u32>();
    }
    for (auto &&p : points) {
        p.z = read<u32>();
    }
}

auto normalize_points(std::vector<Point> &points) -> void {
    std::sort(points.begin(), points.end(),
              [](Point a, Point b) { return a.y < b.y; });
    usize j = 1; // 1 indexed suffix queries -> 0-indexed prefix queries
    for (usize i = 0; i + 1 < points.size(); i += 1) {
        const usize y = points[i].y;
        points[i].y = j;
        if (y < points[i + 1].y) {
            j += 1;
        }
    }
    points[points.size() - 1].y = j;
}

auto body_count(const std::vector<Point> &points) -> usize {
    FenwickTree ladies(points.size());
    usize count = 0;
    for (auto &&p : points) {
        // The Fenwick tree supports prefix queries. The necessary suffix
        // queries are implemented as prefix queries for mirrored indexes.
        ladies.update(points.size() - p.y, p.x);

        if (p.y < points.size() &&
            ladies.query(points.size() - (p.y + 1)) > p.x) {
            count += 1;
        }
    }
    return count;
}

auto main() -> int {
    std::ios::sync_with_stdio(false);

    const auto n = read<usize>();
    std::vector<Point> points(n);

    read_points(points);
    normalize_points(points);
    std::sort(points.begin(), points.end(),
              [](const Point &a, const Point &b) -> bool {
                  if (a.z != b.z) {
                      return a.z > b.z;
                  } else if (a.y != b.y) {
                      return a.y < b.y;
                      // (points[i - 1].z == points[i].z &&
                      //  points[i - 1].y > points[i].y &&
                      //  points[i - 1].x > points[i].x) is an edge case false
                      // positive after the prefix queries. To avoid it, if
                      // points[i - 1].z == points[i].z, then
                      // points[i - 1].y < points[i].y.
                  }
                  return a.x > b.x; // minimize unnecessary Fenwick tree updates
              });

    cout << body_count(points) << '\n';

    return 0;
}
