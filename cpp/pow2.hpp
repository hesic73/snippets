#ifndef POW2_H
#define POW2_H

#include <cstdint>
#include <array>

static constexpr int MODULO = static_cast<int>(1e9 + 7);

// Base 2 exponentiation % MODULO
int pow2(size_t exponent)
{
    constexpr size_t N = 25;
    constexpr auto lookup{[]() constexpr
                       {
                           std::array<int, N> a{};
                           a[0] = 1;
                           for (size_t i = 1; i < N; i++)
                           {
                               a[i] = a[i - 1] << 1;
                           }
                           return a;
                       }()};
    if (exponent <= N)
    {
        return lookup[exponent] % MODULO;
    }
    auto half_e = exponent >> 1;
    auto tmp = static_cast<std::int64_t>(pow2(half_e));
    auto m = (exponent & 1);
    return ((tmp * tmp) << m) % MODULO;
}

#endif