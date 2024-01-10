#ifndef GRAPH_H
#define GRAPH_H

#include <functional>
#include <vector>
#include <optional>
#include <queue>
#include <cassert>
#include <unordered_map>
#include <unordered_set>

namespace hsc_snippets
{
    // if nodes are 0-indexed, we can use vector to replace unordered_map and unordered_set
    void breadth_first_search(std::unordered_map<int, std::vector<int>> &adjacency_list, int root, std::function<void(int, int)> callback)
    {
        auto s = std::unordered_set<int>{};
        auto pq = std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>>{};
        pq.emplace(0, root);
        while (!pq.empty())
        {
            auto [dist, node] = pq.top();
            pq.pop();

            if (s.contains(node))
            {
                continue;
            }
            s.insert(node);

            callback(dist,node);

            for (auto dst : adjacency_list[node])
            {
                if (s.contains(dst))
                {
                    continue;
                }
                pq.emplace(dist + 1, dst);
            }
        }
    }
}

#endif // GRAPH_H