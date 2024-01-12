#include <catch2/catch_test_macros.hpp>
#include "num_digits.hpp"
using namespace hsc_snippets;


TEST_CASE("num_digits.hpp", )
{
    REQUIRE(numDigits(0) == 0);
    REQUIRE(numDigits(10) == 2);
    REQUIRE(numDigits(99) == 2);
    REQUIRE(numDigits(12345) == 5);
    REQUIRE(numDigits(-412345) == 6);
}
