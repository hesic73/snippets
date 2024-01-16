#include <catch2/catch_test_macros.hpp>
#include "sorted_utils.hpp"
using namespace hsc_snippets;

TEST_CASE("sorted_utils.hpp[std]", )
{
    auto v = std::vector<int>{1, 2, 3, 4, 5};
    SECTION("numOfGreaterElements")
    {
        REQUIRE(numOfGreaterElements(v, 2) == 3);
        REQUIRE(numOfGreaterElements(v, 5) == 0);
    }

    SECTION("containsInRange")
    {
        REQUIRE(containsInRange(v, 1, 2));
        REQUIRE(containsInRange(v, 4, 5));
        REQUIRE(containsInRange(v, 5, 7));
        REQUIRE(!containsInRange(v, -1, 1));
        REQUIRE(!containsInRange(v, -1, 0));
    }
}

TEST_CASE("custom functions", )
{
    SECTION("binary_search")
    {
        REQUIRE(binary_search(0, 5, 3, [](int i)
                              { return i; })
                    .value() == 3);

        REQUIRE(!binary_search(0, 5, 3, [](int i)
                               { return i << 1; })
                     .has_value());
    }

    SECTION("greatest_index")
    {
        REQUIRE(greatest_index(0, 5, 3, [](int i)
                               { return i; }) == 3);
        REQUIRE(greatest_index(0, 5, 3, [](int i)
                               { return 10 + i; }) == -1);
        REQUIRE(greatest_index(0, 5, 3, [](int i)
                               { return -10 + i; }) == 5);
    }
}
