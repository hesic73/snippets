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

    /**
     * Finds the greatest index in a non-decreasing array where the function applied to the index
     * returns a value less than or equal to the specified value.
     *
     * @tparam T The type of the value against which the function's results are compared.
     * @tparam I The integral type of the index, defaulting to int.
     * @param low The lower bound of the search range (inclusive).
     * @param high The upper bound of the search range (inclusive).
     * @param value The value to compare against the function's results.
     * @param func The function to apply to each index, expected to return non-decreasing values for the range [low, high].
     * @return The greatest index for which func(index) <= value, or -1 if no such index exists.
     */
    template <typename T, std::integral I = int>
    I greatest_index(I low, I high, const T &value, auto &&func)
    {
        I ans = -1; // Initialize answer to -1 to indicate no valid index found yet
        while (low <= high)
        {
            I mid = low + (high - low) / 2; // Calculate the mid-point of the current search range
            T res = func(mid);              // Evaluate the function at the mid-point
            if (res <= value)
            {
                ans = mid;     // Update answer since res is less than or equal to value
                low = mid + 1; // Narrow the search to the right half to find the greatest index
            }
            else
            {
                high = mid - 1; // Narrow the search to the left half since res is greater than value
            }
        }

        return ans; // Return the found index or -1 if no such index exists
    }

    /**
     * Finds the smallest index in a non-decreasing array where the function applied to the index
     * returns a value greater than or equal to the specified value.
     *
     * @tparam T The type of the value against which the function's results are compared.
     * @tparam I The integral type of the index, defaulting to int.
     * @param low The lower bound of the search range (inclusive).
     * @param high The upper bound of the search range (inclusive).
     * @param value The value to compare against the function's results.
     * @param func The function to apply to each index, expected to return non-decreasing values for the range [low, high].
     * @return The smallest index for which func(index) >= value, or -1 if no such index exists.
     */
    template <typename T, std::integral I = int>
    I smallest_index(I low, I high, const T &value, auto &&func)
    {
        I ans = -1; // Initialize answer to -1 to indicate no valid index found yet
        while (low <= high)
        {
            I mid = low + (high - low) / 2; // Calculate the mid-point of the current search range
            T res = func(mid);              // Evaluate the function at the mid-point
            if (res >= value)
            {
                ans = mid;      // Update answer since res is greater than or equal to value
                high = mid - 1; // Narrow the search to the left half to find the smallest index
            }
            else
            {
                low = mid + 1; // Narrow the search to the right half since res is less than value
            }
        }

        return ans; // Return the found index or -1 if no such index exists
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