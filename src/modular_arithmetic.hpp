#ifndef MODULAR_ARITHMETIC_H
#define MODULAR_ARITHMETIC_H

#include <cstdint>
#include <array>

static constexpr int MODULO = static_cast<int>(1e9 + 7);

constexpr int modular_add(int x, int y)
{
    auto a = static_cast<std::int64_t>(x);
    auto b = static_cast<std::int64_t>(y);
    auto c = (a + b) % MODULO;
    return static_cast<int>(c);
}

constexpr int additive_inverse(int x)
{
    x = x % MODULO; // x might be negative
    x = (x + MODULO) % MODULO;
    return MODULO - x;
}

constexpr int modular_substract(int x, int y)
{
    auto a = static_cast<std::int64_t>(x);
    auto b = static_cast<std::int64_t>(y);
    auto c = (a - b);
    c = c % MODULO;
    c = (c + MODULO) % MODULO;
    return static_cast<int>(c);
}

constexpr int modular_multiply(int x, int y)
{
    auto a = static_cast<std::int64_t>(x);
    auto b = static_cast<std::int64_t>(y);
    auto c = (a * b) % MODULO;
    return static_cast<int>(c);
}

constexpr int modular_square(int x)
{
    auto a = static_cast<int64_t>(x);
    auto b = (a * a) % MODULO;
    return static_cast<int>(b);
}

constexpr int modular_cube(int x)
{
    auto a = static_cast<int64_t>(x);
    auto b = (a * a) % MODULO;
    auto c = (b * a) % MODULO;
    return static_cast<int>(c);
}

// Base 2 exponentiation % MODULO
int modular_pow2(size_t exponent)
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
    auto tmp = static_cast<std::int64_t>(modular_pow2(half_e));
    auto m = (exponent & 1);
    return ((tmp * tmp) << m) % MODULO;
}

#endif