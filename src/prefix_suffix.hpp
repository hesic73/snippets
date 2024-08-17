#ifndef PREFIX_SUFFIX_H
#define PREFIX_SUFFIX_H

#include <concepts>
#include <vector>
#include <algorithm>
#include <numeric>

namespace hsc_snippets
{
    /**
     * @brief Computes the prefix maximums of a given vector.
     *
     * This function returns a vector where each element at index `i` contains
     * the maximum value in the inclusive subarray `v[0]` to `v[i]`.
     *
     * @tparam T The integral type of the elements in the input vector.
     * @param v The input vector of integral type T.
     * @return std::vector<T> A vector of the same size as `v`, where each element
     *         at index `i` is the maximum value of the inclusive subarray `v[0]` to `v[i]`.
     */
    template<std::integral T>
    static std::vector<T> getPrefixMax(const std::vector<T> &v) {
        if (v.empty()) {
            return {};
        }
        std::vector<T> prefixMax(v.size());
        prefixMax[0] = v[0];
        for (size_t i = 1; i < v.size(); ++i) {
            prefixMax[i] = std::max(prefixMax[i - 1], v[i]);
        }
        return prefixMax;
    }

    /**
     * @brief Computes the suffix maximums of a given vector.
     *
     * This function returns a vector where each element at index `i` contains
     * the maximum value in the inclusive subarray `v[i]` to `v[n-1]`, where `n` is the size of the vector.
     *
     * @tparam T The integral type of the elements in the input vector.
     * @param v The input vector of integral type T.
     * @return std::vector<T> A vector of the same size as `v`, where each element
     *         at index `i` is the maximum value of the inclusive subarray `v[i]` to `v[n-1]`.
     */
    template<std::integral T>
    static std::vector<T> getSuffixMax(const std::vector<T> &v) {
        if (v.empty()) {
            return {};
        }
        std::vector<T> suffixMax(v.size());
        size_t n = v.size();
        suffixMax[n - 1] = v[n - 1];
        for (size_t i = n - 2; i < n; --i) {
            suffixMax[i] = std::max(suffixMax[i + 1], v[i]);
        }
        return suffixMax;
    }

    /**
     * @brief Computes the prefix minimums of a given vector.
     *
     * This function returns a vector where each element at index `i` contains
     * the minimum value in the inclusive subarray `v[0]` to `v[i]`.
     *
     * @tparam T The integral type of the elements in the input vector.
     * @param v The input vector of integral type T.
     * @return std::vector<T> A vector of the same size as `v`, where each element
     *         at index `i` is the minimum value of the inclusive subarray `v[0]` to `v[i]`.
     */
    template<std::integral T>
    static std::vector<T> getPrefixMin(const std::vector<T> &v) {
        if (v.empty()) {
            return {};
        }
        std::vector<T> prefixMin(v.size());
        prefixMin[0] = v[0];
        for (size_t i = 1; i < v.size(); ++i) {
            prefixMin[i] = std::min(prefixMin[i - 1], v[i]);
        }
        return prefixMin;
    }

    /**
     * @brief Computes the suffix minimums of a given vector.
     *
     * This function returns a vector where each element at index `i` contains
     * the minimum value in the inclusive subarray `v[i]` to `v[n-1]`, where `n` is the size of the vector.
     *
     * @tparam T The integral type of the elements in the input vector.
     * @param v The input vector of integral type T.
     * @return std::vector<T> A vector of the same size as `v`, where each element
     *         at index `i` is the minimum value of the inclusive subarray `v[i]` to `v[n-1]`.
     */
    template<std::integral T>
    static std::vector<T> getSuffixMin(const std::vector<T> &v) {
        if (v.empty()) {
            return {};
        }
        std::vector<T> suffixMin(v.size());
        size_t n = v.size();
        suffixMin[n - 1] = v[n - 1];
        for (size_t i = n - 2; i < n; --i) {
            suffixMin[i] = std::min(suffixMin[i + 1], v[i]);
        }
        return suffixMin;
    }

    /**
     * @brief Computes the prefix sums of a given vector.
     *
     * This function returns a vector where each element at index `i` contains
     * the sum of the elements in the inclusive subarray `v[0]` to `v[i]`.
     *
     * @tparam T The integral type of the elements in the input vector.
     * @param v The input vector of integral type T.
     * @return std::vector<T> A vector of the same size as `v`, where each element
     *         at index `i` is the sum of the elements in the inclusive subarray `v[0]` to `v[i]`.
     */
    template<std::integral T>
    static std::vector<T> getPrefixSum(const std::vector<T> &v) {
        if (v.empty()) {
            return {};
        }
        std::vector<T> prefixSum(v.size());
        std::partial_sum(v.begin(), v.end(), prefixSum.begin());
        return prefixSum;
    }

    /**
     * @brief Computes the suffix sums of a given vector.
     *
     * This function returns a vector where each element at index `i` contains
     * the sum of the elements in the inclusive subarray `v[i]` to `v[n-1]`, where `n` is the size of the vector.
     *
     * @tparam T The integral type of the elements in the input vector.
     * @param v The input vector of integral type T.
     * @return std::vector<T> A vector of the same size as `v`, where each element
     *         at index `i` is the sum of the elements in the inclusive subarray `v[i]` to `v[n-1]`.
     */
    template<std::integral T>
    static std::vector<T> getSuffixSum(const std::vector<T> &v) {
        if (v.empty()) {
            return {};
        }
        std::vector<T> suffixSum(v.size());
        size_t n = v.size();
        std::partial_sum(v.rbegin(), v.rend(), suffixSum.rbegin());
        return suffixSum;
    }
}

#endif // PREFIX_SUFFIX_H
