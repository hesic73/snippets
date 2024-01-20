#ifndef MONOTONIC_STACK_H
#define MONOTONIC_STACK_H

#include <iostream>
#include <stack>
#include <functional>
#include <optional>

namespace hsc_snippets
{

    template <typename T, typename Comparator>
    class MonotonicStack
    {
    private:
        std::stack<T> s;
        Comparator comp;

    public:
        std::optional<T> push(const T &value)
        {
            while (!s.empty() && comp(s.top(), value))
            {
                s.pop();
            }
            std::optional<T> ans;
            if (s.empty())
            {
                ans = {};
            }
            else
            {
                ans = s.top();
            }
            s.push(value);
            return ans;
        }

        const T &top() const
        {
            return s.top();
        }

        bool empty() const
        {
            return s.empty();
        }
    };

    template <typename T>
    using MonotonicDecreasingStack = MonotonicStack<T, std::less_equal<T>>;
    template <typename T>
    using MonotonicIncreasingStack = MonotonicStack<T, std::greater_equal<T>>;

    template <typename T>
    std::vector<T> nextGreaterElement(const std::vector<T> &nums, std::function<T()> no_greater)
    {
        std::vector<T> result{};
        result.reserve(nums.size());
        MonotonicDecreasingStack<T> decreasingStack;
        for (auto num : nums)
        {
            auto tmp = decreasingStack.push(num);
            if (!tmp.has_value())
            {
                result.push_back(no_greater());
            }
            else
            {
                result.push_back(tmp.value());
            }
        }

        return result;
    }

}

#endif // MONOTONIC_STACK_H
