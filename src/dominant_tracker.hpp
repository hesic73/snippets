#ifndef DOMINANT_TRACKER_H
#define DOMINANT_TRACKER_H
#include <optional>
#include <unordered_map>
namespace hsc_snippets
{
    /**
     * The DominantTracker class is designed to track elements added to it and determine the most frequently occurring element (the dominant element).
     * The dominant element is defined as an element whose frequency is more than half the size of all elements added.
     */
    class DominantTracker
    {
    private:
        int size;
        std::unordered_map<int, int> m;
        int max_value;
        int max_freq;

    public:
        /**
         * Constructor initializes an empty tracker with no elements.
         */
        DominantTracker() : size(0), m(), max_value(), max_freq(0) {}
        /**
         * Adds a new element to the tracker and updates the most frequent element if necessary.
         * @param value The element to be added to the tracker.
         */
        void add(int value)
        {
            size += 1;
            auto it = m.find(value);
            if (it == m.end())
            {
                m.insert(it, {value, 1});
                if (max_freq < 1)
                {
                    max_freq = 1;
                    max_value = value;
                }
            }
            else
            {
                it->second += 1;
                if (max_freq < it->second)
                {
                    max_freq = it->second;
                    max_value = value;
                }
            }
        }

        /**
         * Returns the current dominant element if it exists.
         * A dominant element is defined as an element whose frequency is more than half the size of all elements added.
         * If no such element exists or no elements have been added, returns std::nullopt.
         * @return An optional containing the dominant element if it exists, otherwise std::nullopt.
         */
        std::optional<int> getDominant() const
        {
            if (size == 0 || ((max_freq << 1) <= size))
            {
                return std::nullopt;
            }
            else
            {
                return max_value;
            }
        }
    };

}
#endif // DOMINANT_TRACKER_H