// Name:
// Problem:
// Submission:
// Verdict:

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

template <typename T>
inline auto read_vector(usize n) -> std::vector<T> {
    std::vector<T> v(n);
    for (auto &&x : v) {
        x = read<T>();
    }
    return v;
}

auto main() -> int {
    // std::ios::sync_with_stdio(false);

    return 0;
}
