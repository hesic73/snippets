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

TEST_CASE("BigInteger::abs method", "[abs]") {
    SECTION("Absolute value of positive numbers") {
        for (int i = 0; i < 1000; ++i) {
            auto a = dist(rng);
            BigInteger bigA = BigInteger::from_integer(a < 0 ? -a : a); // Ensure a is positive
            REQUIRE(bigA.abs().to_string() == bigA.to_string());
        }
    }

    SECTION("Absolute value of negative numbers") {
        for (int i = 0; i < 1000; ++i) {
            auto a = dist(rng);
            BigInteger bigA = BigInteger::from_integer(a > 0 ? -a : a); // Ensure a is negative
            BigInteger bigAPositive = BigInteger::from_integer(a > 0 ? a : -a); // Corresponding positive value
            REQUIRE(bigA.abs() == bigAPositive);
        }
    }
}

TEST_CASE("BigInteger::max method", "[max]") {
    SECTION("Maximum of two BigIntegers") {
        for (int i = 0; i < 1000; ++i) {
            auto a = dist(rng);
            auto b = dist(rng);
            BigInteger bigA = BigInteger::from_integer(a);
            BigInteger bigB = BigInteger::from_integer(b);

            BigInteger expectedMax = a > b ? bigA : bigB; // Expected maximum based on integer comparison
            REQUIRE(BigInteger::max(bigA, bigB) == expectedMax);
        }
    }
}

TEST_CASE("BigInteger::min method", "[min]") {
    SECTION("Minimum of two BigIntegers") {
        for (int i = 0; i < 1000; ++i) {
            auto a = dist(rng);
            auto b = dist(rng);
            BigInteger bigA = BigInteger::from_integer(a);
            BigInteger bigB = BigInteger::from_integer(b);

            BigInteger expectedMin = a < b ? bigA : bigB; // Expected minimum based on integer comparison
            REQUIRE(BigInteger::min(bigA, bigB) == expectedMin);
        }
    }
}


TEST_CASE("BigInteger increment and decrement operators", "[BigInteger][Increment][Decrement]") {

    SECTION("Prefix increment") {
        for (int i = 0; i < 1000; ++i) {
            auto a = dist(rng);
            BigInteger bigA = BigInteger::from_integer(a);
            BigInteger &ref = ++bigA; // Prefix increment

            // bigA should be one more than its original value
            REQUIRE(bigA.to_string() == BigInteger::from_integer(a + 1).to_string());
            // Ref should be the same as bigA
            REQUIRE(&ref == &bigA);
        }
    }

    SECTION("Postfix increment") {
        for (int i = 0; i < 1000; ++i) {
            auto a = dist(rng);
            BigInteger bigA = BigInteger::from_integer(a);
            BigInteger prevValue = bigA++;

            // prevValue should be the original value of bigA
            REQUIRE(prevValue.to_string() == BigInteger::from_integer(a).to_string());
            // bigA should be one more than its original value
            REQUIRE(bigA.to_string() == BigInteger::from_integer(a + 1).to_string());
        }
    }

    SECTION("Prefix decrement") {
        for (int i = 0; i < 1000; ++i) {
            auto a = dist(rng);
            BigInteger bigA = BigInteger::from_integer(a);
            BigInteger &ref = --bigA; // Prefix decrement

            // bigA should be one less than its original value
            REQUIRE(bigA.to_string() == BigInteger::from_integer(a - 1).to_string());
            // Ref should be the same as bigA
            REQUIRE(&ref == &bigA);
        }
    }

    SECTION("Postfix decrement") {
        for (int i = 0; i < 1000; ++i) {
            auto a = dist(rng);
            BigInteger bigA = BigInteger::from_integer(a);
            BigInteger prevValue = bigA--;

            // prevValue should be the original value of bigA
            REQUIRE(prevValue.to_string() == BigInteger::from_integer(a).to_string());
            // bigA should be one less than its original value
            REQUIRE(bigA.to_string() == BigInteger::from_integer(a - 1).to_string());
        }
    }
}

TEST_CASE("BigInteger multiplication", "[BigInteger][Multiplication]") {
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(-100000, 100000); // Adjust range as needed for more intensive testing

    SECTION("Multiplying with zero") {
        BigInteger zero = BigInteger::from_integer(0);
        for (int i = 0; i < 10000; ++i) {
            BigInteger randomNum = BigInteger::from_integer(dist(rng));
            REQUIRE((zero * randomNum) == BigInteger::zero());
            REQUIRE((randomNum * zero) == BigInteger::zero());
        }
    }

    SECTION("Multiplying positive numbers") {
        for (int i = 0; i < 10000; ++i) {
            int a = std::abs(dist(rng));
            int b = std::abs(dist(rng));
            BigInteger bigA = BigInteger::from_integer(a);
            BigInteger bigB = BigInteger::from_integer(b);
            REQUIRE((bigA * bigB).to_string() == std::to_string(static_cast<long long>(a) * b));
        }
    }

    SECTION("Multiplying negative numbers") {
        for (int i = 0; i < 10000; ++i) {
            int a = dist(rng);
            int b = dist(rng);
            BigInteger bigA = BigInteger::from_integer(-std::abs(a));
            BigInteger bigB = BigInteger::from_integer(-std::abs(b));
            REQUIRE((bigA * bigB).to_string() == std::to_string(static_cast<long long>(std::abs(a)) * std::abs(b)));
        }
    }

    SECTION("Multiplying positive and negative numbers") {
        for (int i = 0; i < 10000; ++i) {
            int a = std::abs(dist(rng));
            int b = -std::abs(dist(rng));
            BigInteger bigA = BigInteger::from_integer(a);
            BigInteger bigB = BigInteger::from_integer(b);
            REQUIRE((bigA * bigB).to_string() == std::to_string(static_cast<long long>(a) * b));
            REQUIRE((bigB * bigA).to_string() == std::to_string(static_cast<long long>(b) * a));
        }
    }
}

TEST_CASE("BigInteger division", "[BigInteger][Division]") {
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(-100000, 100000); // Adjust range as needed for more intensive testing

    SECTION("Dividing by zero throws exception") {
        BigInteger randomNum = BigInteger::from_integer(dist(rng));
        REQUIRE_THROWS_AS(randomNum / BigInteger::zero(), std::runtime_error);
    }

    SECTION("Zero divided by any number") {
        BigInteger zero = BigInteger::zero();
        for (int i = 0; i < 10000; ++i) {
            int a;
            while ((a = dist(rng)) == 0);
            BigInteger bigA = BigInteger::from_integer(a);
            REQUIRE((zero / bigA) == BigInteger::zero());
        }
    }

    SECTION("Dividing positive numbers") {
        for (int i = 0; i < 10000; ++i) {
            int a = std::abs(dist(rng)) + 1; // Avoid zero to prevent division by zero
            int b = std::abs(dist(rng)) + 1;
            BigInteger bigA = BigInteger::from_integer(a);
            BigInteger bigB = BigInteger::from_integer(b);
            REQUIRE((bigA / bigB).to_string() == std::to_string(a / b));
        }
    }

    SECTION("Dividing negative numbers") {
        for (int i = 0; i < 10000; ++i) {
            int a = -std::abs(dist(rng)) - 1; // Avoid zero
            int b = -std::abs(dist(rng)) - 1;
            BigInteger bigA = BigInteger::from_integer(a);
            BigInteger bigB = BigInteger::from_integer(b);
            REQUIRE((bigA / bigB).to_string() == std::to_string(std::abs(a) / std::abs(b)));
        }
    }

    SECTION("Dividing positive and negative numbers") {
        for (int i = 0; i < 10000; ++i) {
            int a = std::abs(dist(rng)) + 1;
            int b = -std::abs(dist(rng)) - 1;
            BigInteger bigA = BigInteger::from_integer(a);
            BigInteger bigB = BigInteger::from_integer(b);
            REQUIRE((bigA / bigB).to_string() == std::to_string(a / b));
        }
    }
}


TEST_CASE("BigInteger modular operator", "[BigInteger][Modulo]") {
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(-100000, 100000);

    SECTION("Modulo with zero divisor throws exception") {
        BigInteger randomNum = BigInteger::from_integer(dist(rng));
        REQUIRE_THROWS_AS(randomNum % BigInteger::zero(), std::runtime_error);
    }

    SECTION("Zero modulo any number") {
        BigInteger zero = BigInteger::zero();
        for (int i = 0; i < 10000; ++i) {
            int a;
            while ((a = dist(rng)) == 0);
            BigInteger bigA = BigInteger::from_integer(a);
            REQUIRE((zero % bigA) == BigInteger::zero());
        }
    }

    SECTION("Positive numbers modulo operation") {
        for (int i = 0; i < 10000; ++i) {
            int a = std::abs(dist(rng));
            int b = std::abs(dist(rng)) + 1; // Ensure b is not zero
            BigInteger bigA = BigInteger::from_integer(a);
            BigInteger bigB = BigInteger::from_integer(b);
            REQUIRE((bigA % bigB).to_string() == std::to_string(a % b));
        }
    }

    SECTION("Negative numbers modulo operation") {
        for (int i = 0; i < 1000; ++i) {
            int a = -std::abs(dist(rng));
            int b = std::abs(dist(rng)) + 1; // Ensure b is not zero
            BigInteger bigA = BigInteger::from_integer(a);
            BigInteger bigB = BigInteger::from_integer(b);

            int expectedRemainder = a % b;

            REQUIRE((bigA % bigB).to_string() == std::to_string(expectedRemainder));
        }
    }

    SECTION("Mixed sign numbers modulo operation") {
        for (int i = 0; i < 1000; ++i) {
            int a = std::abs(dist(rng));
            int b = -std::abs(dist(rng)) - 1; // Ensure b is not zero
            BigInteger bigA = BigInteger::from_integer(a);
            BigInteger bigB = BigInteger::from_integer(b);

            int expectedRemainder = a % b;
            if (expectedRemainder < 0) {
                expectedRemainder += std::abs(b); // Adjust the expected remainder to have the same sign as the divisor
            }

            REQUIRE((bigA % bigB).to_string() == std::to_string(expectedRemainder));

            // Swapping signs
            BigInteger negA = BigInteger::from_integer(-a);
            BigInteger negB = BigInteger::from_integer(-b);
            expectedRemainder = -a % -b;

            REQUIRE((negA % negB).to_string() == std::to_string(expectedRemainder));
        }
    }
}

TEST_CASE("BigInteger divmod method", "[BigInteger][DivMod]") {
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(-100000, 100000);

    SECTION("divmod with zero divisor throws exception") {
        BigInteger randomNum = BigInteger::from_integer(dist(rng));
        REQUIRE_THROWS_AS(randomNum.divmod(BigInteger::zero()), std::runtime_error);
    }

    SECTION("Zero divmod any number") {
        BigInteger zero = BigInteger::zero();
        for (int i = 0; i < 1000; ++i) {
            int a;
            while ((a = dist(rng)) == 0);
            BigInteger bigA = BigInteger::from_integer(a);
            auto [quotient, remainder] = zero.divmod(bigA);
            REQUIRE(quotient == BigInteger::zero());
            REQUIRE(remainder == BigInteger::zero());
        }
    }

    SECTION("Divmod operation on positive numbers") {
        for (int i = 0; i < 1000; ++i) {
            int a = std::abs(dist(rng));
            int b = std::abs(dist(rng)) + 1; // Ensure b is not zero
            BigInteger bigA = BigInteger::from_integer(a);
            BigInteger bigB = BigInteger::from_integer(b);
            auto [quotient, remainder] = bigA.divmod(bigB);
            REQUIRE(quotient.to_string() == std::to_string(a / b));
            REQUIRE(remainder.to_string() == std::to_string(a % b));
        }
    }

    SECTION("Divmod operation with negative numbers") {
        for (int i = 0; i < 100; ++i) {
            int a = -std::abs(dist(rng)); // Ensure a is negative
            int b;
            while ((b = std::abs(dist(rng))) == 0); // Ensure b is positive and not zero

            BigInteger bigA = BigInteger::from_integer(a);
            BigInteger bigB = BigInteger::from_integer(b);
            auto [quotient, remainder] = bigA.divmod(bigB);

            int expectedQuotient = a / b;
            int expectedRemainder = a % b;


            REQUIRE(quotient.to_string() == std::to_string(expectedQuotient));
            REQUIRE(remainder.to_string() == std::to_string(expectedRemainder));
        }
    }


    SECTION("Divmod operation with mixed sign numbers") {
        for (int i = 0; i < 100; ++i) {
            int a = dist(rng);
            int b;
            while ((b = dist(rng)) == 0); // Ensure b is not zero
            BigInteger bigA = BigInteger::from_integer(a);
            BigInteger bigB = BigInteger::from_integer(b);
            auto [quotient, remainder] = bigA.divmod(bigB);

            int expectedQuotient = a / b;
            int expectedRemainder = a % b;


            REQUIRE(quotient.to_string() == std::to_string(expectedQuotient));
            REQUIRE(remainder.to_string() == std::to_string(expectedRemainder));
        }
    }
}


TEST_CASE("BigInteger += and -= operators", "[BigInteger][Operators]") {
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(-100000, 100000);

    SECTION("+= operator with positive and negative numbers") {
        for (int i = 0; i < 1000; ++i) {
            int a = dist(rng);
            int b = dist(rng);
            BigInteger bigA = BigInteger::from_integer(a);
            BigInteger bigB = BigInteger::from_integer(b);
            bigA += bigB;
            REQUIRE(bigA.to_string() == BigInteger::from_integer(a + b).to_string());
        }
    }

    SECTION("-= operator with positive and negative numbers") {
        for (int i = 0; i < 1000; ++i) {
            int a = dist(rng);
            int b = dist(rng);
            BigInteger bigA = BigInteger::from_integer(a);
            BigInteger bigB = BigInteger::from_integer(b);
            bigA -= bigB;
            REQUIRE(bigA.to_string() == BigInteger::from_integer(a - b).to_string());
        }
    }
}


TEST_CASE("BigInteger consistency between %, /, and divmod", "[BigInteger][Arithmetic]") {
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(-100000, 100000);

    SECTION("Consistency test for non-zero divisors") {
        for (int i = 0; i < 100; ++i) {
            int a_val = dist(rng);
            int b_val;
            while ((b_val = dist(rng)) == 0); // Ensure b is not zero

            BigInteger a = BigInteger::from_integer(a_val);
            BigInteger b = BigInteger::from_integer(b_val);

            BigInteger quotient = a / b;
            BigInteger remainder = a % b;
            auto [divmod_quotient, divmod_remainder] = a.divmod(b);

            // Check for consistency between / and divmod for the quotient
            REQUIRE(quotient == divmod_quotient);

            // Check for consistency between % and divmod for the remainder
            REQUIRE(remainder == divmod_remainder);

            // Verify the equation a = (a / b) * b + (a % b)
            BigInteger lhs = a;
            BigInteger rhs = quotient * b + remainder;
            REQUIRE(lhs == rhs);
        }
    }
}


TEST_CASE("BigInteger gcd and lcm", "[BigInteger][gcd][lcm]") {
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(-10000, 10000); // Adjust range as needed

    SECTION("gcd with various numbers") {
        for (
                int i = 0;
                i < 1000; ++i) {
            int a = dist(rng);
            int b = dist(rng);
            BigInteger bigA = BigInteger::from_integer(a);
            BigInteger bigB = BigInteger::from_integer(b);

// Compute gcd using BigInteger and std::integral implementations
            BigInteger bigGcd = BigInteger::gcd(bigA, bigB);
            int intGcd = std::gcd(std::abs(a), std::abs(b)); // std::gcd always returns a non-negative result

            REQUIRE(bigGcd.to_string() == std::to_string(intGcd));
        }
    }

    SECTION("lcm with various numbers") {
        for (
                int i = 0;
                i < 1000; ++i) {
            int a = dist(rng);
            int b = dist(rng);
            BigInteger bigA = BigInteger::from_integer(a);
            BigInteger bigB = BigInteger::from_integer(b);

// Avoid lcm computation for both a and b being zero as std::lcm(0, 0) is undefined pre C++20
            if (a == 0 && b == 0) {
                REQUIRE(BigInteger::lcm(bigA, bigB) == BigInteger::zero());
                continue;
            }

// Compute lcm using BigInteger and a manual implementation (std::lcm might not be available pre C++17 or when a, b are both 0)
            BigInteger bigLcm = BigInteger::lcm(bigA, bigB);
            int intLcm = (a == 0 || b == 0) ? 0 : std::abs(a * b) / std::gcd(std::abs(a), std::abs(b));

            REQUIRE(bigLcm.to_string() == std::to_string(intLcm));
        }
    }

    SECTION("gcd and lcm properties") {
        for (
                int i = 0;
                i < 1000; ++i) {
            int a = dist(rng);
            int b = dist(rng);
            BigInteger bigA = BigInteger::from_integer(a);
            BigInteger bigB = BigInteger::from_integer(b);

            BigInteger bigGcd = BigInteger::gcd(bigA, bigB);
            BigInteger bigLcm = BigInteger::lcm(bigA, bigB);

// Test gcd(a, b) * lcm(a, b) == |a * b|
            BigInteger product = bigGcd * bigLcm;
            BigInteger absProduct = (bigA * bigB).abs();
            REQUIRE(product == absProduct);
        }
    }
}