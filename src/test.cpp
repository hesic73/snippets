#include <catch2/catch_test_macros.hpp>
#include "num_digits.hpp"
#include "varadic_numeric.hpp"
#include "modular_arithmetic.hpp"
#include "num_of_greater_elements.hpp"
#include <iostream>
#include <format>
#include <vector>
using namespace hsc_snippets;

TEST_CASE("modular_arithmetic.hpp", )
{
    for (int i = 0; i < 100; i++)
    {
        REQUIRE(modular_add(i, additive_inverse(i)) == 0);
    }
}

TEST_CASE("num_digits.hpp", )
{
    REQUIRE(numDigits(0) == 0);
    REQUIRE(numDigits(10) == 2);
    REQUIRE(numDigits(99) == 2);
    REQUIRE(numDigits(12345) == 5);
    REQUIRE(numDigits(-412345) == 6);
}

TEST_CASE("varadic_numeric.hpp", )
{
    REQUIRE(lessThanAll(1, 2, 3, 5));
    REQUIRE(!lessThanAll(1, -2, 3, 5));

    REQUIRE(lessThanOrEqualToAll(1, 1, 3, 5));
    REQUIRE(!lessThanOrEqualToAll(2, 1, 3, 5));

    REQUIRE(greaterThanAll(6, 1, 3, 5));
    REQUIRE(!greaterThanAll(5, 1, 3, 5));

    REQUIRE(greaterThanOrEqualToAll(5, 1, 3, 5));
    REQUIRE(!greaterThanOrEqualToAll(2, 1, 3, 5));

    REQUIRE(sum(10, 10, 305, 205) == 530);
}

TEST_CASE("num_of_greater_elements.hpp", )
{
    auto v = std::vector<int>{1, 2, 3, 4, 5};
    REQUIRE(numOfGreaterElements(v, 2) == 3);
    REQUIRE(numOfGreaterElements(v, 5) == 0);
}
