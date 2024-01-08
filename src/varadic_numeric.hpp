#ifndef VARADIC_NUMERIC_H
#define VARADIC_NUMERIC_H

#include <concepts>
namespace hsc_snippets
{

	template <typename T>
	concept numeric = std::integral<T> || std::floating_point<T>;

	template <numeric T>
	bool lessThanAll(T x, T val)
	{
		return x < val;
	}
	template <numeric T, numeric... Args>
	bool lessThanAll(T x, T val, Args... args)
	{
		if (!(x < val))
			return false;
		return lessThanAll(x, args...);
	}

	template <numeric T>
	bool lessThanOrEqualToAll(T x, T val)
	{
		return x <= val;
	}
	template <numeric T, numeric... Args>
	bool lessThanOrEqualToAll(T x, T val, Args... args)
	{
		if (!(x <= val))
			return false;
		return lessThanOrEqualToAll(x, args...);
	}

	template <numeric T>
	bool greaterThanAll(T x, T val)
	{
		return x > val;
	}
	template <numeric T, numeric... Args>
	bool greaterThanAll(T x, T val, Args... args)
	{
		if (!(x > val))
			return false;
		return greaterThanAll(x, args...);
	}

	template <numeric T>
	bool greaterThanOrEqualToAll(T x, T val)
	{
		return x >= val;
	}
	template <numeric T, numeric... Args>
	bool greaterThanOrEqualToAll(T x, T val, Args... args)
	{
		if (!(x >= val))
			return false;
		return greaterThanOrEqualToAll(x, args...);
	}

	template <numeric T>
	T sum(T x)
	{
		return x;
	}
	template <numeric T, numeric... Args>
	T sum(T x, Args... args)
	{
		return x + sum(args...);
	}

}

#endif // VARADIC_NUMERIC_H