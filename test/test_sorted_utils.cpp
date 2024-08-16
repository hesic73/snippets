#include <catch2/catch_test_macros.hpp>
#include <random>
#include "sorted_utils.hpp"

using namespace hsc_snippets;

TEST_CASE("deferred_binary_search tests", "[deferred_binary_search]") {
    SECTION("Simple ascending function") {
        auto simple_asc = [](int i) { return i; };
        REQUIRE(deferred_binary_search(0, 5, 3, simple_asc).value() == 3);
        REQUIRE(!deferred_binary_search(0, 5, 10, simple_asc).has_value());
    }

    SECTION("Power function") {
        auto power_two = [](int i) { return i * i; }; // x^2 is non-decreasing for non-negative x
        REQUIRE(deferred_binary_search(0, 100, 49, power_two).value() == 7);
        REQUIRE(!deferred_binary_search(0, 100, 50, power_two).has_value());
    }
}

TEST_CASE("deferred_upper_bound and deferred_lower_bound tests", "[bounds]") {
    auto func = [](int i) { return i * 2; }; // Even numbers from 0 to 10, clearly non-decreasing

    SECTION("deferred_upper_bound") {
        REQUIRE(deferred_upper_bound(0, 5, 6, func) == 4);
        REQUIRE(deferred_upper_bound(0, 5, 11, func) == 6);
        REQUIRE(deferred_upper_bound(0, 5, -1, func) == 0);
    }

    SECTION("deferred_lower_bound") {
        REQUIRE(deferred_lower_bound(0, 5, 6, func) == 3);
        REQUIRE(deferred_lower_bound(0, 5, 0, func) == 0);
        REQUIRE(deferred_lower_bound(0, 5, 11, func) == 6);
    }
}

TEST_CASE("Complex cases with different functions", "[complex]") {
    auto parabolic_function = [](int i) { return i * i - 10 * i + 25; }; // x^2 - 10x + 25 is non-decreasing on [5, 10]

    SECTION("deferred_binary_search on parabolic function") {
        REQUIRE(deferred_binary_search(5, 10, 0, parabolic_function).value() ==
            5); // Minimum at x=5, search starts at 5
        REQUIRE(!deferred_binary_search(5, 10, -1, parabolic_function).has_value());
    }

    SECTION("deferred_upper_bound with function producing duplicates") {
        auto duplicates = [](int i) {
            return (i / 2) * 2;
        }; // Non-decreasing as it produces constant or increasing pairs
        REQUIRE(deferred_upper_bound(0, 10, 6, duplicates) == 8);
    }

    // Removing invalid test for negative_values as it was incorrect
}


TEST_CASE("Randomized test for deferred_upper_bound and deferred_lower_bound", "[bounds]") {
    std::mt19937 rng(123); // Fixed seed for reproducibility

    for (int t = 0; t < 100; ++t) {
        std::vector<int> v(1000);
        std::generate(v.begin(), v.end(), rng);
        std::sort(v.begin(), v.end());

        int target = std::uniform_int_distribution<int>(v.front(), v.back())(rng);

        auto lambda_func = [&v](int index) -> int { return v[index]; };

        SECTION("deferred_upper_bound") {
            auto expected = std::upper_bound(v.begin(), v.end(), target) - v.begin();
            auto result = deferred_upper_bound(0, static_cast<int>(v.size()) - 1, target, lambda_func,
                                               std::less<int>{});
            REQUIRE(result == expected);
        }

        SECTION("deferred_lower_bound") {
            auto expected = std::lower_bound(v.begin(), v.end(), target) - v.begin();
            auto result = deferred_lower_bound(0, static_cast<int>(v.size()) - 1, target, lambda_func,
                                               std::less<int>{});
            REQUIRE(result == expected);
        }
    }
}

TEST_CASE("Simple test for create_compression_mapper", "[simple]") {
    // Test case with distinct elements
    std::vector<int> nums = {10, 20, 15, 10, 30};
    auto get_compressed_index = create_compression_mapper(nums);

    REQUIRE(get_compressed_index(10) == 0);
    REQUIRE(get_compressed_index(15) == 1);
    REQUIRE(get_compressed_index(20) == 2);
    REQUIRE(get_compressed_index(30) == 3);

    // Test case with all identical elements
    std::vector<int> identical_nums = {5, 5, 5, 5};
    auto get_compressed_index_identical = create_compression_mapper(identical_nums);

    REQUIRE(get_compressed_index_identical(5) == 0);

    // Test case with negative and positive elements
    std::vector<int> mixed_nums = {-10, 0, 10, -10, 20};
    auto get_compressed_index_mixed = create_compression_mapper(mixed_nums);

    REQUIRE(get_compressed_index_mixed(-10) == 0);
    REQUIRE(get_compressed_index_mixed(0) == 1);
    REQUIRE(get_compressed_index_mixed(10) == 2);
    REQUIRE(get_compressed_index_mixed(20) == 3);

    // Test case with already sorted elements
    std::vector<int> sorted_nums = {1, 2, 3, 4, 5};
    auto get_compressed_index_sorted = create_compression_mapper(sorted_nums);

    REQUIRE(get_compressed_index_sorted(1) == 0);
    REQUIRE(get_compressed_index_sorted(2) == 1);
    REQUIRE(get_compressed_index_sorted(3) == 2);
    REQUIRE(get_compressed_index_sorted(4) == 3);
    REQUIRE(get_compressed_index_sorted(5) == 4);

    // Test case with a single element
    std::vector<int> single_num = {42};
    auto get_compressed_index_single = create_compression_mapper(single_num);

    REQUIRE(get_compressed_index_single(42) == 0);
}
