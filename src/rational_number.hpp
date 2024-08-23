#ifndef RATIONAL_NUMBER_H
#define RATIONAL_NUMBER_H

#include "big_integer.hpp"
#include <stdexcept>
#include <utility>
#include <string>

namespace hsc_snippets {
    class RationalNumber {
    private:
        BigInteger nominator;
        BigInteger denominator;

        // Private Constructor
        RationalNumber(BigInteger nominator, BigInteger denominator)
            : nominator(std::move(nominator)), denominator(std::move(denominator)) {
            if (this->denominator == BigInteger::zero()) {
                throw std::invalid_argument("Denominator cannot be zero.");
            }
            // Ensure denominator is positive
            if (this->denominator < BigInteger::zero()) {
                this->nominator = -this->nominator;
                this->denominator = -this->denominator;
            }
            reduce();
        }

        void reduce() {
            BigInteger gcd_value = BigInteger::gcd(nominator, denominator);
            nominator /= gcd_value;
            denominator /= gcd_value;
            // Ensure denominator is positive
            if (denominator < BigInteger::zero()) {
                nominator = -nominator;
                denominator = -denominator;
            }
        }

    public:
        /**
         * Creates a RationalNumber with the given numerator and denominator.
         *
         * @param nominator The numerator of the rational number.
         * @param denominator The denominator of the rational number. Must not be zero.
         * @return A RationalNumber representing nominator/denominator.
         * @throws std::invalid_argument if the denominator is zero.
         */
        static RationalNumber create(BigInteger nominator, BigInteger denominator) {
            return {std::move(nominator), std::move(denominator)};
        }

        /**
         * Creates a RationalNumber with the given numerator and a denominator of 1.
         *
         * @param nominator The numerator of the rational number.
         * @return A RationalNumber representing nominator/1.
         */
        static RationalNumber create(BigInteger nominator) {
            return {std::move(nominator), BigInteger::one()};
        }

        /**
         * Returns a reference to a static RationalNumber representing 0/1.
         *
         * @return A reference to a RationalNumber with a value of zero.
         */
        static const RationalNumber &zero() {
            static RationalNumber zeroInstance = {BigInteger::zero(), BigInteger::one()};
            return zeroInstance;
        }

        /**
         * Returns a reference to a static RationalNumber representing 1/1.
         *
         * @return A reference to a RationalNumber with a value of one.
         */
        static const RationalNumber &one() {
            static RationalNumber oneInstance = {BigInteger::one(), BigInteger::one()};
            return oneInstance;
        }

        // Copy constructor
        RationalNumber(const RationalNumber &other) = default;

        // Move constructor
        RationalNumber(RationalNumber &&other) noexcept = default;

        // Copy assignment
        RationalNumber &operator=(const RationalNumber &other) = default;

        // Move assignment
        RationalNumber &operator=(RationalNumber &&other) noexcept = default;

        // Arithmetic operators
        RationalNumber operator+(const RationalNumber &other) const {
            BigInteger n = nominator * other.denominator + other.nominator * denominator;
            BigInteger d = denominator * other.denominator;
            return {n, d};
        }

        RationalNumber operator-(const RationalNumber &other) const {
            BigInteger n = nominator * other.denominator - other.nominator * denominator;
            BigInteger d = denominator * other.denominator;
            return {n, d};
        }

        RationalNumber operator*(const RationalNumber &other) const {
            BigInteger n = nominator * other.nominator;
            BigInteger d = denominator * other.denominator;
            return {n, d};
        }

        RationalNumber operator/(const RationalNumber &other) const {
            if (other.nominator == BigInteger::zero()) {
                throw std::invalid_argument("Division by zero.");
            }
            BigInteger n = nominator * other.denominator;
            BigInteger d = denominator * other.nominator;
            return {n, d};
        }

        // Compound assignment operators
        RationalNumber &operator+=(const RationalNumber &other) {
            *this = *this + other;
            return *this;
        }

        RationalNumber &operator-=(const RationalNumber &other) {
            *this = *this - other;
            return *this;
        }

        RationalNumber &operator*=(const RationalNumber &other) {
            *this = *this * other;
            return *this;
        }

        RationalNumber &operator/=(const RationalNumber &other) {
            *this = *this / other;
            return *this;
        }

        // Unary minus operator
        RationalNumber operator-() const {
            return {-nominator, denominator};
        }

        /**
         * 
         * @return
         */
        [[nodiscard]] RationalNumber inverse() const {
            if (nominator == BigInteger::zero()) {
                throw std::invalid_argument("Cannot invert a zero rational number.");
            }
            return {denominator, nominator};
        }

        // Negation function
        [[nodiscard]] RationalNumber negate() const {
            return {-nominator, denominator};
        }

        // Absolute value function
        [[nodiscard]] RationalNumber abs() const {
            return {nominator.abs(), denominator.abs()};
        }

        // Convert to string representation
        [[nodiscard]] std::string to_string() const {
            return nominator.to_string() + "/" + denominator.to_string();
        }

        // Comparison operators
        bool operator==(const RationalNumber &other) const {
            return nominator == other.nominator && denominator == other.denominator;
        }

        bool operator!=(const RationalNumber &other) const {
            return !(*this == other);
        }

        bool operator<(const RationalNumber &other) const {
            return nominator * other.denominator < other.nominator * denominator;
        }

        bool operator<=(const RationalNumber &other) const {
            return nominator * other.denominator <= other.nominator * denominator;
        }

        bool operator>(const RationalNumber &other) const {
            return nominator * other.denominator > other.nominator * denominator;
        }

        bool operator>=(const RationalNumber &other) const {
            return nominator * other.denominator >= other.nominator * denominator;
        }

        // Getter functions
        [[nodiscard]] const BigInteger &getNominator() const {
            return nominator;
        }

        [[nodiscard]] const BigInteger &getDenominator() const {
            return denominator;
        }
    };
}

#endif // RATIONAL_NUMBER_H
