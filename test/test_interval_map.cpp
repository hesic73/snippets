#include <catch2/catch_test_macros.hpp>
#include "interval_map.hpp"
using namespace hsc_snippets;

TEST_CASE("interval_map.hpp", )
{
    auto interval_map = IntervalMap<int, int, Maximum<int>>{};
    auto buildings = std::vector<std::vector<int>>{{2, 9, 10}, {3, 7, 15}, {5, 12, 12}, {15, 20, 10}, {19, 24, 8}};
    for (auto &&building : buildings)
    {
        interval_map.update(building[0], building[1], building[2]);
    }

    interval_map.defragment();
    auto intervals = interval_map.getIntervals();

    auto expected_intervals = std::vector<std::tuple<int, int, int>>{
        {2, 3, 10},
        {3, 7, 15},
        {7, 12, 12},
        {15, 20, 10},
        {20, 24, 8},
    };
    REQUIRE(intervals == expected_intervals);
}
