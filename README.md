# snippets
![tests](https://github.com/hesic73/snippets/actions/workflows/tests.yml/badge.svg)
![Static Badge](https://img.shields.io/badge/std-c%2B%2B20-blue)
[![GitHub license](https://img.shields.io/badge/license-MIT-blue.svg)](https://raw.githubusercontent.com/hesic73/snippets/master/LICENSE)

(hopefully) useful code snippets for LeetCode.

## C++

| file                        | description                                      |
| --------------------------- | ------------------------------------------------ |
| modular_arithmetic.hpp      | `MODULO` is fixed, which is enough for LeetCode. |
| num_digits.hpp              |                                                  |
| varadic_numeric.hpp         |                                                  |
| num_of_greater_elements.hpp |                                                  |
| binary_tree.hpp             |                                                  |
| graph.hpp                   |                                                  |

## Test

The test appears in this manner:

```bash
mkdir -p build
cd build
cmake ..
cmake --build . --config Release
ctest -v -C Release
```

