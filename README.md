# snippets
![tests](https://github.com/hesic73/snippets/actions/workflows/tests.yml/badge.svg)
![Static Badge](https://img.shields.io/badge/std-c%2B%2B20-blue)
[![GitHub license](https://img.shields.io/badge/license-MIT-blue.svg)](https://raw.githubusercontent.com/hesic73/snippets/master/LICENSE)

(hopefully) useful code snippets for LeetCode.

## Overview

| file                   | description                                                  |
| ---------------------- | ------------------------------------------------------------ |
| modular_arithmetic.hpp | `MODULO` is fixed, which is enough for LeetCode.             |
| number_utils.hpp       |                                                              |
| varadic_numeric.hpp    |                                                              |
| sorted_utils.hpp       |                                                              |
| binary_tree.hpp        |                                                              |
| linked_list.hpp        |                                                              |
| graph.hpp              | with the help of GPT-4                                       |
| string_utils.hpp       | with the help of GPT-4                                       |
| monotonic_stack.hpp    |                                                              |
| dominant_tracker.hpp   | [LeetCode 2780](https://leetcode.com/problems/minimum-index-of-a-valid-split/description/) |
| segment_tree.hpp       | adapted from https://oi-wiki.org/ds/seg/                     |
| sliding_window.hpp     | with the help of GPT-4                                       |
| interval_map.hpp       | Initially, I aimed for a simplified interval tree, but it turned out differently. Although it's not thoroughly tested and might have some bugs, I managed to use it successfully to solve LeetCode 218's Skyline Problem. Check out the solution here: [LeetCode Submission](https://leetcode.com/problems/the-skyline-problem/submissions/1172986139/). |
| union_find.hpp         | with the help of GPT-4                                       |
| big_integer.hpp        | with the help of GPT-4                                       |

## Usage

To incorporate `snippets` into your C++ project, you can use CMake's `FetchContent` module as shown below:

```cmake
cmake_minimum_required(VERSION 3.11)
project(YourProject)

include(FetchContent)
FetchContent_Declare(
    snippets
    GIT_REPOSITORY https://github.com/hesic73/snippets.git
    GIT_TAG        main  # or any specific tag/version you prefer
)
FetchContent_MakeAvailable(snippets)

add_executable(YourApplication ...)
target_link_libraries(YourApplication PRIVATE snippets)
```

You can then include the desired header files from `snippets` directly in your project's source files:

```C++
#include <iostream>
#include "big_integer.h"

int main() {
    auto a = hsc_snippets::BigInteger::factorial(100);
    auto b = hsc_snippets::BigInteger::pow(hsc_snippets::BigInteger::from_integer(3), 100);
    std::cout << a.to_string() << std::endl;
    std::cout << b.to_string() << std::endl;
}
```

## Running Tests

The test appears in this manner:

```bash
mkdir -p build
cd build
cmake ..
cmake --build . --config Release
ctest -v -C Release
```

