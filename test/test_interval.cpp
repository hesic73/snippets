#include <catch2/catch_test_macros.hpp>
#include "interval.hpp"
#include "string_utils.hpp"
#include <iostream>

using namespace hsc_snippets;

TEST_CASE("interval_map", "[basic]") {
    SECTION("Basic") {
        auto interval_map = IntervalMap<int, int, Maximum<int> >{};
        auto buildings = std::vector<std::vector<int> >{
            {2, 9, 10},
            {3, 7, 15},
            {5, 12, 12},
            {15, 20, 10},
            {19, 24, 8}
        };
        for (auto &&building: buildings) {
            interval_map.update(building[0], building[1], building[2]);
        }

        interval_map.defragment();
        auto intervals = interval_map.getIntervals();

        auto expected_intervals = std::vector<std::tuple<int, int, int> >{
            {2, 3, 10},
            {3, 7, 15},
            {7, 12, 12},
            {15, 20, 10},
            {20, 24, 8},
        };
        REQUIRE(intervals == expected_intervals);
    }

    SECTION("Completely overlapping intervals") {
        IntervalMap<int, int> interval_map;
        interval_map.update(5, 15, 10);
        interval_map.update(0, 20, 5);
        interval_map.defragment();
        auto intervals = interval_map.getIntervals();
        std::vector<std::tuple<int, int, int> > expected_intervals{{0, 20, 5}};
        REQUIRE(intervals == expected_intervals);
    }

    SECTION("Subset intervals") {
        IntervalMap<int, int, Override<int> > interval_map;
        interval_map.update(0, 10, 1);
        interval_map.update(3, 7, 2);
        interval_map.defragment();
        auto intervals = interval_map.getIntervals();
        std::vector<std::tuple<int, int, int> > expected_intervals{
            {0, 3, 1},
            {3, 7, 2},
            {7, 10, 1}
        };
        REQUIRE(intervals == expected_intervals);
    }

    SECTION("Overlapping intervals with different values") {
        IntervalMap<int, int, Override<int> > interval_map;
        interval_map.update(0, 5, 1);
        interval_map.update(2, 7, 2);
        interval_map.defragment();
        auto intervals = interval_map.getIntervals();
        std::vector<std::tuple<int, int, int> > expected_intervals{
            {0, 2, 1},
            {2, 7, 2}
        };
        REQUIRE(intervals == expected_intervals);
    }
}

TEST_CASE("Intervals with shared boundaries in IntervalMap", "[edge_cases]") {
    IntervalMap<int, int, Override<int> > interval_map;
    interval_map.update(0, 5, 1);
    interval_map.update(5, 10, 2);
    interval_map.defragment();
    auto intervals = interval_map.getIntervals();
    std::vector<std::tuple<int, int, int> > expected_intervals{
        {0, 5, 1},
        {5, 10, 2}
    };
    REQUIRE(intervals == expected_intervals);
}

TEST_CASE("Interval completely overlapping existing intervals in IntervalMap", "[edge_cases]") {
    IntervalMap<int, int, Override<int> > interval_map;
    interval_map.update(10, 20, 3);
    interval_map.update(5, 25, 5);
    interval_map.defragment();
    auto intervals = interval_map.getIntervals();
    std::vector<std::tuple<int, int, int> > expected_intervals{
        {5, 25, 5}
    };
    REQUIRE(intervals == expected_intervals);
}


TEST_CASE("Multiple overlapping intervals with different update policies", "[edge_cases]") {
    // Using Maximum update policy
    IntervalMap<int, int, Maximum<int> > interval_map_max;
    interval_map_max.update(0, 5, 1);
    interval_map_max.update(3, 7, 2);
    interval_map_max.defragment();
    auto intervals_max = interval_map_max.getIntervals();
    std::vector<std::tuple<int, int, int> > expected_intervals_max{
        {0, 3, 1},
        {3, 7, 2}
    };
    REQUIRE(intervals_max == expected_intervals_max);

    // Using Override update policy
    IntervalMap<int, int, Override<int> > interval_map_override;
    interval_map_override.update(0, 5, 1);
    interval_map_override.update(3, 7, 2);
    interval_map_override.defragment();
    auto intervals_override = interval_map_override.getIntervals();
    std::vector<std::tuple<int, int, int> > expected_intervals_override{
        {0, 3, 1},
        {3, 7, 2}
    };
    REQUIRE(intervals_override == expected_intervals_override);
}


TEST_CASE("interval_set", "[basic]") {
    SECTION("Overlapping at boundaries") {
        IntervalSet<int> interval_set;
        interval_set.update(1, 5);
        interval_set.update(5, 10);
        interval_set.defragment();
        auto intervals = interval_set.getIntervals();
        std::vector<std::pair<int, int> > expected_intervals{{1, 10}};
        REQUIRE(intervals == expected_intervals);
    }

    SECTION("Negative intervals") {
        IntervalSet<int> interval_set;
        interval_set.update(-10, -5);
        interval_set.update(-7, -3);
        interval_set.defragment();
        auto intervals = interval_set.getIntervals();
        std::vector<std::pair<int, int> > expected_intervals{{-10, -3}};
        REQUIRE(intervals == expected_intervals);
    }

    SECTION("Merging multiple overlapping intervals") {
        IntervalSet<int> interval_set;
        interval_set.update(1, 4);
        interval_set.update(3, 6);
        interval_set.update(5, 8);
        interval_set.defragment();
        auto intervals = interval_set.getIntervals();
        std::vector<std::pair<int, int> > expected_intervals{{1, 8}};
        REQUIRE(intervals == expected_intervals);
    }
}


TEST_CASE("Intervals with gaps in IntervalSet", "[edge_cases]") {
    IntervalSet<int> interval_set;
    interval_set.update(1, 2);
    interval_set.update(3, 4);
    interval_set.update(5, 6);
    interval_set.defragment();
    auto intervals = interval_set.getIntervals();
    std::vector<std::pair<int, int> > expected_intervals{
        {1, 2},
        {3, 4},
        {5, 6}
    };
    REQUIRE(intervals == expected_intervals);
}


TEST_CASE("Merging adjacent intervals in IntervalSet", "[edge_cases]") {
    IntervalSet<int> interval_set;
    interval_set.update(1, 2);
    interval_set.update(2, 3);
    interval_set.update(3, 4);
    interval_set.defragment();
    auto intervals = interval_set.getIntervals();
    std::vector<std::pair<int, int> > expected_intervals{
        {1, 4}
    };
    REQUIRE(intervals == expected_intervals);
}

TEST_CASE("IntervalSet query with Interval<T>", "[interval_query]") {
    IntervalSet<int> interval_set;
    interval_set.update(1, 5);
    interval_set.update(10, 15);
    interval_set.update(20, 25);

    // Intervals to test
    Interval<int> interval1{0, 2}; // Overlaps with [1, 5)
    Interval<int> interval2{4, 12}; // Overlaps with [1, 5) and [10, 15)
    Interval<int> interval3{13, 22}; // Overlaps with [10, 15) and [20, 25)
    Interval<int> interval4{23, 30}; // Overlaps with [20, 25)
    Interval<int> interval5{5, 10}; // Does not overlap
    Interval<int> interval6{15, 20}; // Does not overlap
    Interval<int> interval7{25, 30}; // Does not overlap

    // Test intervals that should intersect
    REQUIRE(interval_set.query(interval1)); // Should be true
    REQUIRE(interval_set.query(interval2)); // Should be true
    REQUIRE(interval_set.query(interval3)); // Should be true
    REQUIRE(interval_set.query(interval4)); // Should be true

    // Test intervals that should not intersect
    REQUIRE(!interval_set.query(interval5)); // Should be false
    REQUIRE(!interval_set.query(interval6)); // Should be false
    REQUIRE(!interval_set.query(interval7)); // Should be false
}
