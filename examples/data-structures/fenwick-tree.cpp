#include <cstddef>
#include <vector>

using usize = std::size_t;
using isize = std::ptrdiff_t;

template <typename T>
class FenwickTree {
    std::vector<T> bit;

    // Returns the index where node i's range begins. Every node i stores the
    // result of the query operation on the range [node_begin(i), i].
    inline auto range_begin(const usize node) const -> usize {
        return node & (node + 1);
    }
    // Returns the index of node i's parent node.
    inline auto parent(const usize node) const -> usize {
        return node | (node + 1);
    }

public:
    FenwickTree(const usize size) : bit(size, 0) {}
    FenwickTree(const std::vector<T> v) : bit(v.size(), 0) {
        for (usize i = 0; i < bit.size(); i += 1) {
            bit[i] += v[i];
            if (parent(i) < bit.size()) bit[parent(i)] += bit[i];
        }
    }

    auto point_add(const usize index, const T delta) -> void {
        for (usize i = index; i < bit.size(); i = parent(i)) {
            bit[i] += delta;
        }
    }

    auto point_set(const usize index, const T val) -> void {
        // For even index values, bit[index] stores the exact value of the
        // element at index.
        // Proof:
        // bit[index] = sum [range_begin(index), index].
        // For all natural numbers k, range_begin(2k) == 2k, therefore
        // bit[2k] = sum [2k, 2k] = v[2k].
        const T node_val = (index & 1) == 0 ? bit[index] : range_sum(index, index + 1);
        point_add(index, val - node_val);
    }

    // [0, index]
    auto prefix_sum(const usize index) const -> T {
        T sum = 0;
        for (usize i = index + 1; i > 0; i = range_begin(i)) {
            i -= 1;
            sum += bit[i];
        }
        return sum;
    }

    // [begin, end)
    auto range_sum(const usize begin, const usize end) const -> T {
        return prefix_sum(end - 1) - (begin > 0 ? prefix_sum(begin - 1) : 0);
    }
};
