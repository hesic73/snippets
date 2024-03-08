#include <catch2/catch_test_macros.hpp>
#include "big_integer.hpp"
#include <random>
#include <iostream>

using namespace hsc_snippets;

TEST_CASE("BigInteger::parse method", "[parse]") {
    SECTION("Parsing positive numbers") {
        REQUIRE(BigInteger::parse("1234567890").to_string() == "1234567890");
        REQUIRE(BigInteger::parse("0").to_string() == "0");
    }

    SECTION("Parsing negative numbers") {
        REQUIRE(BigInteger::parse("-1234567890").to_string() == "-1234567890");
    }

    SECTION("Parsing numbers with leading zeros") {
        REQUIRE(BigInteger::parse("00001234").to_string() == "1234");
        REQUIRE(BigInteger::parse("-00001234").to_string() == "-1234");
    }

    SECTION("Parsing invalid strings throws std::invalid_argument") {
        REQUIRE_THROWS_AS(BigInteger::parse("abc123"), std::invalid_argument);
        REQUIRE_THROWS_AS(BigInteger::parse("123abc"), std::invalid_argument);
        REQUIRE_THROWS_AS(BigInteger::parse("-123abc"), std::invalid_argument);
    }
}

TEST_CASE("BigInteger::from_integer method", "[from_integer]") {
    SECTION("Creating BigInteger from positive integers") {
        REQUIRE(BigInteger::from_integer(1234567890).to_string() == "1234567890");
        REQUIRE(BigInteger::from_integer(0).to_string() == "0");
    }

    SECTION("Creating BigInteger from negative integers") {
        REQUIRE(BigInteger::from_integer(-1234567890).to_string() == "-1234567890");
    }

    SECTION("Creating BigInteger from large integers") {
        REQUIRE(BigInteger::from_integer(9223372036854775807LL).to_string() == "9223372036854775807"); // Max int64_t
        REQUIRE(BigInteger::from_integer(-9223372036854775807LL - 1).to_string() ==
                "-9223372036854775808"); // Min int64_t
    }
}

TEST_CASE("BigInteger::to_string method", "[to_string]") {
    SECTION("Converting BigInteger to string") {
        BigInteger num1 = BigInteger::parse("1234567890");
        BigInteger num2 = BigInteger::from_integer(-987654321);

        REQUIRE(num1.to_string() == "1234567890");
        REQUIRE(num2.to_string() == "-987654321");
    }
}

std::mt19937 rng(std::random_device{}()); // Random number generator
std::uniform_int_distribution<std::int64_t> dist(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());

TEST_CASE("BigInteger comparison operators", "[BigInteger][Comparison]") {
    SECTION("Testing == operator with random integers") {
        for (int i = 0; i < 100; ++i) {
            auto a = dist(rng);
            BigInteger bigA = BigInteger::from_integer(a);

            // Comparing same numbers should always be true
            REQUIRE(bigA == BigInteger::from_integer(a));
        }
    }

    SECTION("Testing != operator with random integers") {
        for (int i = 0; i < 100; ++i) {
            auto a = dist(rng);
            auto b = dist(rng);
            // Ensure a and b are different for the test
            while (a == b) {
                b = dist(rng);
            }

            BigInteger bigA = BigInteger::from_integer(a);
            BigInteger bigB = BigInteger::from_integer(b);

            REQUIRE(bigA != bigB);
        }
    }

    SECTION("Testing < operator with random integers") {
        for (int i = 0; i < 100; ++i) {
            auto a = dist(rng);
            auto b = dist(rng);
            BigInteger bigA = BigInteger::from_integer(a);
            BigInteger bigB = BigInteger::from_integer(b);

            REQUIRE((a < b) == (bigA < bigB));
        }
    }

    SECTION("Testing <= operator with random integers") {
        for (int i = 0; i < 100; ++i) {
            auto a = dist(rng);
            auto b = dist(rng);
            BigInteger bigA = BigInteger::from_integer(a);
            BigInteger bigB = BigInteger::from_integer(b);

            REQUIRE((a <= b) == (bigA <= bigB));
        }
    }

    SECTION("Testing > operator with random integers") {
        for (int i = 0; i < 100; ++i) {
            auto a = dist(rng);
            auto b = dist(rng);
            BigInteger bigA = BigInteger::from_integer(a);
            BigInteger bigB = BigInteger::from_integer(b);

            REQUIRE((a > b) == (bigA > bigB));
        }
    }

    SECTION("Testing >= operator with random integers") {
        for (int i = 0; i < 100; ++i) {
            auto a = dist(rng);
            auto b = dist(rng);
            BigInteger bigA = BigInteger::from_integer(a);
            BigInteger bigB = BigInteger::from_integer(b);

            REQUIRE((a >= b) == (bigA >= bigB));
        }
    }
}

TEST_CASE("BigInteger addition", "[BigInteger][Addition]") {
    SECTION("Adding positive numbers") {
        REQUIRE(BigInteger::from_integer(123) + BigInteger::from_integer(456) == BigInteger::from_integer(579));
        REQUIRE(BigInteger::from_integer(0) + BigInteger::from_integer(123) == BigInteger::from_integer(123));
    }

    SECTION("Adding negative numbers") {
        REQUIRE(BigInteger::from_integer(-123) + BigInteger::from_integer(-456) == BigInteger::from_integer(-579));
    }

    SECTION("Adding positive and negative numbers") {
        REQUIRE(BigInteger::from_integer(123) + BigInteger::from_integer(-456) == BigInteger::from_integer(-333));
        REQUIRE(BigInteger::from_integer(-123) + BigInteger::from_integer(456) == BigInteger::from_integer(333));
    }

    SECTION("Adding with zero") {
        REQUIRE(BigInteger::from_integer(0) + BigInteger::from_integer(0) == BigInteger::from_integer(0));
        REQUIRE(BigInteger::from_integer(-123) + BigInteger::from_integer(0) == BigInteger::from_integer(-123));
        REQUIRE(BigInteger::from_integer(0) + BigInteger::from_integer(123) == BigInteger::from_integer(123));
    }
}

TEST_CASE("BigInteger subtraction", "[BigInteger][Subtraction]") {
    SECTION("Subtracting positive numbers") {
        REQUIRE(BigInteger::from_integer(456) - BigInteger::from_integer(123) == BigInteger::from_integer(333));
        REQUIRE(BigInteger::from_integer(123) - BigInteger::from_integer(123) == BigInteger::from_integer(0));
    }

    SECTION("Subtracting negative numbers") {
        REQUIRE(BigInteger::from_integer(-456) - BigInteger::from_integer(-123) == BigInteger::from_integer(-333));
    }

    SECTION("Subtracting positive and negative numbers") {
        REQUIRE(BigInteger::from_integer(123) - BigInteger::from_integer(-456) == BigInteger::from_integer(579));
        REQUIRE(BigInteger::from_integer(-123) - BigInteger::from_integer(456) == BigInteger::from_integer(-579));
    }

    SECTION("Subtracting with zero") {
        REQUIRE(BigInteger::from_integer(0) - BigInteger::from_integer(0) == BigInteger::from_integer(0));
        REQUIRE(BigInteger::from_integer(-123) - BigInteger::from_integer(0) == BigInteger::from_integer(-123));
        REQUIRE(BigInteger::from_integer(0) - BigInteger::from_integer(123) == BigInteger::from_integer(-123));
    }
}

TEST_CASE("BigInteger getMinValueInstance and getMaxValueInstance", "[BigInteger][Min][Max]") {
    SECTION("Testing getMinValueInstance") {
        REQUIRE(BigInteger::getMinValueInstance<int>().to_string() == std::to_string(std::numeric_limits<int>::min()));
        REQUIRE(BigInteger::getMinValueInstance<short>().to_string() ==
                std::to_string(std::numeric_limits<short>::min()));
        REQUIRE(BigInteger::getMinValueInstance<long>().to_string() ==
                std::to_string(std::numeric_limits<long>::min()));

        // Since unsigned types have a min value of 0, we can directly compare to BigInteger::zero()
        REQUIRE(BigInteger::getMinValueInstance<unsigned int>() == BigInteger::zero());
        REQUIRE(BigInteger::getMinValueInstance<unsigned short>() == BigInteger::zero());
        REQUIRE(BigInteger::getMinValueInstance<unsigned long>() == BigInteger::zero());
    }

    SECTION("Testing getMaxValueInstance") {
        REQUIRE(BigInteger::getMaxValueInstance<int>().to_string() == std::to_string(std::numeric_limits<int>::max()));
        REQUIRE(BigInteger::getMaxValueInstance<short>().to_string() ==
                std::to_string(std::numeric_limits<short>::max()));
        REQUIRE(BigInteger::getMaxValueInstance<long>().to_string() ==
                std::to_string(std::numeric_limits<long>::max()));

        REQUIRE(BigInteger::getMaxValueInstance<unsigned int>().to_string() ==
                std::to_string(std::numeric_limits<unsigned int>::max()));
        REQUIRE(BigInteger::getMaxValueInstance<unsigned short>().to_string() ==
                std::to_string(std::numeric_limits<unsigned short>::max()));
        REQUIRE(BigInteger::getMaxValueInstance<unsigned long>().to_string() ==
                std::to_string(std::numeric_limits<unsigned long>::max()));
    }
}


bool safeToAdd(int a, int b) {
    // Check for overflow
    if (a > 0 && b > std::numeric_limits<int>::max() - a) return false;
    // Check for underflow
    if (a < 0 && b < std::numeric_limits<int>::min() - a) return false;
    return true;
}

bool safeToSubtract(int a, int b) {
    // Check for overflow
    if (b < 0 && a > std::numeric_limits<int>::max() + b) return false;
    // Check for underflow
    if (b > 0 && a < std::numeric_limits<int>::min() + b) return false;
    return true;
}

TEST_CASE("BigInteger random addition and subtraction", "[BigInteger][Random][Addition][Subtraction]") {
    SECTION("Random addition") {
        for (int i = 0; i < 1000; ++i) { // Perform 100 random tests
            int a = dist(rng);
            int b = dist(rng);
            if (!safeToAdd(a, b)) {
                continue;
            }

            int result = a + b;

            BigInteger bigA = BigInteger::from_integer(a);
            BigInteger bigB = BigInteger::from_integer(b);
            BigInteger bigResult = bigA + bigB;

            // Convert the standard integer result to BigInteger for comparison
            BigInteger bigResultFromInt = BigInteger::from_integer(result);
            REQUIRE(bigResult == bigResultFromInt);
        }
    }

    SECTION("Random subtraction") {
        for (int i = 0; i < 1000; ++i) { // Perform 100 random tests
            int a = dist(rng);
            int b = dist(rng);
            if (!safeToSubtract(a, b)) {
                continue;
            }
            int result = a - b;

            BigInteger bigA = BigInteger::from_integer(a);
            BigInteger bigB = BigInteger::from_integer(b);
            BigInteger bigResult = bigA - bigB;

            // Convert the standard integer result to BigInteger for comparison
            BigInteger bigResultFromInt = BigInteger::from_integer(result);

            REQUIRE(bigResult == bigResultFromInt);
        }
    }
}

TEST_CASE("BigInteger to<T>() conversion", "[BigInteger][Conversion]") {
    SECTION("Successful conversions") {
        BigInteger bigPos = BigInteger::parse("12345");
        auto posResult = bigPos.to<int>();
        REQUIRE(posResult.has_value());
        REQUIRE(posResult.value() == 12345);

        BigInteger bigNeg = BigInteger::parse("-12345");
        auto negResult = bigNeg.to<int>();
        REQUIRE(negResult.has_value());
        REQUIRE(negResult.value() == -12345);

        BigInteger bigZero = BigInteger::parse("0");
        auto zeroResult = bigZero.to<int>();
        REQUIRE(zeroResult.has_value());
        REQUIRE(zeroResult.value() == 0);
    }

    SECTION("Conversions expected to fail") {
        // Assuming int is 32-bit, this value is too large to fit
        BigInteger bigTooLarge = BigInteger::parse("10000000000");
        auto tooLargeResult = bigTooLarge.to<int>();
        REQUIRE(!tooLargeResult.has_value());

        // A negative value cannot be represented by an unsigned type
        BigInteger bigNeg = BigInteger::parse("-1");
        auto negToUnsignedResult = bigNeg.to<unsigned int>();
        REQUIRE(!negToUnsignedResult.has_value());
    }

    // Additional tests can include edge cases and conversions to other integral types
}


TEST_CASE("BigInteger to<T>() conversion with random long long", "[BigInteger][Conversion]") {
    // Random number generator setup
    std::random_device rd;
    std::mt19937_64 gen(rd()); // Use mt19937_64 for generating 64-bit numbers
    std::uniform_int_distribution<std::int64_t> distPositiveInt(0,
                                                                std::numeric_limits<int>::max()); // Positive int range
    std::uniform_int_distribution<std::int64_t> distLongLong(std::numeric_limits<int>::max() + 1LL,
                                                             std::numeric_limits<std::int64_t>::max()); // Beyond int range


    SECTION("Conversion within positive int range") {
        for (int i = 0; i < 1000; ++i) {
            std::int64_t randomPositiveInt = distPositiveInt(gen);
            BigInteger bigInt = BigInteger::from_integer(randomPositiveInt);

            // Test conversion to int
            auto convertedToInt = bigInt.to<int>();
            REQUIRE(convertedToInt.has_value());
            REQUIRE(convertedToInt.value() == static_cast<int>(randomPositiveInt));

            // Test conversion to unsigned int
            auto convertedToUnsignedInt = bigInt.to<unsigned int>();
            REQUIRE(convertedToUnsignedInt.has_value());
            REQUIRE(convertedToUnsignedInt.value() == static_cast<unsigned int>(randomPositiveInt));
        }
    }

    SECTION("Conversion outside int range") {
        for (int i = 0; i < 1000; ++i) {
            std::int64_t randomLongLong = distLongLong(gen);
            BigInteger bigInt = BigInteger::from_integer(randomLongLong);

            // Test conversion to int (should fail due to overflow)
            auto convertedToInt = bigInt.to<int>();
            REQUIRE(!convertedToInt.has_value());

            // Test conversion to unsigned int (should succeed only if within unsigned int range)
            auto convertedToUnsignedInt = bigInt.to<unsigned int>();
            if (randomLongLong <= static_cast<std::int64_t>(std::numeric_limits<unsigned int>::max())) {
                REQUIRE(convertedToUnsignedInt.has_value());
                REQUIRE(convertedToUnsignedInt.value() == static_cast<unsigned int>(randomLongLong));
            } else {
                REQUIRE(!convertedToUnsignedInt.has_value());
            }
        }
    }
}