#include <catch2/catch_test_macros.hpp>
#include "union_find.hpp"
using namespace hsc_snippets;

TEST_CASE("union_find.hpp", )
{
    UnionFind uf(10); // Create a UnionFind with 10 elements.

    uf.unionSets(1, 2); // Union sets containing 1 and 2.
    uf.unionSets(2, 3); // Union sets containing 2 and 3.
    uf.unionSets(4, 5); // Union sets containing 4 and 5.
    REQUIRE(uf.find(2) == 1);
    REQUIRE(uf.find(4) == 4);
    uf.unionSets(3, 4);       // Union sets containing 3 and 4.
    REQUIRE(uf.find(2) == 1); // Now, 2 and 4 should be in the same set.
    REQUIRE(uf.find(4) == 1);
}
