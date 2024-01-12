#include <catch2/catch_test_macros.hpp>
#include "num_of_greater_elements.hpp"
using namespace hsc_snippets;

TEST_CASE("num_of_greater_elements.hpp", )
{
    auto v = std::vector<int>{1, 2, 3, 4, 5};
    REQUIRE(numOfGreaterElements(v, 2) == 3);
    REQUIRE(numOfGreaterElements(v, 5) == 0);
}
