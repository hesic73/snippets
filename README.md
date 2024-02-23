# snippets
![tests](https://github.com/hesic73/snippets/actions/workflows/tests.yml/badge.svg)
![Static Badge](https://img.shields.io/badge/std-c%2B%2B20-blue)
[![GitHub license](https://img.shields.io/badge/license-MIT-blue.svg)](https://raw.githubusercontent.com/hesic73/snippets/master/LICENSE)

(hopefully) useful code snippets for LeetCode.

## C++

| file                   | description                                                  |
| ---------------------- | ------------------------------------------------------------ |
| modular_arithmetic.hpp | `MODULO` is fixed, which is enough for LeetCode.             |
| number_utils.hpp       |                                                              |
| varadic_numeric.hpp    |                                                              |
| sorted_utils.hpp       |                                                              |
| binary_tree.hpp        |                                                              |
| graph.hpp              | with the help of GPT-4                                       |
| string_utils.hpp       | with the help of GPT-4                                       |
| monotonic_stack.hpp    |                                                              |
| dominant_tracker.hpp   | [LeetCode 2780](https://leetcode.com/problems/minimum-index-of-a-valid-split/description/) |
| segment_tree.hpp       | adapted from https://oi-wiki.org/ds/seg/                     |
| sliding_window.hpp     | with the help of GPT-4                                       |
| interval_map.hpp       | Initially, I aimed for a simplified interval tree, but it turned out differently. Although it's not thoroughly tested and might have some bugs, I managed to use it successfully to solve LeetCode 218's Skyline Problem. Check out the solution here: [LeetCode Submission](https://leetcode.com/problems/the-skyline-problem/submissions/1172986139/). |

## Test

The test appears in this manner:

```bash
mkdir -p build
cd build
cmake ..
cmake --build . --config Release
ctest -v -C Release
```

