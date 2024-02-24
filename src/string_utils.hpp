#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <functional>
#include <vector>
#include <optional>
#include <queue>
#include <cassert>
#include <unordered_map>
#include <sstream>

namespace hsc_snippets
{
    /**
     * Searches for all occurrences of a pattern within a text using the Knuth-Morris-Pratt (KMP) algorithm.
     *
     * The KMP algorithm pre-processes the pattern to construct an array of longest proper prefixes which are also suffixes (LPS array).
     * It then uses this LPS array to skip redundant comparisons when a mismatch occurs, thereby improving the search efficiency.
     *
     * @param pat The pattern string to search for within the text.
     * @param txt The text string in which to search for the pattern.
     * @return A vector containing the starting indices of all occurrences of 'pat' within 'txt'.
     */
    std::vector<int> kmpSearch(const std::string &pat, const std::string &txt)
    {
        int M = pat.size();
        int N = txt.size();

        // Longest Prefix Suffix (lps) array
        std::vector<int> lps(M);
        std::vector<int> result;

        // Preprocess the pattern
        int len = 0;
        lps[0] = 0; // lps[0] is always 0
        int i = 1;
        while (i < M)
        {
            if (pat[i] == pat[len])
            {
                len++;
                lps[i] = len;
                i++;
            }
            else
            {
                if (len != 0)
                {
                    len = lps[len - 1];
                }
                else
                {
                    lps[i] = 0;
                    i++;
                }
            }
        }

        // Search the pattern in txt
        i = 0;     // index for txt[]
        int j = 0; // index for pat[]
        while (i < N)
        {
            if (pat[j] == txt[i])
            {
                j++;
                i++;
            }

            if (j == M)
            {
                result.push_back(i - j);
                j = lps[j - 1];
            }
            else if (i < N && pat[j] != txt[i])
            {
                if (j != 0)
                {
                    j = lps[j - 1];
                }
                else
                {
                    i = i + 1;
                }
            }
        }

        return result;
    }

    /**
     * Checks if a given string is a palindrome.
     *
     * @param s The string to check for palindromicity.
     * @return True if 's' is a palindrome, False otherwise.
     */
    bool isPalindrome(const std::string &s)
    {
        assert(!s.empty());
        const int n = s.size();
        for (int i = 0; i < n / 2; i++)
        {
            if (s[i] != s[n - 1 - i])
            {
                return false;
            }
        }
        return true;
    }

    /**
     * Convert a vector of integral type T to its string representation.
     *
     * @tparam T The integral type of elements in the vector.
     * @param vec The vector to convert.
     * @return The string representation of the vector.
     */
    template <std::integral T>
    std::string to_string(const std::vector<T> &vec)
    {
        std::stringstream ss;
        ss << "[";
        for (size_t i = 0; i < vec.size(); ++i)
        {
            ss << vec[i];
            if (i < vec.size() - 1)
            { // Check if it's not the last element
                ss << ", ";
            }
        }
        ss << "]";
        return ss.str();
    }

    /**
     * Convert a vector of strings to its string representation, with elements separated by commas.
     * The resulting string is enclosed in square brackets.
     *
     * @param vec The vector of strings to convert. Each element in the vector is expected to be a string.
     * @return A string that represents the vector's contents, formatted as "[element1, element2, ...]".
     *         If the vector is empty, the returned string will be "[]".
     */
    std::string to_string(const std::vector<std::string> &vec)
    {
        std::stringstream ss;
        ss << "[";
        for (size_t i = 0; i < vec.size(); ++i)
        {
            ss << vec[i];
            if (i < vec.size() - 1)
            { // Check if it's not the last element
                ss << ", ";
            }
        }
        ss << "]";
        return ss.str();
    }

    /**
     * Convert a vector of vectors of integral type T to its string representation.
     *
     * @tparam T The integral type of elements in the vectors.
     * @param vec The vector of vectors to convert.
     * @return The string representation of the vector of vectors.
     */
    template <std::integral T>
    std::string to_string(const std::vector<std::vector<T>> &vec)
    {
        std::stringstream ss;
        ss << "[";
        for (size_t i = 0; i < vec.size(); ++i)
        {
            ss << to_string(vec[i]);
            if (i < vec.size() - 1)
            { // Check if it's not the last element
                ss << ", ";
            }
        }
        ss << "]";
        return ss.str();
    }

}

#endif // STRING_UTILS_H