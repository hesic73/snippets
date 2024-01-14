#include <catch2/catch_test_macros.hpp>
#include "bounds.hpp"
using namespace hsc_snippets;

TEST_CASE("bounds.hpp", )
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
