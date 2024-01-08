#ifndef NUM_OF_GREATER_ELEMENTS
#define NUM_OF_GREATER_ELEMENTS
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
}

#endif // NUM_OF_GREATER_ELEMENTS