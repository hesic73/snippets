#include <catch2/catch_test_macros.hpp>
#include "prefix_suffix.hpp"
#include <vector>

using namespace hsc_snippets;

TEST_CASE("prefix_suffix.hpp", "[prefix_suffix]") {

    SECTION("getPrefixMax") {
        std::vector<int> v = {1, 3, 2, 5, 4};
        std::vector<int> expected = {1, 3, 3, 5, 5};
        REQUIRE(getPrefixMax(v) == expected);
    }

    SECTION("getSuffixMax") {
        std::vector<int> v = {1, 3, 2, 5, 4};
        std::vector<int> expected = {5, 5, 5, 5, 4};
        REQUIRE(getSuffixMax(v) == expected);
    }

    SECTION("getPrefixMin") {
        std::vector<int> v = {5, 3, 2, 4, 1};
        std::vector<int> expected = {5, 3, 2, 2, 1};
        REQUIRE(getPrefixMin(v) == expected);
    }

    SECTION("getSuffixMin") {
        std::vector<int> v = {5, 3, 2, 4, 1};
        std::vector<int> expected = {1, 1, 1, 1, 1};
        REQUIRE(getSuffixMin(v) == expected);
    }

    SECTION("getPrefixSum") {
        std::vector<int> v = {1, 2, 3, 4, 5};
        std::vector<int> expected = {1, 3, 6, 10, 15};
        REQUIRE(getPrefixSum(v) == expected);
    }

    SECTION("getSuffixSum") {
        std::vector<int> v = {1, 2, 3, 4, 5};
        std::vector<int> expected = {15, 14, 12, 9, 5};
        REQUIRE(getSuffixSum(v) == expected);
    }

    SECTION("Edge case - empty vector") {
        std::vector<int> v = {};
        REQUIRE(getPrefixMax(v).empty());
        REQUIRE(getSuffixMax(v).empty());
        REQUIRE(getPrefixMin(v).empty());
        REQUIRE(getSuffixMin(v).empty());
        REQUIRE(getPrefixSum(v).empty());
        REQUIRE(getSuffixSum(v).empty());
    }

    SECTION("Edge case - single element vector") {
        std::vector<int> v = {7};
        REQUIRE(getPrefixMax(v) == std::vector<int>{7});
        REQUIRE(getSuffixMax(v) == std::vector<int>{7});
        REQUIRE(getPrefixMin(v) == std::vector<int>{7});
        REQUIRE(getSuffixMin(v) == std::vector<int>{7});
        REQUIRE(getPrefixSum(v) == std::vector<int>{7});
        REQUIRE(getSuffixSum(v) == std::vector<int>{7});
    }

    SECTION("Test with negative numbers") {
        std::vector<int> v = {-1, -3, -2, -5, -4};
        REQUIRE(getPrefixMax(v) == std::vector<int>{-1, -1, -1, -1, -1});
        REQUIRE(getSuffixMax(v) == std::vector<int>{-1, -2, -2, -4, -4});
        REQUIRE(getPrefixMin(v) == std::vector<int>{-1, -3, -3, -5, -5});
        REQUIRE(getSuffixMin(v) == std::vector<int>{-5, -5, -5, -5, -4});
        REQUIRE(getPrefixSum(v) == std::vector<int>{-1, -4, -6, -11, -15});
        REQUIRE(getSuffixSum(v) == std::vector<int>{-15, -14, -11, -9, -4});
    }
}
