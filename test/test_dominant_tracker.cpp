#include <catch2/catch_test_macros.hpp>
#include "dominant_tracker.hpp"
#include <vector>
using namespace hsc_snippets;

TEST_CASE("dominant_tracker.hpp", )
{
    auto nums = std::vector<int>{1, 2, 2, 2};
    auto result = std::vector<std::optional<int>>{};
    auto tracker = DominantTracker();
    for (auto num : nums)
    {
        tracker.add(num);
        result.push_back(tracker.getDominant());
    }
    auto expected_result = std::vector<std::optional<int>>{1, std::nullopt, 2, 2};
    REQUIRE(result == expected_result);
}
