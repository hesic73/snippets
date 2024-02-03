import os
import sys
import re
from string import Template

HEADER_TEMPLATE = Template("""#ifndef ${name_upper}_H
#define ${name_upper}_H

namespace hsc_snippets
{
    
}

#endif // ${name_upper}_H
""")


TEST_TEMPLATE = Template("""#include <catch2/catch_test_macros.hpp>
#include "${name}.hpp"
using namespace hsc_snippets;

TEST_CASE("${name}.hpp", )
{
    
}
""")


def is_valid_name(name: str):
    # Check for null, empty, or whitespace names
    if not name or name.isspace():
        return False

    # Check for invalid characters
    invalid_chars = r'<>:"\/|?*'
    if any(char in invalid_chars for char in name):
        return False

    # Check if name contains only ASCII characters
    try:
        name.encode('ascii')
    except UnicodeEncodeError:
        return False

    # Check for alphanumeric characters and underscores only
    if not re.match(r'^[a-zA-Z0-9_]+$', name):
        return False

    return True


def main(name: str):
    name = name.strip()
    assert is_valid_name(name)
    hpp_file_path = os.path.join("src", name+".hpp")
    if os.path.exists(hpp_file_path):
        raise FileExistsError(f"The file '{hpp_file_path}' already exists.")

    with open(hpp_file_path, 'w') as file:
        file.write(HEADER_TEMPLATE.substitute(name_upper=name.upper()))

    test_file_path = os.path.join("test", f"test_{name}.cpp")
    if os.path.exists(test_file_path):
        raise FileExistsError(f"The file '{test_file_path}' already exists.")

    with open(test_file_path, 'w') as file:
        file.write(TEST_TEMPLATE.substitute(name=name))


if __name__ == "__main__":
    args = sys.argv[1:]
    assert len(args) == 1
    main(args[0])
