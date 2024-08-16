#ifndef MONOTONIC_STACK_H
#define MONOTONIC_STACK_H

#include <iostream>
#include <stack>
#include <functional>
#include <optional>
#include <vector>

namespace hsc_snippets {
    /**
     * A stack that maintains a monotonic order based on a comparator.
     * @tparam T The type of elements in the stack.
     * @tparam Comparator The comparator that defines the monotonic order.
     */
    template<typename T, typename Comparator>
    class MonotonicStack {
    private:
        std::stack<T> s;
        Comparator comp;

    public:
        /**
         * Pushes a value onto the stack. Values not meeting the monotonic condition are popped.
         * @param value The value to be pushed.
         * @return The previous top value that meets the monotonic condition, if any.
         */
        std::optional<T> push(const T &value) {
            while (!s.empty() && comp(s.top(), value)) {
                s.pop();
            }
            std::optional<T> ans;
            if (s.empty()) {
                ans = {};
            } else {
                ans = s.top();
            }
            s.push(value);
            return ans;
        }

        /**
         * Returns the top value of the stack.
         * @return The top value of the stack.
         */
        const T &top() const {
            return s.top();
        }

        /**
         * Checks if the stack is empty.
         * @return True if the stack is empty, false otherwise.
         */
        bool empty() const {
            return s.empty();
        }
    };

    template<typename T>
    using MonotonicDecreasingStack = MonotonicStack<T, std::less_equal<T>>;
    template<typename T>
    using MonotonicIncreasingStack = MonotonicStack<T, std::greater_equal<T>>;

    /**
     * Finds the next greater element for each element in a sequence.
     * @tparam T The type of elements in the sequence.
     * @param nums The sequence of elements.
     * @param no_greater Function to call when no greater element is found.
     * @return A vector containing the next greater element for each element in `nums`.
     */
    template<typename T>
    std::vector<T> nextGreaterElement(const std::vector<T> &nums, std::function<T()> no_greater) {
        std::vector<T> result{};
        result.reserve(nums.size());
        MonotonicDecreasingStack<T> decreasingStack;
        for (auto num: nums) {
            auto tmp = decreasingStack.push(num);
            if (!tmp.has_value()) {
                result.push_back(no_greater());
            } else {
                result.push_back(tmp.value());
            }
        }

        return result;
    }


    /**
     * LeetCode 84: Largest Rectangle in Histogram
     * This function calculates the maximum area of a rectangle that can be formed within a given histogram.
     * Each bar's height is given in the 'heights' vector, where each element represents the height of a bar.
     *
     * @param heights A vector of integers where each integer represents the height of a histogram bar.
     * @return The maximum area of the rectangle that can be formed in the histogram.
     */
    static int largestRectangleInHistogram(const std::vector<int> &heights) {
        std::stack<int> s;
        int maxArea = 0;
        int n = static_cast<int>(heights.size());
        for (int i = 0; i <= n; i++) {
            int h = (i == n ? 0 : heights[i]); // Add a bar of height 0 to flush the stack at the end.
            while (!s.empty() && h < heights[s.top()]) {
                int height = heights[s.top()];
                s.pop();
                int width = s.empty() ? i : i - s.top() - 1; // Calculate width using the stack's new top.
                maxArea = std::max(maxArea, height * width);
            }
            s.push(i); // Push the current index onto the stack.
        }
        return maxArea;
    }
}

#endif // MONOTONIC_STACK_H
