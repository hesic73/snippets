#include <catch2/catch_test_macros.hpp>
#include "monotonic_stack.hpp"
using namespace hsc_snippets;
#include <vector>
#include <numeric>
#include <iostream>

TEST_CASE("monotonic_stack.hpp", )
{
    SECTION("basic")
    {
        auto le = [](int a, int b)
        {
            return a <= b;
        };
        MonotonicDecreasingStack<int> decreasingStack;
        REQUIRE(decreasingStack.push(5) == std::nullopt);
        REQUIRE(decreasingStack.push(4) == 5);
        REQUIRE(decreasingStack.push(3) == 4);
        REQUIRE(decreasingStack.push(2) == 3);
        REQUIRE(decreasingStack.push(1) == 2);
    }
    SECTION("nextGreaterElement")
    {
        std::vector<int> nums = {3, 4, 2, 1, 2};
        auto result = nextGreaterElement<int>(nums, []()
                                              { return std::numeric_limits<int>::min(); });
        auto expected_result = std::vector<int>{std::numeric_limits<int>::min(), std::numeric_limits<int>::min(), 4, 2, 4};
        REQUIRE(result == expected_result);
    }
}