#include <catch2/catch_test_macros.hpp>
#include "graph.hpp"
#include <vector>
#include <unordered_map>
using namespace hsc_snippets;

TEST_CASE("graph.hpp", )
{
    auto adjacency_list = std::vector<std::vector<int>>(7);
    adjacency_list[0].push_back(1);
    adjacency_list[0].push_back(2);
    adjacency_list[2].push_back(3);
    adjacency_list[2].push_back(4);
    adjacency_list[3].push_back(5);
    adjacency_list[5].push_back(6);
    SECTION("bfs")
    {
        auto nodes_dist_bfs = std::unordered_map<int, int>{};
        breadth_first_search(adjacency_list, 0, [&nodes_dist_bfs](int dist, int node)
                             { nodes_dist_bfs[node] = dist; });
        REQUIRE(nodes_dist_bfs[0] == 0);
        REQUIRE(nodes_dist_bfs[1] == 1);
        REQUIRE(nodes_dist_bfs[2] == 1);
        REQUIRE(nodes_dist_bfs[3] == 2);
        REQUIRE(nodes_dist_bfs[5] == 3);
        REQUIRE(nodes_dist_bfs[6] == 4);
    }

    SECTION("dfs")
    {
        auto nodes_dist_dfs = std::unordered_map<int, int>{};
        depth_first_search(adjacency_list, 0, [&nodes_dist_dfs](int dist, int node)
                           { nodes_dist_dfs[node] = dist; });
        // The result of DFS traversal may vary depending on the order of traversal
        // Therefore, we are only checking if each node is visited during the traversal
        REQUIRE(nodes_dist_dfs[0] == 0);
        REQUIRE(nodes_dist_dfs[1] == 1);
        REQUIRE(nodes_dist_dfs[2] == 1);
        REQUIRE(nodes_dist_dfs[3] == 2);
        REQUIRE(nodes_dist_dfs[4] == 2); // Not strictly required but for completeness
        REQUIRE(nodes_dist_dfs[5] == 3);
        REQUIRE(nodes_dist_dfs[6] == 4);
    }
}