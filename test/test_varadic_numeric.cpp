#include <catch2/catch_test_macros.hpp>
#include "varadic_numeric.hpp"
using namespace hsc_snippets;

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
