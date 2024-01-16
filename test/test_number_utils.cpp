#include <catch2/catch_test_macros.hpp>
#include "number_utils.hpp"
#include <cstdint>
using namespace hsc_snippets;

TEST_CASE("number_utils.hpp", )
{
    SECTION("numDigits")
    {
        REQUIRE(numDigits(0) == 0);
        REQUIRE(numDigits(10) == 2);
        REQUIRE(numDigits(99) == 2);
        REQUIRE(numDigits(12345) == 5);
        REQUIRE(numDigits(-412345) == 6);
    }
    SECTION("numBits")
    {
        REQUIRE(numBits(0) == 0);
        REQUIRE(numBits(1 << 8) == 9);
        REQUIRE(numBits((1 << 8) - 1) == 8);
        REQUIRE(numBits(static_cast<std::int32_t>(-12345)) == 32);
    }
}
