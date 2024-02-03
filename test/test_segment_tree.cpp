#include <catch2/catch_test_macros.hpp>
#include "segment_tree.hpp"
using namespace hsc_snippets;
#include <vector>
#include <numeric>
#include <iostream>

TEST_CASE("segment_tree.hpp", )
{
    auto a = std::vector<int>{10, 11, 12, 13, 14, 15, 16, 17, 18};
    auto segmentTree = SegmentTree<int>(a);
    for (int i = 0; i < a.size(); i++)
    {
        REQUIRE(segmentTree.range_sum(i, i) == a[i]);
    }
    REQUIRE(segmentTree.range_sum(0, 4) == 60);
    segmentTree.range_set(5, 5, 12345);
    REQUIRE(segmentTree.range_sum(5, 5) == 12345);
    segmentTree.range_add(0, 6, 666);
    REQUIRE(segmentTree.range_sum(0, 0) == 676);
    REQUIRE(segmentTree.range_sum(0, 4) == 60 + 666 * 5);
}