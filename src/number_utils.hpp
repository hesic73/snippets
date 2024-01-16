#ifndef NUMBER_UTILS_H
#define NUMBER_UTILS_H

#include <concepts>

namespace hsc_snippets
{

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

}

#endif // NUMBER_UTILS_H