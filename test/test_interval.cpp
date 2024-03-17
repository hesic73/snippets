#include <catch2/catch_test_macros.hpp>
#include "interval.hpp"
#include "string_utils.hpp"
#include <iostream>

using namespace hsc_snippets;

TEST_CASE("interval_map", "[basic]")
{
    auto interval_map = IntervalMap<int, int, Maximum<int>>{};
    auto buildings = std::vector<std::vector<int>>{{2,  9,  10},
                                                   {3,  7,  15},
                                                   {5,  12, 12},
                                                   {15, 20, 10},
                                                   {19, 24, 8}};
    for (auto &&building: buildings) {
        interval_map.update(building[0], building[1], building[2]);
    }

    interval_map.defragment();
    auto intervals = interval_map.getIntervals();

    auto expected_intervals = std::vector<std::tuple<int, int, int>>{
            {2,  3,  10},
            {3,  7,  15},
            {7,  12, 12},
            {15, 20, 10},
            {20, 24, 8},
    };
    REQUIRE(intervals == expected_intervals);
}


TEST_CASE("interval_set", "[basic]")
{
    auto interval_set = IntervalSet<int>{};
    auto intervals = std::vector<std::vector<int>>{{1, 3},
                                                   {6, 9}};
    for (auto &&interval: intervals) {
        interval_set.update(interval[0], interval[1]);
    }

    interval_set.update(2, 5);

    interval_set.defragment();
    auto new_intervals = interval_set.getIntervals();

    auto expected_intervals = std::vector<std::pair<int, int>>{
            {1, 5},
            {6, 9},
    };
    REQUIRE(new_intervals == expected_intervals);
}
