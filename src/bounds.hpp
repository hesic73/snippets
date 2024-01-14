#ifndef BOUNDS_H
#define NBOUNDS_H
#include <vector>
#include <concepts>

namespace hsc_snippets
{
    template <std::totally_ordered T>
    int numOfGreaterElements(const std::vector<T> &v, T value)
    // v should be non-descreasing
    {
        auto it = std::lower_bound(v.cbegin(), v.cend(), value, [](const T &value, const T &element)
                                   { return value <= element; });
        if (it == v.cend())
        {
            return 0;
        }
        return v.cend() - it;
    }

    template <std::integral T>
    // vec must be in asending order. [start, end)
    bool containsInRange(const std::vector<T> &vec, T start, T end)
    {
        if (vec.empty() || start >= end)
        {
            return false;
        }

        // Lower bound of the range
        auto lower = std::lower_bound(vec.begin(), vec.end(), start);

        // Check if the lower bound is not beyond the vector and less than 'end'
        if (lower != vec.end() && *lower < end)
        {
            return true;
        }

        return false;
    }
}

#endif // BOUNDS_H