#ifndef DOMINANT_TRACKER_H
#define DOMINANT_TRACKER_H
#include <optional>
#include <unordered_map>
namespace hsc_snippets
{
    class DominantTracker
    {
    private:
        int size;
        std::unordered_map<int, int> m;
        int max_value;
        int max_freq;

    public:
        DominantTracker() : size(0), m(), max_value(), max_freq(0) {}
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