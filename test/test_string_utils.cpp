#include <catch2/catch_test_macros.hpp>
#include "string_utils.hpp"
#include <vector>

using namespace hsc_snippets;

TEST_CASE("string_utils.hpp",)
{
    SECTION("kmpSearch")
    {
        auto txt = std::string{"abcabcabcaabbbcaaabc"};
        auto pat = std::string{"abc"};
        auto indices = kmpSearch(pat, txt);
        auto expected = std::vector<int>{0, 3, 6, 17};
        REQUIRE(indices == expected);
    }SECTION("to_string(vector<int>)")
    {
        auto v = std::vector<int>{1, 2, 3, 4, 5};
        auto s = to_string(v);
        auto expected = std::string{"[1, 2, 3, 4, 5]"};
        REQUIRE(s == expected);
    }SECTION("to_string(vector<string>)")
    {
        auto v = std::vector<std::string>{"a", "b", "c", "d", "e"};
        auto s = to_string(v);
        auto expected = std::string{"[a, b, c, d, e]"};
        REQUIRE(s == expected);
    }SECTION("to_string(vector<vector<int>>)")
    {
        auto v = std::vector<std::vector<int>>{{1, 2, 3},
                                               {4, 5, 6},
                                               {7, 8, 9}};
        auto s = to_string(v);
        auto expected = std::string{"[[1, 2, 3], [4, 5, 6], [7, 8, 9]]"};
        REQUIRE(s == expected);
    }


    SECTION("split") {
        auto s = std::string{"a,b,c,d,e"};
        auto delimiter = ',';
        auto result = split(s, delimiter);
        auto expected = std::vector<std::string>{"a", "b", "c", "d", "e"};
        REQUIRE(result == expected);
    }
}
