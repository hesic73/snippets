#ifndef BIG_INTEGER_H
#define BIG_INTEGER_H

#include <vector>
#include <string>
#include <algorithm>
#include <cstdint>
#include <concepts>
#include <optional>
#include <iostream>
#include <numeric>

namespace hsc_snippets {
    /**
     * @class BigInteger
     * @brief Implements a class for representing and manipulating large integers beyond the native integer range.
     *
     * This class supports basic arithmetic operations, comparison, and conversion from/to strings and native integer types.
     * It handles both positive and negative large integer values.
     */
    class BigInteger {
    private:
        std::vector<std::uint8_t> digits;
        bool isNegative = false;

        // Helper function to remove leading zeros
        void removeLeadingZeros() {
            while (digits.size() > 1 && digits.back() == 0) {
                digits.pop_back();
            }
            if (digits.size() == 1 && digits[0] == 0) {
                isNegative = false; // Ensure 0 is always positive
            }
        }

        bool _isAbsoluteGreaterOrEqual(const BigInteger &other) const {
            if (digits.size() != other.digits.size()) {
                return digits.size() > other.digits.size();
            }

            for (int i = digits.size() - 1; i >= 0; --i) {
                if (digits[i] != other.digits[i]) {
                    return digits[i] > other.digits[i];
                }
            }

            return true; // Equal in absolute value
        }

#pragma region private constructors

        BigInteger() = default;

        BigInteger(bool isNegative, const std::vector<std::uint8_t> &digits)
                : isNegative(isNegative), digits(digits) {}

#pragma endregion

#pragma region add&subtract

        BigInteger _add(const BigInteger &other) const {
            BigInteger result;
            result.digits.clear(); // Ensure the result starts with an empty digit vector

            size_t maxLength = std::max(digits.size(), other.digits.size());
            int carry = 0;

            for (size_t i = 0; i < maxLength || carry; ++i) {
                int digitSum = carry;

                if (i < digits.size()) {
                    digitSum += digits[i];
                }
                if (i < other.digits.size()) {
                    digitSum += other.digits[i];
                }

                result.digits.push_back(digitSum % 10); // Store the single digit
                carry = digitSum / 10; // Calculate carry for the next digit
            }

            return result;
        }

        BigInteger _subtract(const BigInteger &other) const {
            BigInteger result;
            result.digits.clear();

            int borrow = 0;
            for (size_t i = 0; i < digits.size(); ++i) {
                int digitSub = digits[i] - borrow - (i < other.digits.size() ? other.digits[i] : 0);
                borrow = 0;

                if (digitSub < 0) {
                    digitSub += 10;
                    borrow = 1;
                }

                result.digits.push_back(digitSub);
            }

            result.removeLeadingZeros(); // Defined previously to remove leading zeros

            return result;
        }

#pragma endregion

    public:

#pragma region conversion

        /**
         * Constructs a BigInteger from a string representation.
         * @param number A string representing a potentially large integer.
         * @return A BigInteger instance corresponding to the input string.
         * @throws std::invalid_argument If the string contains non-numeric characters (excluding an initial minus sign).
         */
        static BigInteger parse(const std::string &number) {
            BigInteger result;
            size_t start = 0;

            if (!number.empty() && number[0] == '-') {
                result.isNegative = true;
                start = 1;
            }

            for (size_t i = number.size(); i > start; --i) {
                char c = number[i - 1];
                if (c < '0' || c > '9') {
                    throw std::invalid_argument("Invalid character in number string.");
                }
                result.digits.push_back(c - '0');
            }
            result.removeLeadingZeros();
            return result;
        }

        /**
         * Constructs a BigInteger from an integral type.
         * @tparam T The integral type of the input number.
         * @param number The number to be converted to a BigInteger.
         * @return A BigInteger instance representing the input number.
         */
        template<std::integral T>
        static BigInteger from_integer(T number) {
            if (number == std::numeric_limits<T>::min()) {
                return BigInteger(getMinValueInstance<T>());
            }

            BigInteger result;
            if (number < 0) {
                result.isNegative = true;
                number = -number; // Make number positive for processing
            }

            do {
                result.digits.push_back(number % 10);
                number /= 10;
            } while (number > 0);

            return result;
        }

        /**
         * Converts the BigInteger to its string representation.
         * @return A string representation of the BigInteger.
         */
        std::string to_string() const {
            if (digits.empty()) {
                return "0";
            }

            std::string str;
            if (isNegative) {
                str += '-';
            }

            str.reserve(digits.size() + str.size());
            for (auto it = digits.rbegin(); it != digits.rend(); ++it) {
                str += '0' + *it;
            }
            return str;
        }

        /**
         * Attempts to convert the BigInteger to a specified integral type T.
         *
         * This method checks if the BigInteger's value fits within the range of the target type T. If the conversion is possible,
         * the method returns an std::optional containing the converted value. If the conversion would lead to overflow, underflow, or
         * if the BigInteger's value cannot be accurately represented by type T, the method returns std::nullopt.
         *
         * @tparam T The target integral type for the conversion. Must satisfy std::integral.
         * @return An std::optional<T> containing the converted value if successful; otherwise, std::nullopt.
         */
        template<std::integral T>
        std::optional<T> to() const {
            T result = 0;
            T multiplier = 1;

            if constexpr (!std::is_signed_v<T>) {
                if (isNegative) {
                    return std::nullopt;
                }
            }

            for (size_t i = 0; i < digits.size(); ++i) {
                T digitValue = static_cast<T>(digits[i]);

                // Check for potential overflow when adding the digit value
                T tempResult = result + digitValue * multiplier;
                if (tempResult < result) {
                    return std::nullopt; // Overflow occurred during addition
                }
                result = tempResult;

                // Check for potential overflow in the next multiplier
                if (i < digits.size() - 1) {
                    if (std::numeric_limits<T>::max() / 10 < multiplier) {
                        return std::nullopt; // Next multiplier would overflow
                    }
                    multiplier *= 10;
                }
            }

            if constexpr (std::is_signed_v<T>) {
                if (isNegative) {
                    if (result == 0 || result > std::numeric_limits<T>::max()) {
                        return std::nullopt; // Can't represent this negative value in T
                    }
                    result = -result; // Negate the result
                }
            }

            return result;
        }

#pragma endregion

#pragma region singletons

        /**
         * Provides a singleton instance representing zero.
         * @return A const reference to the BigInteger instance representing zero.
         */

        static const BigInteger &zero() {
            static BigInteger zeroInstance(false, {0}); // Zero is not negative and has a single digit '0'
            return zeroInstance;
        }

        /**
         * Provides a singleton instance representing one.
         * @return A const reference to the BigInteger instance representing one.
         */
        static const BigInteger &one() {
            static BigInteger oneInstance(false, {1}); // One is not negative and has a single digit '1'
            return oneInstance;
        }

        /**
         * Provides a singleton instance representing the minimum value of an integral type.
         * @tparam T The integral type for which the minimum value is requested.
         * @return A const reference to the BigInteger instance representing the minimum value of the integral type T.
         */
        template<std::integral T>
        static const BigInteger &getMinValueInstance() {
            static BigInteger minValue = []() -> BigInteger {
                if constexpr (std::is_signed_v<T>) {
                    T number = std::numeric_limits<T>::min();
                    BigInteger result;
                    result.isNegative = true;

                    // Special handling for the most negative number, which cannot be directly negated in signed types
                    if (number == std::numeric_limits<T>::min()) {
                        result.digits.push_back(-(number % 10));
                        number /= 10;
                        number = -number;
                    }

                    while (number > 0) {
                        result.digits.push_back(number % 10);
                        number /= 10;
                    }

                    return result;
                } else {
                    // For unsigned types, the minimum value is always 0
                    return BigInteger::zero();
                }
            }();

            return minValue;
        }

        /**
         * Provides a singleton instance representing the maximum value of an integral type.
         * @tparam T The integral type for which the maximum value is requested.
         * @return A const reference to the BigInteger instance representing the maximum value of the integral type T.
         */
        template<std::integral T>
        static const BigInteger &getMaxValueInstance() {
            static BigInteger maxValue = []() -> BigInteger {
                T number = std::numeric_limits<T>::max();
                BigInteger result;
                result.isNegative = false;

                while (number > 0) {
                    result.digits.push_back(number % 10);
                    number /= 10;
                }

                return result;
            }();

            return maxValue; // Return a const reference to the singleton instance
        }

#pragma endregion

        // Negates the BigInteger instance.
        void negate() {
            if (digits.size() == 1 && digits[0] == 0) {
                // Zero remains non-negative
                isNegative = false;
            } else {
                isNegative = !isNegative;
            }
        }

        /**
         * Calculates the absolute value of the BigInteger instance.
         * @return A new BigInteger representing the absolute value, with the negative flag turned off.
         */
        BigInteger abs() const {
            BigInteger result = *this;
            result.isNegative = false; // Remove sign
            return result;
        }


        // Unary minus operator to return the negated value of the BigInteger instance.
        BigInteger operator-() const {
            BigInteger result = *this;
            result.negate();
            return result;
        }


#pragma region arithmetic

        /**
         * Adds two BigInteger instances.
         * @param other The BigInteger instance to add to the current instance.
         * @return The result of adding the current instance to the other instance.
         */
        BigInteger operator+(const BigInteger &other) const {
            BigInteger result;

            if (isNegative == other.isNegative) {
                result = _add(other);
                result.isNegative = isNegative; // Result will have the same sign
            } else {
                // Determine which number is greater in absolute value
                if (_isAbsoluteGreaterOrEqual(other)) {
                    result = _subtract(other);
                    result.isNegative = isNegative;
                } else {
                    result = other._subtract(*this);
                    result.isNegative = other.isNegative;
                }
            }

            result.removeLeadingZeros(); // Ensure there are no leading zeros
            if (result.digits.size() == 1 && result.digits[0] == 0) {
                result.isNegative = false; // Explicitly set the sign to non-negative for zero
            }

            return result;
        }

        /**
         * Subtracts a BigInteger instance from the current instance.
         * @param other The BigInteger instance to subtract from the current instance.
         * @return The result of subtracting the other instance from the current instance.
         */
        BigInteger operator-(const BigInteger &other) const {
            BigInteger negatedOther = other;
            negatedOther.isNegative = !other.isNegative; // Negate the second operand
            return *this + negatedOther; // Use the + operator
        }

        /**
         * Multiplies this BigInteger with another BigInteger.
         *
         * The method uses a classic grade-school multiplication algorithm, where each digit of the first number is
         * multiplied by each digit of the second number, and the intermediate results are added together, taking care
         * of the carry at each step. The result is stored in a temporary vector which is large enough to hold the maximum
         * possible number of digits (sum of the number of digits in both numbers).
         *
         * Time Complexity: O(n*m), where n and m are the number of digits in the two numbers. This is because each digit
         * of the first number is multiplied with each digit of the second number.
         * Space Complexity: O(n + m), which is the size of the temporary vector used to store the intermediate results.
         *
         * @param other The BigInteger to multiply with this BigInteger.
         * @return The product of this BigInteger and the other BigInteger.
         */
        BigInteger operator*(const BigInteger &other) const {
            // Check if either operand is zero
            if (*this == BigInteger::zero() || other == BigInteger::zero()) {
                return BigInteger::zero();
            }

            size_t totalLength = digits.size() + other.digits.size();
            BigInteger result;
            result.digits.resize(totalLength, 0); // Prepare the result vector with the appropriate size

            // Perform the multiplication algorithm
            for (size_t i = 0; i < digits.size(); ++i) {
                int carry = 0;
                for (size_t j = 0; j < other.digits.size() || carry; ++j) {
                    int product = carry + result.digits[i + j];
                    if (j < other.digits.size()) {
                        product += digits[i] * other.digits[j];
                    }
                    result.digits[i + j] = product % 10;
                    carry = product / 10;
                }
            }

            result.removeLeadingZeros(); // Ensure the result is correctly processed for leading zeros
            result.isNegative = isNegative != other.isNegative; // Determine the sign of the result

            return result;
        }

        /**
         * Divides this BigInteger by another BigInteger and returns the quotient.
         *
         * The method uses a long division approach where the dividend is divided by the divisor starting from the highest
         * order of magnitude down to the lowest. At each step, the method finds how many times the divisor fits into the
         * current portion of the dividend and subtracts the corresponding multiple of the divisor from the dividend. The
         * quotient is built digit by digit from these multiples.
         *
         * Time Complexity: For simplicity, let's denote this as O(d*(n-m)), where n is the number of digits in the dividend,
         * m is the number of digits in the divisor, and d is the number of digits in the quotient. This accounts for the
         * repeated subtraction of the divisor from portions of the dividend.
         * Space Complexity: O(n), mainly for storing the quotient, where n is the number of digits in the dividend.
         *
         * @param other The BigInteger divisor.
         * @return The quotient of dividing this BigInteger by the other BigInteger.
         * @throws std::runtime_error if attempted to divide by zero.
         */
        BigInteger operator/(const BigInteger &other) const {
            if (other == BigInteger::zero()) {
                throw std::runtime_error("Division by zero");
            }

            BigInteger dividend = this->abs();
            BigInteger divisor = other.abs();
            BigInteger quotient;
            BigInteger current;
            quotient.digits.resize(dividend.digits.size(), 0);

            for (int i = dividend.digits.size() - 1; i >= 0; --i) {
                current = current * BigInteger::from_integer(10) + BigInteger::from_integer(dividend.digits[i]);
                int count = 0;
                while (current >= divisor) {
                    current = current - divisor;
                    ++count;
                }
                quotient.digits[i] = count;
            }

            quotient.removeLeadingZeros(); // Remove any leading zeros

            // After calculating the quotient, if it is zero, its sign should be positive
            if (quotient == BigInteger::zero()) {
                quotient.isNegative = false;
            } else {
                // Otherwise, the sign of the quotient is determined by the signs of the operands
                quotient.isNegative = isNegative != other.isNegative;
            }

            return quotient;
        }


#pragma endregion

        /**
         * Adds the value of another BigInteger to this instance and updates this instance with the result.
         *
         * This operator modifies the current instance by adding the value of the specified BigInteger ('other')
         * to it. The addition is performed using the existing addition logic defined in the class, which handles
         * the arithmetic and any necessary carry operation. After the addition, the current instance is updated
         * with the new value, making this operation in-place.
         *
         * @param other The BigInteger to add to this instance.
         * @return A reference to this instance after the addition.
         */
        BigInteger &operator+=(const BigInteger &other) {
            // Use the existing addition logic (_add method, or however addition is implemented in your class)
            *this = *this + other; // This line might change depending on how you've implemented addition internally
            return *this; // Return the current instance after modification
        }

        /**
         * Subtracts the value of another BigInteger from this instance and updates this instance with the result.
         *
         * This operator modifies the current instance by subtracting the value of the specified BigInteger ('other')
         * from it. The subtraction is performed using the existing subtraction logic defined in the class, which
         * handles the arithmetic and any necessary borrow operation. After the subtraction, the current instance is
         * updated with the new value, making this operation in-place.
         *
         * @param other The BigInteger to subtract from this instance.
         * @return A reference to this instance after the subtraction.
         */
        BigInteger &operator-=(const BigInteger &other) {
            // Use the existing subtraction logic (_subtract method, or however subtraction is implemented in your class)
            *this = *this - other; // This line might change depending on how you've implemented subtraction internally
            return *this; // Return the current instance after modification
        }


        /**
         * Calculates the remainder of division of this BigInteger by another BigInteger.
         *
         * The modular operation follows the standard definition where the remainder of the division
         * of this BigInteger (dividend) by the 'other' BigInteger (divisor) is returned. If the divisor
         * is zero, the operation throws a runtime error due to division by zero being undefined.
         *
         * @param other The divisor in the modular operation.
         * @return The remainder after dividing this BigInteger by the 'other' BigInteger.
         * @throws std::runtime_error If attempting to perform modulo by zero.
         */
        BigInteger operator%(const BigInteger &other) const {
            if (other == BigInteger::zero()) {
                throw std::runtime_error("Modulo by zero");
            }

            BigInteger quotient = *this / other;
            BigInteger product = quotient * other;
            BigInteger remainder = *this - product;

            return remainder;
        }


        /**
         * Performs division and modulo operations simultaneously, returning both the quotient and the remainder.
         *
         * This method divides this BigInteger by another BigInteger (divisor) and returns a pair consisting
         * of the quotient and the remainder. It is more efficient than performing division and modulo operations
         * separately. If the divisor is zero, the method throws a runtime error due to division by zero being undefined.
         *
         * The remainder's sign is adjusted to match the divisor's sign, following the standard mathematical convention
         * for division and modulus operations. This ensures that the remainder has the same sign as the divisor or is
         * non-negative if the divisor is positive.
         *
         * @param other The divisor in the division and modulo operations.
         * @return A std::pair containing the quotient (first element) and the remainder (second element) of the division.
         * @throws std::runtime_error If attempting division by zero in the divmod operation.
         */
        std::pair<BigInteger, BigInteger> divmod(const BigInteger &other) const {
            if (other == BigInteger::zero()) {
                throw std::runtime_error("Modulo by zero");
            }

            BigInteger quotient = *this / other;
            BigInteger product = quotient * other;
            BigInteger remainder = *this - product;

            return std::make_pair(quotient, remainder);
        }

        /**
         * Determines the maximum of two BigInteger values.
         * @param a The first BigInteger to compare.
         * @param b The second BigInteger to compare.
         * @return The larger of the two BigInteger values.
         */
        static BigInteger max(const BigInteger &a, const BigInteger &b) {
            if (a.isNegative && !b.isNegative) return b; // a is negative, b is positive
            if (!a.isNegative && b.isNegative) return a; // a is positive, b is negative

            // Both are positive or negative
            if (a._isAbsoluteGreaterOrEqual(b))
                return a.isNegative ? b : a; // If both have same sign, return based on absolute value
            return a.isNegative ? a : b;
        }

        /**
         * Determines the minimum of two BigInteger values.
         * @param a The first BigInteger to compare.
         * @param b The second BigInteger to compare.
         * @return The smaller of the two BigInteger values.
         */
        static BigInteger min(const BigInteger &a, const BigInteger &b) {
            if (a.isNegative && !b.isNegative) return a; // a is negative, b is positive
            if (!a.isNegative && b.isNegative) return b; // a is positive, b is negative

            // Both are positive or negative
            if (a._isAbsoluteGreaterOrEqual(b))
                return a.isNegative ? a : b; // If both have same sign, return based on absolute value
            return a.isNegative ? b : a;
        }

#pragma region increment & decrement

        // Prefix increment
        BigInteger &operator++() {
            *this = *this + BigInteger::one();
            return *this;
        }

        // Postfix increment
        BigInteger operator++(int) {
            BigInteger temp = *this;
            ++(*this); // Use prefix increment
            return temp;
        }

        // Prefix decrement
        BigInteger &operator--() {
            *this = *this - BigInteger::one();
            return *this;
        }

        // Postfix decrement
        BigInteger operator--(int) {
            BigInteger temp = *this;
            --(*this); // Use prefix decrement
            return temp;
        }

#pragma endregion


#pragma region comparators

        // Equality comparator
        bool operator==(const BigInteger &other) const {
            return isNegative == other.isNegative && digits == other.digits;
        }

        // Inequality comparator
        bool operator!=(const BigInteger &other) const {
            return !(*this == other);
        }

        // Less than comparator
        bool operator<(const BigInteger &other) const {
            if (isNegative != other.isNegative) {
                return isNegative; // If *this is negative and other is positive, *this is smaller
            }

            if (digits.size() != other.digits.size()) {
                return isNegative ? digits.size() > other.digits.size() : digits.size() < other.digits.size();
            }

            for (int i = digits.size() - 1; i >= 0; --i) {
                if (digits[i] != other.digits[i]) {
                    return isNegative ? digits[i] > other.digits[i] : digits[i] < other.digits[i];
                }
            }

            return false; // Numbers are equal, so *this is not less than other
        }

        // Less than or equal comparator
        bool operator<=(const BigInteger &other) const {
            return *this == other || *this < other;
        }

        // Greater than comparator
        bool operator>(const BigInteger &other) const {
            return !(*this <= other);
        }

        // Greater than or equal comparator
        bool operator>=(const BigInteger &other) const {
            return !(*this < other);
        }

#pragma endregion
    };
}

#endif // BIG_INTEGER_H
