#include <catch2/catch_test_macros.hpp>
#include "modular_arithmetic.hpp"
using namespace hsc_snippets;

TEST_CASE("modular_arithmetic.hpp", )
{
    REQUIRE(modular_add(5, additive_inverse(5)) == 0);
}