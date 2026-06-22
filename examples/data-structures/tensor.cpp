#include <cassert>
#include <cstdint>
#include <vector>

using i64 = std::int64_t;

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