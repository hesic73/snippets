#ifndef SORTED_UTILS_H
#define SORTED_UTILS_H
#include <vector>
#include <concepts>
#include <optional>

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

    template <typename T, std::integral I = int>
    // func should return values in ascending order for the indices in the range [low, high]
    std::optional<I> binary_search(I low,
                                   I high,
                                   const T &value,
                                   auto &&func)
    {

        while (low <= high)
        {
            I mid = low + (high - low) / 2;
            T res = func(mid);
            if (res == value)
            {
                return mid;
            }
            else if (res < value)
            {
                low = mid + 1;
            }
            else
            {
                high = mid - 1;
            }
        }

        return std::nullopt;
    }

    template <typename T, std::integral I = int>
    // func should return values in anon-decreasing order for the indices in the range [low, high]
    // return the greatest integer num in the range [low, high], such that func(num)<=value
    I greatest_index(I low,
                     I high,
                     const T &value,
                     auto &&func)
    {

        while (low <= high)
        {
            I mid = low + (high - low) / 2;
            T res = func(mid);
            if (res <= value)
            {
                low = mid + 1;
            }
            else
            {
                high = mid - 1;
            }
        }

        return high;
    }

    /**
     * Sorts three elements in non-decreasing order using a simple comparison and swap algorithm.
     *
     * @tparam T The type of the elements to be sorted. Must be an integral type.
     * @param a Reference to the first element, will be the smallest after sorting.
     * @param b Reference to the second element, will be the middle element after sorting.
     * @param c Reference to the third element, will be the largest after sorting.
     */
    template <std::integral T>
    void sortThree(T &a, T &b, T &c)
    {
        if (a > b)
        {
            std::swap(a, b);
        }
        if (b > c)
        {
            std::swap(b, c);
        }
        if (a > b)
        {
            std::swap(a, b);
        }
    }

}

#endif // SORTED_UTILS_H