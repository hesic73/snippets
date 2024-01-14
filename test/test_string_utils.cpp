#include <catch2/catch_test_macros.hpp>
#include "string_utils.hpp"
#include <vector>
using namespace hsc_snippets;

TEST_CASE("string_utils.hpp", )
{
    auto txt = std::string{"abcabcabcaabbbcaaabc"};
    auto pat = std::string{"abc"};
    auto indices = kmpSearch(pat, txt);
    auto expected = std::vector<int>{0, 3, 6, 17};
    REQUIRE(indices == expected);
}
