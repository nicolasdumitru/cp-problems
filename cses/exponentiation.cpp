// Problem: https://cses.fi/problemset/task/1095/
// Submission: https://cses.fi/problemset/result/10929649/
// Verdict: ACCEPTED

#include <cstddef>
#include <cstdint>
#include <iostream>

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
    T value;
    std::cin >> value;
    return value;
}

template <typename T>
inline auto is_odd(const T n) -> bool {
    return (n & 1) == static_cast<T>(1);
}

const u64 MOD = 1'000'000'000 + 7;
auto fast_exp_mod(const u32 base, const u32 exponent,
                  const u64 mod = MOD) -> u32 {
    u64 res = 1;
    u64 b = base;
    u64 e = exponent;
    while (e > 0) {
        res = res * (is_odd(e) ? b : 1) % mod;
        b = b * b % mod;
        e /= 2;
    }

    return static_cast<u32>(res);
}

int main() {
    for (auto n = read<u32>(); n > 0; n -= 1) {
        auto base = read<u32>(), exp = read<u32>();
        cout << fast_exp_mod(base, exp) << '\n';
    }

    return 0;
}
