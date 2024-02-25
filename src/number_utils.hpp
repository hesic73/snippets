#ifndef NUMBER_UTILS_H
#define NUMBER_UTILS_H

#include <concepts>
#include <cmath>
#include <vector>

namespace hsc_snippets
{
	/**
	 * Calculates the number of digits in the decimal representation of an integer.
	 *
	 * @tparam T The type of the input number, constrained to integral types.
	 * @param num The input number whose number of decimal digits is to be calculated.
	 * @return The number of digits in the decimal representation of num.
	 */
	template <std::integral T>
	int numDigits(T num)
	{
		int cnt = 0;
		while (num != 0)
		{
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
	template <std::integral T>
	int numBits(T num)
	{
		if (num < 0)
		{
			return sizeof(T) << 3;
		}
		int cnt = 0;
		while (num != 0)
		{
			cnt += 1;
			num = num >> 1;
		}
		return cnt;
	}

	/**
	 * Calculates the greatest common divisor (GCD) of two numbers using the Euclidean algorithm.
	 *
	 * @tparam T A numeric type that should be an integral type (e.g., int, long).
	 * @param a The first number.
	 * @param b The second number.
	 * @return The greatest common divisor of a and b.
	 */
	template <std::integral T>
	T gcd(T a, T b)
	{
		while (b != 0)
		{
			T temp = b;
			b = a % b;
			a = temp;
		}
		return a; // When b becomes 0, a contains the gcd
	}

	/**
	 * Calculates the least common multiple (LCM) of two numbers using the formula:
	 * LCM(a, b) = (a * b) / GCD(a, b)
	 *
	 * @tparam T A numeric type that should be an integral type (e.g., int, long).
	 * @param a The first number.
	 * @param b The second number.
	 * @return The least common multiple of a and b.
	 */
	template <std::integral T>
	T lcm(T a, T b)
	{
		return (a * b) / gcd(a, b);
	}

	/**
	 * Implements the Sieve of Eratosthenes algorithm to find all prime numbers up to a given limit n.
	 *
	 * @param n The upper limit (inclusive) up to which prime numbers are to be found.
	 * @return A std::vector<int> containing all the prime numbers less than or equal to n.
	 */
	std::vector<int> SieveOfEratosthenes(int n)
	{
		// Initialize a boolean vector "prime" with entries up to n. All entries are initially set to true.
		// A value in prime[i] will be false if i is not a prime number, and true if it is a prime number.
		std::vector<bool> prime(n + 1, true);
		prime[0] = prime[1] = false; // 0 and 1 are not considered prime numbers.

		// This vector will store all the prime numbers found.
		std::vector<int> primes;

		// Start iterating from the first prime number, 2, up to the square root of n.
		// We only need to go up to sqrt(n) because if n has a divisor greater than sqrt(n),
		// it must also have a smaller one, so all composites will have been marked by this point.
		for (int p = 2; p <= std::sqrt(n); ++p)
		{
			// If prime[p] is true, then it is a prime number.
			if (prime[p])
			{
				// Mark all multiples of p starting from p^2 as not prime.
				// Starting from p^2 because all smaller multiples of p would have already been marked by smaller primes.
				for (int i = p * p; i <= n; i += p)
				{
					prime[i] = false;
				}
			}
		}

		// Collect all prime numbers: iterate over the range up to n and
		// add the number to the primes list if its corresponding value in the prime vector is true.
		for (int p = 2; p <= n; ++p)
		{
			if (prime[p])
			{
				primes.push_back(p);
			}
		}

		// Return the vector containing all the primes found.
		return primes;
	}
}

#endif // NUMBER_UTILS_H