#include <catch2/catch_test_macros.hpp>
#include "graph.hpp"
#include <vector>
#include <unordered_map>
using namespace hsc_snippets;

TEST_CASE("graph.hpp", )
{
    auto adjacency_list = std::unordered_map<int, std::vector<int>>{};
    adjacency_list[0].push_back(1);
    adjacency_list[0].push_back(2);
    adjacency_list[2].push_back(3);
    adjacency_list[2].push_back(4);
    adjacency_list[3].push_back(5);
    adjacency_list[5].push_back(6);
    SECTION("bfs")
    {
        auto nodes_dist = std::unordered_map<int, int>{};
        breadth_first_search(adjacency_list, 0, [&nodes_dist](int dist, int node)
                             { nodes_dist[node] = dist; });
        REQUIRE(nodes_dist[0] == 0);
        REQUIRE(nodes_dist[1] == 1);
        REQUIRE(nodes_dist[2] == 1);
        REQUIRE(nodes_dist[3] == 2);
        REQUIRE(nodes_dist[5] == 3);
        REQUIRE(nodes_dist[6] == 4);
    }
}
