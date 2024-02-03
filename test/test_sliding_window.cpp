#include <catch2/catch_test_macros.hpp>
#include "sliding_window.hpp"
#include <vector>
using namespace hsc_snippets;

TEST_CASE("sliding_window.hpp", )
{
    auto sw = SlidingWindowMax<int>(3);
    auto arr = std::vector<int>{12, 1, 78, 90, 57, 89, 56};
    auto result = std::vector<int>{};
    auto expected_result = std::vector<int>{12, 12, 78, 90, 90, 90, 89};
    for (auto num : arr)
    {
        sw.update(num);
        result.push_back(sw.get_max().value());
    }
    REQUIRE(result == expected_result);
}
