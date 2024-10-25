#include <catch2/catch_test_macros.hpp>
#include "string_utils.hpp"
#include <vector>
#include <string>
#include <random>


using namespace hsc_snippets;

TEST_CASE("kmpSearch function", "[string_utils][kmpSearch]") {
    std::string txt = "abcabcabcaabbbcaaabc";
    std::string pat = "abc";
    auto indices = kmpSearch(pat, txt);
    std::vector<int> expected = {0, 3, 6, 17};
    REQUIRE(indices == expected);
}

TEST_CASE("to_string(vector<int>) function", "[string_utils][to_string]") {
    std::vector<int> v = {1, 2, 3, 4, 5};
    std::string s = to_string(v);
    std::string expected = "[1, 2, 3, 4, 5]";
    REQUIRE(s == expected);
}

TEST_CASE("to_string(vector<std::string>) function", "[string_utils][to_string]") {
    std::vector<std::string> v = {"a", "b", "c", "d", "e"};
    std::string s = to_string(v);
    std::string expected = "[a, b, c, d, e]";
    REQUIRE(s == expected);
}

TEST_CASE("to_string(vector<vector<int>>) function", "[string_utils][to_string]") {
    std::vector<std::vector<int> > v = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    std::string s = to_string(v);
    std::string expected = "[[1, 2, 3], [4, 5, 6], [7, 8, 9]]";
    REQUIRE(s == expected);
}

TEST_CASE("string_split function", "[string_utils][string_split]") {
    std::string s = "a,b,c,d,e";
    char delimiter = ',';
    auto result = string_split(s, delimiter);
    std::vector<std::string> expected = {"a", "b", "c", "d", "e"};
    REQUIRE(result == expected);
}

TEST_CASE("string_repeat function", "[string_utils][string_repeat]") {
    SECTION("Edge cases") {
        std::string s = "abc";
        size_t n = 3;
        std::string result = string_repeat(s, n);
        std::string expected = "abcabcabc";
        REQUIRE(result == expected);
        REQUIRE(string_repeat(s, 0).empty()); // Empty result when n is 0
        REQUIRE(string_repeat(s, 1) == s); // Original string when n is 1
        REQUIRE(string_repeat("", 5).empty()); // Empty result when s is empty
        REQUIRE(string_repeat("", 0).empty()); // Empty result when both s and n are empty
        REQUIRE(string_repeat("a", 1) == "a"); // Single character repeated once
    }

    SECTION("Random tests") {
        std::mt19937 rng(std::random_device{}());
        std::uniform_int_distribution<size_t> dist_len(0, 100); // Length of the string `s`
        std::uniform_int_distribution<size_t> dist_n(0, 1000); // Number of repetitions `n`

        for (int i = 0; i < 100; ++i) {
            // Run 100 random tests
            size_t len = dist_len(rng);
            size_t n = dist_n(rng);

            // Generate a random string of length `len`
            std::string s(len, ' ');
            std::generate_n(s.begin(), len, [&]() {
                return static_cast<char>('a' + (rng() % 26)); // Random lowercase letter
            });

            // Generate expected output
            std::string expected(len * n, ' ');
            for (size_t j = 0; j < n; ++j) {
                std::copy(s.begin(), s.end(), expected.begin() + j * len);
            }

            // Compare with the result from string_repeat
            std::string result = string_repeat(s, n);
            REQUIRE(result == expected);
        }
    }
}

TEST_CASE("string_repeat(char, size_t) function", "[string_utils][string_repeat]") {
    SECTION("Edge cases") {
        char c = 'x';
        size_t n = 5;
        std::string result = string_repeat(c, n);
        std::string expected = "xxxxx";
        REQUIRE(result == expected);
        REQUIRE(string_repeat(c, 0).empty()); // Empty result when n is 0
        REQUIRE(string_repeat(c, 1) == "x"); // Single character repeated once
        REQUIRE(string_repeat('y', 3) == "yyy"); // Different character repeated multiple times
        REQUIRE(string_repeat('z', 0).empty()); // Empty result when n is 0, different character
    }

    SECTION("Random tests") {
        std::mt19937 rng(std::random_device{}());
        std::uniform_int_distribution<size_t> dist_n(0, 1000); // Number of repetitions `n`
        std::uniform_int_distribution<int> dist_char('a', 'z'); // Random lowercase letter

        for (int i = 0; i < 100; ++i) {
            // Run 100 random tests
            char random_char = static_cast<char>(dist_char(rng));
            size_t n = dist_n(rng);

            // Generate expected output
            std::string expected(n, random_char);

            // Compare with the result from string_repeat
            std::string result = string_repeat(random_char, n);
            REQUIRE(result == expected);
        }
    }
}


TEST_CASE("string_join function", "[string_utils][string_join]") {
    SECTION("Basic functionality with non-empty strings") {
        std::vector<std::string> strings = {"a", "b", "c", "d", "e"};
        std::string delimiter = ",";
        std::string result = string_join(strings, delimiter);
        std::string expected = "a,b,c,d,e";
        REQUIRE(result == expected);
    }

    SECTION("Empty vector") {
        std::vector<std::string> strings;
        std::string delimiter = ",";
        std::string result = string_join(strings, delimiter);
        REQUIRE(result.empty()); // Joining an empty vector should return an empty string
    }

    SECTION("Single element vector") {
        std::vector<std::string> strings = {"a"};
        std::string delimiter = ",";
        std::string result = string_join(strings, delimiter);
        REQUIRE(result == "a"); // No delimiter is added when there’s only one element
    }

    SECTION("Custom delimiter") {
        std::vector<std::string> strings = {"apple", "banana", "cherry"};
        std::string delimiter = " | ";
        std::string result = string_join(strings, delimiter);
        std::string expected = "apple | banana | cherry";
        REQUIRE(result == expected);
    }

    SECTION("Delimiter with empty strings") {
        std::vector<std::string> strings = {"", "", ""};
        std::string delimiter = "-";
        std::string result = string_join(strings, delimiter);
        std::string expected = "--"; // Empty strings joined by delimiter
        REQUIRE(result == expected);
    }

    SECTION("Random tests") {
        std::mt19937 rng(std::random_device{}());
        std::uniform_int_distribution<size_t> dist_len(0, 100); // Length of strings
        std::uniform_int_distribution<size_t> dist_count(0, 20); // Number of strings in vector
        std::uniform_int_distribution<char> dist_char('a', 'z'); // Random characters

        for (int i = 0; i < 100; ++i) {
            // Run 100 random tests
            size_t count = dist_count(rng);
            std::vector<std::string> strings(count);

            for (size_t j = 0; j < count; ++j) {
                size_t len = dist_len(rng);
                strings[j].resize(len);
                std::generate(strings[j].begin(), strings[j].end(), [&]() { return dist_char(rng); });
            }

            std::string delimiter = ",";
            std::string expected = strings.empty() ? "" : strings[0]; // Handle the first string separately
            for (size_t k = 1; k < strings.size(); ++k) {
                expected += delimiter + strings[k]; // Add delimiter before subsequent strings
            }

            std::string result = string_join(strings, delimiter);
            REQUIRE(result == expected);
        }
    }
}
