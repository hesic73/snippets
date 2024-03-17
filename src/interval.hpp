#ifndef INTERVAL_H
#define INTERVAL_H

#include <map>
#include <concepts>
#include <optional>
#include <cassert>
#include <set>

namespace hsc_snippets {

    template<std::integral T>
    struct Interval {
        T left;  // inclusive
        T right; // exclusize
    };

    /*
     * transparent comparison:
     *
     * 2 is no less than [1,3]
     * [1,3] is no less than 2
     * So 2 is equivalent to [1,3]
     *
     * 1 is no less than [1,3]
     * [1,3] is no less than 1
     * So 1 is equivalent to [1,3]
     *
     * 3 is no less than [1,3]
     * [1,3] is less than 3
     * So 3 is not equivalent to [1,3]
     *
     */
    template<std::integral T>
    static bool operator<(const Interval<T> &interval, T x) {
        return interval.right <= x;
    }

    template<std::integral T>
    static bool operator<(T x, const Interval<T> &interval) {
        return x < interval.left;
    }

    // we ensure that intervals never overlap
    template<std::integral T>
    static bool operator<(const Interval<T> &interval1, const Interval<T> &interval2) {
        return interval1.left < interval2.left;
    }

    template<std::integral T>
    struct Override {
        T operator()(T old_value, T new_value) const {
            return new_value;
        }
    };

    template<std::integral T>
    struct Maximum {
        T operator()(T old_value, T new_value) const {
            return std::max(old_value, new_value);
        }
    };

    /**
     * A data structure for efficiently managing intervals and their associated values.
     * It allows for adding new intervals with specified values, querying the value at any given point within the intervals,
     * and consolidating adjacent intervals with identical values to minimize fragmentation.
     * The behavior of overlapping intervals during updates can be customized through a user-defined update policy.
     *
     * Template Parameters:
     * - T: The type of the endpoints of the intervals, required to be an integral type (e.g., int, long).
     * - V: The type of the values associated with each interval.
     * - update_policy_t: A struct that defines the policy for resolving values of overlapping intervals.
     *   It must be a callable that takes two arguments of type V (the existing and new values) and returns a resolved value of type V.
     *
     * The class uses a balanced binary search tree (std::map) internally to store intervals in a non-overlapping manner,
     * ensuring efficient queries and updates. The update and query operations are expected to perform in O(log n) time complexity,
     * where n is the number of intervals in the map.
     */
    template<std::integral T, std::integral V, typename update_policy_t = Override<T>>
    // update_policy_t is a callable with a signature of  V(V old_value, V new_value)
    class IntervalMap {
    public:
        explicit IntervalMap() = default;

        /**
         * Updates the interval map by adding a new interval specified by left (inclusive) and right (exclusive) boundaries,
         * associating it with the given value.
         * If the new interval overlaps with existing intervals, the provided update_policy is applied to resolve the value conflicts.
         *
         * @param left The starting boundary of the interval to add, inclusive.
         * @param right The ending boundary of the interval to add, exclusive. Must be greater than left.
         * @param value The value to associate with the interval.
         */
        void update(T left, T right, V value) {
            assert(left < right); // or UB

            auto it = map.find(left);
            if (it != map.end()) {
                auto p = *it;
                map.erase(it);

                // the value for the overlapped area
                auto _value = update_policy(p.second, value);

                // the code below is messy in effort to eliminate fragmentation

                if (p.first.right > right) {
                    // [p.first.left, left) p.second
                    // [left, right) _value
                    // [right, p.first.right) p.second

                    if (_value != p.second) {
                        if (p.first.left != left) {
                            map.insert({Interval<T>{p.first.left, left}, p.second});
                        }
                        map.insert({Interval<T>{left, right}, _value});
                        map.insert({Interval<T>{right, p.first.right}, p.second});
                    } else {
                        map.insert({Interval<T>{p.first.left, p.first.right}, _value});
                    }
                } else {
                    // [p.first.left, left) p.second
                    // [left, p.first.right) _value
                    // [p.first.right, right) We don't know!!!

                    if (_value != p.second) {
                        if (p.first.left != left) {
                            map.insert({Interval<T>{p.first.left, left}, p.second});
                        }
                        map.insert({Interval<T>{left, p.first.right}, _value});
                    } else {
                        map.insert({Interval<T>{p.first.left, p.first.right}, _value});
                    }

                    if (p.first.right != right) {
                        // this is non-trivial
                        update(p.first.right, right, value);

                        // here there might be a fragmentation
                    }
                }

                return;
            }

            if (right - 1 > right) {
                throw std::overflow_error("right underflows.");
            }
            it = map.find(right - 1);

            if (it != map.end()) {
                auto p = *it;
                map.erase(it);
                assert(left < p.first.left); // or map.find(left)!=map.end(), we should not in this branch
                assert(right > p.first.left);
                assert(right <= p.first.right);

                update(left, p.first.left, value);

                auto _value = update_policy(p.second, value);

                // [p.first.left, right) _value
                // [right, p.first.right) p.second

                if (_value == p.second) {
                    map.insert({Interval<T>{p.first.left, p.first.right}, _value});
                } else {
                    map.insert({Interval<T>{p.first.left, right}, _value});
                    if (right < p.first.right) {
                        map.insert({Interval<T>{right, p.first.right}, p.second});
                    }
                }

                return;
            }

            // the first element that is no less than left
            // or interval.end>left
            it = map.lower_bound(left);
            if (it == map.end()) {
                // here there might be a fragmentation
                map.insert({Interval<T>{left, right}, value});
            } else {
                auto p = *it;
                assert(left < p.first.left);

                // we can safely add a new interval here.
                if (right <= p.first.left) {
                    map.insert({Interval<T>{left, right}, value});
                } else {
                    map.erase(it);
                    // if not, we add [left,p.first.left)
                    map.insert({Interval<T>{left, p.first.left}, value});
                    // and update [p.first.left,end)
                    update(p.first.left, right, value);
                }
            }
        }

        /**
         * Queries the value associated with a specific index in the interval tree.
         * If the index falls within an interval, the value for that interval is returned.
         * If the index does not fall within any interval, std::nullopt is returned.
         *
         * @param index The index to query in the interval tree.
         * @return An std::optional<V> containing the value associated with the index if it falls within an interval,
         * or std::nullopt if the index is not covered by any interval.
         */
        std::optional<V> query(T index) {
            auto it = map.find(index);
            if (it == map.end()) {
                return std::nullopt;
            } else {
                return it->second;
            }
        }

        /**
         * Consolidates adjacent intervals with the same value into a single interval to reduce fragmentation within the interval tree.
         */
        void defragment() {
            // We assume that erasion only affects the iterator of the erased element.
            if (map.size() < 2) {
                return;
            }
            auto it = map.begin();
            auto right = it->first.right;
            auto value = it->second;
            auto next_it = std::next(it);

            do {
                if (right == next_it->first.left && value == next_it->second) {
                    auto new_left = it->first.left;
                    auto new_right = next_it->first.right;
                    map.erase(next_it);
                    map.erase(it);
                    auto [new_it, success] = map.insert({Interval<T>{new_left, new_right}, value});
                    assert(success);
                    it = new_it;

                    right = it->first.right;
                    value = it->second;
                    next_it = std::next(it);
                } else {
                    it = std::next(it);
                    right = it->first.right;
                    value = it->second;
                    next_it = std::next(it);
                }

            } while (next_it != map.end());

            assert(no_fragmentation());
        }

        /**
         * Retrieves a list of all intervals and their associated values.
         *
         * @return A std::vector of std::tuple<T, T, V> elements,
         * where each tuple represents an interval with its left and right boundaries and its associated value.
         */
        std::vector<std::tuple<T, T, V>> getIntervals() const {
            std::vector<std::tuple<T, T, V>> intervals;
            intervals.reserve(map.size());

            for (const auto &entry: map) {
                intervals.emplace_back(entry.first.left, entry.first.right, entry.second);
            }

            return intervals;
        }

    private:
        /**
         * Verifies the absence of fragmentation in the map.
         *
         * @return True if no adjacent intervals with the same value are found unmerged, indicating a well-merged state.
         */
        bool no_fragmentation() {
            if (map.empty()) {
                return true;
            }

            auto it = map.begin();
            auto right = it->first.right;
            auto value = it->second;

            it = std::next(it);
            for (; it != map.end(); it = std::next(it)) {
                if (right == it->first.left && value == it->second) {
                    return false;
                }

                right = it->first.right;
                value = it->second;
            }
            return true;
        }

        std::map<Interval<T>, V, std::less<>> map;
        update_policy_t update_policy;
    };


    template<std::integral T>
    class IntervalSet {
    public:
        explicit IntervalSet() = default;

        /**
         * Updates the interval set by adding a new interval specified by left (inclusive) and right (exclusive) boundaries.
         * If the new interval overlaps with existing intervals, they will be merged into a single interval. But there might be fragmentation!
         *
         * @param left The starting boundary of the interval to add, inclusive.
         * @param right The ending boundary of the interval to add, exclusive. Must be greater than left.
         */
        void update(T left, T right) {
            assert(left < right); // or UB

            auto it = s.find(left);
            if (it != s.end()) {
                Interval<T> interval = *it;
                s.erase(it);


                // the code below is messy in effort to eliminate fragmentation

                if (interval.right > right) {
                    // [interval.left, left)
                    // [left, right)
                    // [right, interval.right)

                    s.insert(Interval<T>{interval.left, interval.right});

                } else {
                    // [interval.left, left)
                    // [left, interval.right)
                    // [interval.right, right)


                    s.insert(Interval<T>{interval.left, interval.right});


                    if (interval.right != right) {
                        //! this is non-trivial
                        update(interval.right, right);

                        // here there might be a fragmentation
                    }
                }

                return;
            }

            if (right - 1 > right) {
                throw std::overflow_error("right underflows.");
            }
            it = s.find(right - 1);

            if (it != s.end()) {
                Interval<T> interval = *it;
                s.erase(it);
                assert(left < interval.left); // or s.find(left)!=s.end(), we should not in this branch
                assert(right > interval.left);
                assert(right <= interval.right);

                update(left, interval.left);

                // [interval.left, right)
                // [right, interval.right)

                s.insert(Interval<T>{interval.left, interval.right});

                return;
            }

            // the first element that is no less than left
            // or interval.end>left
            it = s.lower_bound(left);
            if (it == s.end()) {
                // here there might be a fragmentation
                s.insert(Interval<T>{left, right});
            } else {
                Interval<T> interval = *it;
                assert(left < interval.left);

                // we can safely add a new interval here.
                if (right <= interval.left) {
                    s.insert(Interval<T>{left, right});
                } else {
                    s.erase(it);
                    // if not, we add [left,interval.left)
                    s.insert(Interval<T>{left, interval.left});
                    // and update [interval.left,end)
                    update(interval.left, right);
                }
            }
        }


        /**
 * Retrieves a list of all intervals and their associated values.
 *
 * @return A std::vector of std::tuple<T, T, V> elements,
 * where each tuple represents an interval with its left and right boundaries and its associated value.
 */
        std::vector<std::pair<T, T>> getIntervals() const {
            std::vector<std::pair<T, T>> intervals;
            intervals.reserve(s.size());

            for (const auto &interval: s) {
                intervals.emplace_back(interval.left, interval.right);
            }

            return intervals;
        }


        /**
         * Consolidates adjacent intervals into a single interval to reduce fragmentation within the interval tree.
         */
        void defragment() {
            // We assume that erasion only affects the iterator of the erased element.
            if (s.size() < 2) {
                return;
            }
            auto it = s.begin();
            auto right = it->right;
            auto next_it = std::next(it);

            do {
                if (right == next_it->left) {
                    auto new_left = it->left;
                    auto new_right = next_it->right;
                    s.erase(next_it);
                    s.erase(it);
                    auto [new_it, success] = s.insert(Interval<T>{new_left, new_right});
                    assert(success);
                    it = new_it;

                    right = it->right;
                    next_it = std::next(it);
                } else {
                    it = std::next(it);
                    right = it->right;
                    next_it = std::next(it);
                }

            } while (next_it != s.end());

            assert(no_fragmentation());
        }


    private:
        /**
         * Verifies the absence of fragmentation in the set.
         *
         * @return True if no adjacent intervals are found unmerged, indicating a well-merged state.
         */
        bool no_fragmentation() {
            if (s.empty()) {
                return true;
            }

            auto it = s.begin();
            auto right = it->right;

            it = std::next(it);
            for (; it != s.end(); it = std::next(it)) {
                if (right == it->left) {
                    return false;
                }
                right = it->right;
            }
            return true;
        }

        std::set<Interval<T>, std::less<>> s;
    };
}

#endif // INTERVAL_H
