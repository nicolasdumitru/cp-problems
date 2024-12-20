// Name: 292E Copying Data
// Problem: https://codeforces.com/contest/292/problem/E
// Submission: https://codeforces.com/contest/292/submission/297551255
// Verdict: Accepted

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

using std::cout;

template <typename T>
inline auto read() -> T {
    T value = (std::cin >> value, value);
    return value;
}

template <typename T>
inline auto read_vector(usize n) -> std::vector<T> {
    std::vector<T> v(n);
    for (auto &&x : v) {
        x = read<T>();
    }
    return v;
}

// Unset the least significant set bit
inline auto pop_last(const usize n) -> usize {
    return n & n - 1;
}

struct Segment {
    isize offset;
    u32 uid;                         // update id
    Segment() : offset(0), uid(0) {} // 0 by default
};

template <typename T>
class CopySegmentTree {
    std::vector<Segment> tree;
    const usize origin;
    u32 update_count;

    const std::vector<T> &source;
    const std::vector<T> &dest;

    inline auto parent(const usize i) -> usize {
        return i >> 1;
    }
    inline auto left_child(const usize i) -> usize {
        return 2 * i;
    }
    inline auto right_child(const usize i) -> usize {
        return 2 * i + 1;
    }
    inline auto is_left_child(const usize i) -> bool {
        return (i & 1) == 0;
    }
    inline auto is_right_child(const usize i) -> bool {
        return (i & 1) == 1;
    }

    inline auto get_origin(const usize n) -> usize {
        usize orig;
        for (orig = n; pop_last(orig) > 0; orig = pop_last(orig)) {}
        return n > orig ? orig << 1 : orig;
    }

public:
    CopySegmentTree(const std::vector<T> &a, const std::vector<T> &b)
        : origin(get_origin(b.size())), update_count(0), source(a), dest(b) {
        tree.resize(b.size() + origin);
    }

    auto copy(const usize x, const usize y, const usize k) -> void {
        // The parameters follow the problem statement's naming convention
        // IMPORTANT: this implementation relies on 0-based indexing
        isize offset = static_cast<isize>(x) - static_cast<isize>(y);
        usize begin = origin + y;
        usize end = origin + y + k - 1;
        update_count += 1;
        while (begin <= end) {
            if (is_left_child(begin) && is_right_child(end)) {
                begin = parent(begin);
                end = parent(end);
            } else {
                if (is_right_child(begin)) {
                    tree[begin].offset = offset;
                    tree[begin].uid = update_count;
                    begin += 1;
                }
                if (is_left_child(end)) {
                    tree[end].offset = offset;
                    tree[end].uid = update_count;
                    end -= 1;
                }
            }
        }
    }

    auto query(const usize x) -> T {
        // The parameters follow the problem statement's naming convention
        usize i = origin + x;
        Segment &result = tree[i];
        while (i > 0) {
            if (tree[i].uid > result.uid) {
                result = tree[i];
            }
            i = parent(i);
        }

        return result.uid > 0 ? source[x + result.offset] : dest[x];
    }
};

template <typename T>
auto process_queries(const u32 m, const std::vector<T> &a,
                     const std::vector<T> &b) -> void {

    CopySegmentTree stree(a, b);
    for (u32 i = 0; i < m; i += 1) {
        const auto t = read<u16>();
        if (t == 1) {
            const auto x = read<usize>() - 1, y = read<usize>() - 1,
                       k = read<usize>(); // 0-indexing
            stree.copy(x, y, k);
        } else if (t == 2) {
            const auto pos = read<usize>() - 1; // 0-indexing
            cout << stree.query(pos) << '\n';
        }
    }
}

auto main() -> int {
    std::ios::sync_with_stdio(false);

    const auto n = read<usize>();
    const auto m = read<u32>();
    const auto a = read_vector<i32>(n);
    const auto b = read_vector<i32>(n);
    process_queries(m, a, b);

    return 0;
}
