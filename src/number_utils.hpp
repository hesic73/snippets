#ifndef NUMBER_UTILS_H
#define NUMBER_UTILS_H

#include <concepts>
#include <cmath>
#include <vector>
#include <array>
#include <cstdint>

namespace hsc_snippets {
	/**
	 * Calculates the number of digits in the decimal representation of an integer.
	 *
	 * @tparam T The type of the input number, constrained to integral types.
	 * @param num The input number whose number of decimal digits is to be calculated.
	 * @return The number of digits in the decimal representation of num.
	 */
	template<std::integral T>
	int numDigits(T num) {
		int cnt = 0;
		while (num != 0) {
			cnt += 1;
			num /= 10;
		}
		return cnt;
	}

	/**
	 * Calculates the number of bits required to represent an integer in binary.
	 * For negative numbers, it returns the number of bits in the type (e.g., 32 for int),
	 * assuming two's complement representation.
	 *
	 * @tparam T The type of the input number, constrained to integral types.
	 * @param num The input number whose binary bit count is to be calculated.
	 * @return The number of bits required to represent num in binary, or the bit size of T for negative numbers.
	 */
	template<std::integral T>
	int numBits(T num) {
		if (num < 0) {
			return sizeof(T) << 3;
		}
		int cnt = 0;
		while (num != 0) {
			cnt += 1;
			num = num >> 1;
		}
		return cnt;
	}

	/**
	 * Implements the Sieve of Eratosthenes algorithm to find all prime numbers up to a given limit n.
	 *
	 * @param n The upper limit (inclusive) up to which prime numbers are to be found.
	 * @return A std::vector<int> containing all the prime numbers less than or equal to n.
	 */
	static std::vector<int> SieveOfEratosthenes(int n) {
		// Initialize a boolean vector "prime" with entries up to n. All entries are initially set to true.
		// A value in prime[i] will be false if i is not a prime number, and true if it is a prime number.
		std::vector<bool> prime(n + 1, true);
		prime[0] = prime[1] = false; // 0 and 1 are not considered prime numbers.

		// This vector will store all the prime numbers found.
		std::vector<int> primes;

		// Start iterating from the first prime number, 2, up to the square root of n.
		// We only need to go up to sqrt(n) because if n has a divisor greater than sqrt(n),
		// it must also have a smaller one, so all composites will have been marked by this point.
		for (int p = 2; p <= std::sqrt(n); ++p) {
			// If prime[p] is true, then it is a prime number.
			if (prime[p]) {
				// Mark all multiples of p starting from p^2 as not prime.
				// Starting from p^2 because all smaller multiples of p would have already been marked by smaller primes.
				for (int i = p * p; i <= n; i += p) {
					prime[i] = false;
				}
			}
		}

		// Collect all prime numbers: iterate over the range up to n and
		// add the number to the primes list if its corresponding value in the prime vector is true.
		for (int p = 2; p <= n; ++p) {
			if (prime[p]) {
				primes.push_back(p);
			}
		}

		// Return the vector containing all the primes found.
		return primes;
	}

	/**
	 * Checks if a given number is a perfect square using a precomputed array of squares.
	 *
	 * @param num The number to check if it is a perfect square.
	 * @return True if num is a perfect square, otherwise false.
	 */
	static bool isPerfectSquare(std::int32_t num) {
		if (num < 0) {
			return false;
		}
		constexpr std::array<std::int32_t, 46341> arr = []()constexpr {
			std::array<std::int32_t, 46341> _arr = {};
			for (int i = 0; i < 46341; ++i) {
				_arr[i] = i * i;
			}
			return _arr;
		}();

		return std::binary_search(arr.begin(), arr.end(), num);
	}
}

#endif // NUMBER_UTILS_H
