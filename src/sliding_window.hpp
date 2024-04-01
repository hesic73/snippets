#ifndef SLIDING_WINDOW_H
#define SLIDING_WINDOW_H

#include <concepts>
#include <deque>
#include <optional>
#include <vector>
#include <unordered_map>

namespace hsc_snippets {

    template<std::integral T>
    class SlidingWindowMax {
    public:
        /**
         * @param size The maximum size of the sliding window.
        */
        explicit SlidingWindowMax(size_t size) : maxSize(size) {}

        /**
         * Updates the sliding window with a new value.
         * @param value The new value to be added to the window.
         */
        void update(T value) {
            // Remove the front element if it's outside the window's range
            while (!window.empty() && window.front().second <= currentIndex - static_cast<int>(maxSize)) {
                window.pop_front();
            }

            // Remove elements from the back that are smaller than the new element
            while (!window.empty() && value >= window.back().first) {
                window.pop_back();
            }

            // Add the new element to the back
            window.push_back(std::make_pair(value, currentIndex));

            currentIndex += 1;
        }

        /**
         * Retrieves the maximum value within the current window.
         * @return An optional containing the maximum value if the window is not empty; otherwise, an empty optional.
         */
        std::optional<T> get_max() const {
            if (window.empty()) {
                return std::nullopt; // Return an empty optional if the window is empty
            }
            return window.front().first; // The front always holds the maximum value
        }

        /**
         * Returns the current size of the sliding window.
         * @return The current size of the sliding window, which may be less than the maximum size.
         */
        size_t size() const {
            return std::min(maxSize, static_cast<size_t>(currentIndex -
                                                         (window.empty() ? currentIndex : window.front().second)));
        }

    private:
        std::deque<std::pair<T, int>> window; // Pair of value and its index
        size_t maxSize;
        int currentIndex = 0; // To keep track of the index of the latest element added
    };

    /**
     * Counts subarrays with at most `k` distinct integers using a sliding window approach.
     *
     * Related LeetCode Problem: https://leetcode.com/problems/subarrays-with-k-different-integers/description/
     *
     * @param nums A vector of integers.
     * @param k The maximum number of distinct integers allowed in a subarray.
     * @return The total count of such subarrays.
     */
    int subarraysWithAtMostKDistinct(const std::vector<int> &nums, int k) {
        const int n = static_cast<int>(nums.size());
        std::unordered_map<int, int> m;
        int ans = 0;
        int left = 0;
        int right = 0;

        while (right < n) {
            m[nums[right]]++;

            while (left <= right && m.size() > k) {
                auto it = m.find(nums[left]);
                if (it->second == 1) {
                    m.erase(it);
                } else {
                    it->second -= 1;
                }
                left++;
            }

            ans += (right - left + 1);

            right++;
        }

        return ans;
    }
}

#endif // SLIDING_WINDOW_H
