#include <catch2/catch_test_macros.hpp>
#include "disjoint_set.hpp"
using namespace hsc_snippets;

TEST_CASE("disjoint_set.hpp", )
{
    DisjointSet disjoint_set(10);

    disjoint_set.unionSets(1, 2); // Union sets containing 1 and 2.
    disjoint_set.unionSets(2, 3); // Union sets containing 2 and 3.
    disjoint_set.unionSets(4, 5); // Union sets containing 4 and 5.
    REQUIRE(disjoint_set.find(2) == 1);
    REQUIRE(disjoint_set.find(4) == 4);
    disjoint_set.unionSets(3, 4);       // Union sets containing 3 and 4.
    REQUIRE(disjoint_set.find(2) == 1); // Now, 2 and 4 should be in the same set.
    REQUIRE(disjoint_set.find(4) == 1);
}
