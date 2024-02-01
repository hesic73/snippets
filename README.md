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
| graph.hpp              |                                                              |
| string_utils.hpp       | Some functions are written by ChatGPT                        |
| monotonic_stack.hpp    |                                                              |
| dominant_tracker.hpp   | [LeetCode 2780](https://leetcode.com/problems/minimum-index-of-a-valid-split/description/) |

## Test

The test appears in this manner:

```bash
mkdir -p build
cd build
cmake ..
cmake --build . --config Release
ctest -v -C Release
```

