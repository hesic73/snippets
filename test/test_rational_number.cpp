#include <catch2/catch_test_macros.hpp>
#include "rational_number.hpp"
using namespace hsc_snippets;

TEST_CASE("rational_number.hpp", "[RationalNumber]") {
    SECTION("Test creation and basic properties") {
        RationalNumber r1 = RationalNumber::create(BigInteger::from_integer(3), BigInteger::from_integer(4));
        REQUIRE(r1.getNominator() == BigInteger::from_integer(3));
        REQUIRE(r1.getDenominator() == BigInteger::from_integer(4));

        RationalNumber r2 = RationalNumber::create(BigInteger::from_integer(5));
        REQUIRE(r2.getNominator() == BigInteger::from_integer(5));
        REQUIRE(r2.getDenominator() == BigInteger::from_integer(1));
    }

    SECTION("Test reduction and normalization") {
        RationalNumber r = RationalNumber::create(BigInteger::from_integer(6), BigInteger::from_integer(8));
        REQUIRE(r.getNominator() == BigInteger::from_integer(3));
        REQUIRE(r.getDenominator() == BigInteger::from_integer(4));

        RationalNumber r_neg = RationalNumber::create(BigInteger::from_integer(-6), BigInteger::from_integer(8));
        REQUIRE(r_neg.getNominator() == BigInteger::from_integer(-3));
        REQUIRE(r_neg.getDenominator() == BigInteger::from_integer(4));

        RationalNumber r_neg_den = RationalNumber::create(BigInteger::from_integer(6), BigInteger::from_integer(-8));
        REQUIRE(r_neg_den.getNominator() == BigInteger::from_integer(-3));
        REQUIRE(r_neg_den.getDenominator() == BigInteger::from_integer(4));
    }

    SECTION("Test arithmetic operations") {
        RationalNumber r1 = RationalNumber::create(BigInteger::from_integer(1), BigInteger::from_integer(2));
        RationalNumber r2 = RationalNumber::create(BigInteger::from_integer(1), BigInteger::from_integer(3));

        RationalNumber r_add = r1 + r2;
        REQUIRE(r_add.getNominator() == BigInteger::from_integer(5));
        REQUIRE(r_add.getDenominator() == BigInteger::from_integer(6));

        RationalNumber r_sub = r1 - r2;
        REQUIRE(r_sub.getNominator() == BigInteger::from_integer(1));
        REQUIRE(r_sub.getDenominator() == BigInteger::from_integer(6));

        RationalNumber r_mul = r1 * r2;
        REQUIRE(r_mul.getNominator() == BigInteger::from_integer(1));
        REQUIRE(r_mul.getDenominator() == BigInteger::from_integer(6));

        RationalNumber r_div = r1 / r2;
        REQUIRE(r_div.getNominator() == BigInteger::from_integer(3));
        REQUIRE(r_div.getDenominator() == BigInteger::from_integer(2));
    }

    SECTION("Test compound assignment operators") {
        RationalNumber r1 = RationalNumber::create(BigInteger::from_integer(1), BigInteger::from_integer(2));
        RationalNumber r2 = RationalNumber::create(BigInteger::from_integer(1), BigInteger::from_integer(3));

        r1 += r2;
        REQUIRE(r1.getNominator() == BigInteger::from_integer(5));
        REQUIRE(r1.getDenominator() == BigInteger::from_integer(6));

        r1 -= r2;
        REQUIRE(r1.getNominator() == BigInteger::from_integer(1));
        REQUIRE(r1.getDenominator() == BigInteger::from_integer(2));

        r1 *= r2;
        REQUIRE(r1.getNominator() == BigInteger::from_integer(1));
        REQUIRE(r1.getDenominator() == BigInteger::from_integer(6));

        r1 /= r2;
        r1 /= r2;
        REQUIRE(r1.getNominator() == BigInteger::from_integer(3));
        REQUIRE(r1.getDenominator() == BigInteger::from_integer(2));
    }

    SECTION("Test unary minus and negate") {
        RationalNumber r1 = RationalNumber::create(BigInteger::from_integer(3), BigInteger::from_integer(4));
        RationalNumber r_neg = -r1;
        REQUIRE(r_neg.getNominator() == BigInteger::from_integer(-3));
        REQUIRE(r_neg.getDenominator() == BigInteger::from_integer(4));

        RationalNumber r_negate = r1.negate();
        REQUIRE(r_negate.getNominator() == BigInteger::from_integer(-3));
        REQUIRE(r_negate.getDenominator() == BigInteger::from_integer(4));
    }

    SECTION("Test inverse and absolute value") {
        RationalNumber r1 = RationalNumber::create(BigInteger::from_integer(3), BigInteger::from_integer(4));
        RationalNumber r_inv = r1.inverse();
        REQUIRE(r_inv.getNominator() == BigInteger::from_integer(4));
        REQUIRE(r_inv.getDenominator() == BigInteger::from_integer(3));

        RationalNumber r_abs = RationalNumber::create(BigInteger::from_integer(-3), BigInteger::from_integer(4)).abs();
        REQUIRE(r_abs.getNominator() == BigInteger::from_integer(3));
        REQUIRE(r_abs.getDenominator() == BigInteger::from_integer(4));
    }

    SECTION("Test string representation") {
        RationalNumber r1 = RationalNumber::create(BigInteger::from_integer(3), BigInteger::from_integer(4));
        REQUIRE(r1.to_string() == "3/4");

        RationalNumber r_neg = RationalNumber::create(BigInteger::from_integer(-3), BigInteger::from_integer(4));
        REQUIRE(r_neg.to_string() == "-3/4");

        RationalNumber r_simple = RationalNumber::create(BigInteger::from_integer(2), BigInteger::from_integer(1));
        REQUIRE(r_simple.to_string() == "2/1");
    }

    SECTION("Test zero and one") {
        RationalNumber r_zero = RationalNumber::zero();
        REQUIRE(r_zero.getNominator() == BigInteger::zero());
        REQUIRE(r_zero.getDenominator() == BigInteger::one());

        RationalNumber r_one = RationalNumber::one();
        REQUIRE(r_one.getNominator() == BigInteger::one());
        REQUIRE(r_one.getDenominator() == BigInteger::one());
    }
}
