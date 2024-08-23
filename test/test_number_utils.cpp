#include <catch2/catch_test_macros.hpp>
#include "number_utils.hpp"
#include <cstdint>
using namespace hsc_snippets;

TEST_CASE("number_utils.hpp",) {
    SECTION("numDigits") {
        REQUIRE(numDigits(0) == 0);
        REQUIRE(numDigits(10) == 2);
        REQUIRE(numDigits(99) == 2);
        REQUIRE(numDigits(12345) == 5);
        REQUIRE(numDigits(-412345) == 6);
    }
    SECTION("numBits") {
        REQUIRE(numBits(0) == 0);
        REQUIRE(numBits(1 << 8) == 9);
        REQUIRE(numBits((1 << 8) - 1) == 8);
        REQUIRE(numBits(static_cast<std::int32_t>(-12345)) == 32);
    }

    SECTION("SieveOfEratosthenes") {
        auto primes = SieveOfEratosthenes(100);
        auto expected_primes = std::vector<int>{
            2, 3, 5, 7, 11, 13, 17, 19, 23, 29,
            31, 37, 41, 43, 47, 53, 59, 61, 67, 71,
            73, 79, 83, 89, 97
        };
        REQUIRE(primes==expected_primes);
    }

    SECTION("isPerfectSquare") {
        REQUIRE(!isPerfectSquare(-12345));
        REQUIRE(isPerfectSquare(0));
        REQUIRE(!isPerfectSquare(10));
        REQUIRE(!isPerfectSquare(99));
        REQUIRE(isPerfectSquare(100));
        REQUIRE(!isPerfectSquare(101));
    }
}
