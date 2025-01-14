#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <functional>
#include <vector>
#include <optional>
#include <queue>
#include <cassert>
#include <unordered_map>
#include <sstream>

namespace hsc_snippets {
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
    static std::vector<int> kmpSearch(const std::string &pat, const std::string &txt) {
        const int M = static_cast<int>(pat.size());
        const int N = static_cast<int>(txt.size());

        // Longest Prefix Suffix (lps) array
        std::vector<int> lps(M);
        std::vector<int> result;

        // Preprocess the pattern
        int len = 0;
        lps[0] = 0; // lps[0] is always 0
        int i = 1;
        while (i < M) {
            if (pat[i] == pat[len]) {
                len++;
                lps[i] = len;
                i++;
            } else {
                if (len != 0) {
                    len = lps[len - 1];
                } else {
                    lps[i] = 0;
                    i++;
                }
            }
        }

        // Search the pattern in txt
        i = 0; // index for txt[]
        int j = 0; // index for pat[]
        while (i < N) {
            if (pat[j] == txt[i]) {
                j++;
                i++;
            }

            if (j == M) {
                result.push_back(i - j);
                j = lps[j - 1];
            } else if (i < N && pat[j] != txt[i]) {
                if (j != 0) {
                    j = lps[j - 1];
                } else {
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
    static bool isPalindrome(const std::string &s) {
        assert(!s.empty());
        const int n = static_cast<int>(s.size());
        for (int i = 0; i < n / 2; i++) {
            if (s[i] != s[n - 1 - i]) {
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
    template<std::integral T>
    std::string to_string(const std::vector<T> &vec) {
        std::stringstream ss;
        ss << "[";
        for (size_t i = 0; i < vec.size(); ++i) {
            ss << vec[i];
            if (i < vec.size() - 1) {
                // Check if it's not the last element
                ss << ", ";
            }
        }
        ss << "]";
        return ss.str();
    }

    /**
     * Convert a pair of integral type T to its string representation.
     *
     * @tparam T The integral type of the pair elements.
     * @param p The pair to convert to a string representation.
     * @return The string representation of the pair, formatted as "{first, second}".
     */
    template<std::integral T>
    std::string to_string(std::pair<T, T> p) {
        std::stringstream ss;
        ss << "{";
        ss << p.first;
        ss << ", ";
        ss << p.second;
        ss << "}";
        return ss.str();
    }

    /**
     * Convert a vector of pairs of integral type T to its string representation.
     *
     *
     * @tparam T The integral type of the elements in the pairs within the vector.
     * @param vec The vector of pairs to convert to a string representation.
     * @return The string representation of the vector of pairs, formatted as "[{first1, second1}, {first2, second2}, ...]".
     */
    template<std::integral T>
    std::string to_string(const std::vector<std::pair<T, T> > &vec) {
        std::stringstream ss;
        ss << "[";
        for (size_t i = 0; i < vec.size(); ++i) {
            ss << to_string(vec[i]);
            if (i < vec.size() - 1) {
                // Check if it's not the last element
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
    static std::string to_string(const std::vector<std::string> &vec) {
        std::stringstream ss;
        ss << "[";
        for (size_t i = 0; i < vec.size(); ++i) {
            ss << vec[i];
            if (i < vec.size() - 1) {
                // Check if it's not the last element
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
    template<std::integral T>
    std::string to_string(const std::vector<std::vector<T> > &vec) {
        std::stringstream ss;
        ss << "[";
        for (size_t i = 0; i < vec.size(); ++i) {
            ss << to_string(vec[i]);
            if (i < vec.size() - 1) {
                // Check if it's not the last element
                ss << ", ";
            }
        }
        ss << "]";
        return ss.str();
    }

    /**
     * Splits a given string into a vector of substrings based on a specified delimiter.
     *
     * @param s The input string to be split.
     * @param delimiter The character used as the delimiter to split the string.
     * @return A vector of substrings obtained by splitting the input string by the delimiter.
     */
    static std::vector<std::string> string_split(const std::string &s, char delimiter) {
        std::vector<std::string> tokens;
        std::string token;
        std::istringstream tokenStream(s);
        while (std::getline(tokenStream, token, delimiter)) {
            tokens.push_back(token);
        }
        return tokens;
    }

    /**
     * Repeats a given string `s` for `n` times efficiently.
     *
     * This function creates a new string by repeating the input string `s` for `n` times.
     * It pre-allocates the required memory and employs a doubling strategy to minimize
     * the number of concatenations, which enhances performance, especially for large `n`.
     *
     * @param s The string to be repeated.
     * @param n The number of times to repeat the string.
     * @return A new string consisting of `s` repeated `n` times.
     */
    static std::string string_repeat(const std::string &s, size_t n) {
        if (n == 0) return "";
        if (n == 1) return s;
        if (s.empty()) return "";

        std::string result;
        result.reserve(n * s.size());

        size_t current_length = s.size();
        while (result.size() + current_length <= n * s.size()) {
            result += s;
        }

        // Append the remaining part to reach exactly n * s.size()
        result += result.substr(0, (n * s.size()) - result.size());

        return result;
    }

    /**
     * Repeats a given character `c` for `n` times, producing a new string.
     *
     * This function creates a string consisting of the character `c` repeated `n` times.
     * It efficiently initializes the string with the required size and fills it with the character `c`.
     *
     * @param c The character to be repeated.
     * @param n The number of times to repeat the character.
     * @return A new string consisting of the character `c` repeated `n` times. If `n` is 0, returns an empty string.
     */
    static std::string string_repeat(char c, size_t n) {
        if (n == 0) return "";
        std::string result(n, c);
        return result;
    }

    /**
     * Joins a vector of strings into a single string, using a specified delimiter between each string.
     *
     * @param strings The vector of strings to be joined.
     * @param delimiter The string used as the delimiter between each element in the vector.
     * @return A new string consisting of the elements in `strings`, joined by `delimiter`.
     */
    static std::string string_join(const std::vector<std::string> &strings, const std::string &delimiter) {
        if (strings.empty()) return "";

        std::ostringstream result;
        auto iter = strings.begin();
        result << *iter++; // Add the first element without the delimiter

        while (iter != strings.end()) {
            result << delimiter << *iter++;
        }

        return result.str();
    }
}

#endif // STRING_UTILS_H
