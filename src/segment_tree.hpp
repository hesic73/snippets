// adapted from https://oi-wiki.org/ds/seg/

#ifndef SEGMENT_TREE_H
#define SEGMENT_TREE_H

#include <vector>
#include <concepts>

namespace hsc_snippets
{
    template <std::integral T>
    class SegmentTree
    {
    private:
        const int n;
        std::vector<T> d;
        std::vector<T> lazy_tag;
        void build(const std::vector<T> &a, int s, int t, int p)
        {
            if (s == t)
            {
                d[p] = a[s];
                return;
            }
            int m = s + ((t - s) >> 1);
            build(a, s, m, p * 2), build(a, m + 1, t, p * 2 + 1);
            d[p] = d[p * 2] + d[(p * 2) + 1];
        }
        T _range_sum(int l, int r, int s, int t, int p)
        {
            if (l <= s && t <= r)
                return d[p];
            int m = s + ((t - s) >> 1), sum = 0;
            maintain(s, t, p);
            if (l <= m)
                sum += _range_sum(l, r, s, m, p * 2);
            if (r > m)
                sum += _range_sum(l, r, m + 1, t, p * 2 + 1);
            return sum;
        }
        void maintain(int cl, int cr, int p)
        {
            int cm = cl + (cr - cl) / 2;
            if (cl != cr && lazy_tag[p])
            {
                lazy_tag[p * 2] += lazy_tag[p];
                lazy_tag[p * 2 + 1] += lazy_tag[p];
                d[p * 2] += lazy_tag[p] * (cm - cl + 1);
                d[p * 2 + 1] += lazy_tag[p] * (cr - cm);
                lazy_tag[p] = 0;
            }
        }
        void _range_set(int l, int r, T val, int cl, int cr, int p)
        {
            if (l <= cl && cr <= r)
            {
                lazy_tag[p] = val;
                d[p] = (cr - cl + 1) * val;
                return;
            }
            int m = cl + (cr - cl) / 2;
            maintain(cl, cr, p);
            if (l <= m)
                _range_set(l, r, val, cl, m, p * 2);
            if (r > m)
                _range_set(l, r, val, m + 1, cr, p * 2 + 1);
            d[p] = d[p * 2] + d[p * 2 + 1];
        }
        void _range_add(int l, int r, T val, int cl, int cr, int p)
        {
            if (l <= cl && cr <= r)
            {
                lazy_tag[p] += val;
                d[p] += (cr - cl + 1) * val;
                return;
            }
            int m = cl + (cr - cl) / 2;
            maintain(cl, cr, p);
            if (l <= m)
                _range_add(l, r, val, cl, m, p * 2);
            if (r > m)
                _range_add(l, r, val, m + 1, cr, p * 2 + 1);
            d[p] = d[p * 2] + d[p * 2 + 1];
        }

    public:
        explicit SegmentTree(const std::vector<T> &a) : n(a.size())
        {
            auto vector_size = n << 2;
            d = std::vector<T>(vector_size);
            lazy_tag = std::vector<T>(vector_size, 0);
            build(a, 0, n - 1, 1);
        }
        /**
         * Compute the sum of values within the range [left, right].
         * @param left 0-indexed, inclusive
         * @param right 0-indexed, inclusive
         */
        T range_sum(int left, int right)
        {
            return _range_sum(left, right, 0, n - 1, 1);
        }

        /**
         * Assign `value` to all elements in the range [left, right].
         * @param left 0-indexed, inclusive
         * @param right 0-indexed, inclusive
         * @param value The value to set for each element within the specified range
         */
        void range_set(int left, int right, T value) { _range_set(left, right, value, 0, n - 1, 1); }

        /**
         * Add `value` to all elements in the range [left, right].
         * @param left 0-indexed, inclusive
         * @param right 0-indexed, inclusive
         * @param value The value to add for each element within the specified range
         */
        void range_add(int left, int right, T value) { _range_add(left, right, value, 0, n - 1, 1); }

        /**
         * Return the size of the original vector.
         */
        int size() const { return n; }
    };
}
#endif // SEGMENT_TREE_H