#ifndef GRAPH_H
#define GRAPH_H

#include <functional>
#include <vector>
#include <optional>
#include <queue>
#include <stack>
#include <cassert>
#include <unordered_set>
#include <unordered_map>

namespace hsc_snippets
{
    /**
     * Constructs a weighted, directed adjacency list representation of a graph from a given set of edges.
     * Nodes are indexed from 0 to n-1.
     *
     * @param n The number of nodes in the graph.
     * @param edges A vector of vectors representing edges, where each inner vector
     *              contains three integers: [from, to, weight], denoting a weighted edge from
     *              node 'from' to node 'to' with the given weight.
     * @return A vector of vectors of pairs representing the adjacency list of the graph.
     *         Each inner vector corresponds to a node, containing pairs of connected nodes
     *         and their respective edge weights.
     */
    std::vector<std::vector<std::pair<int, int>>> make_weighted_directed_adjacency_list(int n, const std::vector<std::vector<int>> &edges)
    {
        auto adjacency_list = std::vector<std::vector<std::pair<int, int>>>(n);
        for (auto &&edge : edges)
        {
            int from = edge[0];
            int to = edge[1];
            int weight = edge[2];
            adjacency_list[from].emplace_back(to, weight);
        }
        return adjacency_list;
    }

    /**
     * Constructs an unweighted, undirected adjacency list representation of a graph from a given set of edges.
     * Nodes are indexed from 0 to n-1.
     *
     * @param n The number of nodes in the graph.
     * @param edges A vector of vectors representing edges, where each inner vector
     *              contains two integers: [from, to], denoting an edge from
     *              node 'from' to node 'to'.
     * @return A vector of vectors representing the adjacency list of the graph.
     *         Each inner vector corresponds to a node, containing the indices of
     *         connected nodes (edges are unweighted in this representation).
     */
    std::vector<std::vector<int>> make_unweighted_undirected_adjacency_list(int n, const std::vector<std::vector<int>> &edges)
    {
        auto adjacency_list = std::vector<std::vector<int>>(n);
        for (auto &&edge : edges)
        {
            int from = edge[0];
            int to = edge[1];
            adjacency_list[from].push_back(to);
            adjacency_list[to].push_back(from); // For undirected graph, edges are bidirectional
        }
        return adjacency_list;
    }

    /**
     * Constructs a weighted, undirected adjacency list representation of a graph from a given set of edges.
     * Nodes are indexed from 0 to n-1.
     *
     * @param n The number of nodes in the graph.
     * @param edges A vector of vectors representing edges, where each inner vector
     *              contains three integers: [from, to, weight], denoting a weighted edge between
     *              node 'from' and node 'to' with the given weight.
     * @return A vector of vectors of pairs representing the adjacency list of the graph.
     *         Each inner vector corresponds to a node, containing pairs of connected nodes
     *         and their respective edge weights.
     */
    std::vector<std::vector<std::pair<int, int>>> make_weighted_undirected_adjacency_list(int n, const std::vector<std::vector<int>> &edges)
    {
        auto adjacency_list = std::vector<std::vector<std::pair<int, int>>>(n);
        for (auto &&edge : edges)
        {
            int from = edge[0];
            int to = edge[1];
            int weight = edge[2];
            adjacency_list[from].emplace_back(to, weight);
            adjacency_list[to].emplace_back(from, weight); // For undirected graph, edges are bidirectional
        }
        return adjacency_list;
    }

    /**
     * Constructs an unweighted, directed adjacency list representation of a graph from a given set of edges.
     * Nodes are indexed from 0 to n-1.
     *
     * @param n The number of nodes in the graph.
     * @param edges A vector of vectors representing edges, where each inner vector
     *              contains two integers: [from, to], denoting a directed edge from
     *              node 'from' to node 'to'.
     * @return A vector of vectors representing the adjacency list of the graph.
     *         Each inner vector corresponds to a node, containing the indices of
     *         connected nodes (edges are unweighted in this representation).
     */
    std::vector<std::vector<int>> make_unweighted_directed_adjacency_list(int n, const std::vector<std::vector<int>> &edges)
    {
        auto adjacency_list = std::vector<std::vector<int>>(n);
        for (auto &&edge : edges)
        {
            int from = edge[0];
            int to = edge[1];
            adjacency_list[from].push_back(to);
        }
        return adjacency_list;
    }

    /**
     * Performs a breadth-first search (BFS) traversal on a graph represented by an adjacency list,
     * starting from the specified root node.
     *
     * @param adjacency_list The adjacency list representation of the graph.
     *                       Each element represents a node and contains the indices of its adjacent nodes.
     * @param root The index of the root node from which the BFS traversal starts.
     * @param callback A callback function invoked for each visited node during the BFS traversal.
     *                 It takes two parameters: the distance of the current node from the root
     *                 and the index of the current node.
     */
    void breadth_first_search(std::vector<std::vector<int>> &adjacency_list, int root, std::function<void(int, int)> callback)
    {
        auto visited = std::unordered_set<int>{};
        auto q = std::queue<std::pair<int, int>>{}; // Regular queue for BFS
        q.emplace(0, root);                         // Initialize queue with root node at distance 0
        while (!q.empty())
        {
            auto [dist, node] = q.front(); // Extract node at the front of the queue
            q.pop();

            if (visited.contains(node)) // Skip if node has already been visited
            {
                continue;
            }
            visited.insert(node); // Mark current node as visited

            callback(dist, node); // Invoke callback for the current node

            for (auto adjacent_node : adjacency_list[node]) // Explore adjacent nodes
            {
                if (visited.contains(adjacent_node)) // Skip if adjacent node has already been visited
                {
                    continue;
                }
                q.emplace(dist + 1, adjacent_node); // Enqueue adjacent node with distance incremented by 1
            }
        }
    }
    /**
     * Performs a breadth-first search (BFS) on an undirected graph starting from a given root node.
     * It uses a queue to explore nodes level by level, ensuring each node is visited exactly once.
     *
     * @param adjacency_list The graph represented as an adjacency list, where each key-value pair corresponds to
     *                       a node and its list of adjacent nodes.
     * @param root The starting node for the BFS.
     * @param callback A function to be called for each visited node. It takes the distance from the root
     *                 and the node itself as arguments.
     */
    void breadth_first_search(std::unordered_map<int, std::vector<int>> &adjacency_list, int root, std::function<void(int, int)> callback)
    {
        auto visited = std::unordered_set<int>{};
        auto q = std::queue<std::pair<int, int>>{}; // Regular queue for BFS
        q.emplace(0, root);                         // Initialize queue with root node at distance 0
        while (!q.empty())
        {
            auto [dist, node] = q.front(); // Extract node at the front of the queue
            q.pop();

            if (visited.contains(node)) // Skip if node has already been visited
            {
                continue;
            }
            visited.insert(node); // Mark current node as visited

            callback(dist, node); // Invoke callback for the current node

            for (auto adjacent_node : adjacency_list[node]) // Explore adjacent nodes
            {
                if (visited.contains(adjacent_node)) // Skip if adjacent node has already been visited
                {
                    continue;
                }
                q.emplace(dist + 1, adjacent_node); // Enqueue adjacent node with distance incremented by 1
            }
        }
    }

    /**
     * Performs a depth-first search (DFS) traversal on a graph represented by an adjacency list,
     * starting from the specified root node.
     *
     * @param adjacency_list The adjacency list representation of the graph.
     *                       Each element represents a node and contains the indices of its adjacent nodes.
     * @param root The index of the root node from which the DFS traversal starts.
     * @param callback A callback function invoked for each visited node during the DFS traversal.
     *                 It takes two parameters: the distance of the current node from the root
     *                 and the index of the current node.
     */
    void depth_first_search(std::vector<std::vector<int>> &adjacency_list, int root, std::function<void(int, int)> callback)
    {
        auto visited = std::unordered_set<int>{};
        auto stack = std::stack<std::pair<int, int>>{}; // Stack for DFS
        stack.emplace(0, root);                         // Initialize stack with root node at distance 0
        while (!stack.empty())
        {
            auto [dist, node] = stack.top(); // Extract node at the top of the stack
            stack.pop();

            if (visited.contains(node)) // Skip if node has already been visited
            {
                continue;
            }
            visited.insert(node); // Mark current node as visited

            callback(dist, node); // Invoke callback for the current node

            for (auto adjacent_node : adjacency_list[node]) // Explore adjacent nodes
            {
                if (visited.contains(adjacent_node)) // Skip if adjacent node has already been visited
                {
                    continue;
                }
                stack.emplace(dist + 1, adjacent_node); // Push adjacent node with distance incremented by 1
            }
        }
    }

    /**
     * Dijkstra's algorithm to find the shortest path from source to destination in a graph.
     *
     * @param n Number of vertices in the graph.
     * @param adjacency_list Adjacency list representation of the graph where each element is a pair representing an edge (to, weight).
     * @param src Source vertex.
     * @param dst Destination vertex.
     * @return Shortest distance from source to destination. Returns -1 if no path exists.
     */
    int dijkstra(int n, const std::vector<std::vector<std::pair<int, int>>> &adjacency_list, int src, int dst)
    {

        std::vector<int> dist(n, std::numeric_limits<int>::max());
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> pq;

        dist[src] = 0;
        pq.emplace(0, src);

        while (!pq.empty())
        {
            int u = pq.top().second;
            pq.pop();

            for (const auto &neighbor : adjacency_list[u])
            {
                int v = neighbor.first;
                int weight = neighbor.second;

                if (dist[v] > dist[u] + weight)
                {
                    dist[v] = dist[u] + weight;
                    pq.emplace(dist[v], v);
                }
            }
        }

        return dist[dst] == std::numeric_limits<int>::max() ? -1 : dist[dst];
    }

    /**
     * Finds an Eulerian path or circuit in a directed graph.
     *
     * This function assumes that the given graph has an Eulerian path or circuit,
     * which means the graph is connected and either:
     * <p>
     * - All vertices have equal in-degrees and out-degrees (Eulerian circuit), or
     * <p>
     * - All but two vertices have equal in-degrees and out-degrees, and one of those
     *   two vertices has out-degree = in-degree + 1 (start), and the other has
     *   in-degree = out-degree + 1 (end) (Eulerian path).
     *
     * @param edges A vector of pairs representing directed edges in the graph. Each pair (a, b)
     *              represents a directed edge from a to b.
     * @return A vector representing the Eulerian path or circuit as a sequence of vertex
     *         indices. If a circuit exists, the path can start from any vertex in the circuit.
     */
    std::vector<int> find_euler_path_directed(const std::vector<std::vector<int>> &edges)
    {
        std::unordered_map<int, std::stack<int>> adj;
        std::unordered_map<int, int> in;
        std::unordered_map<int, int> out;
        for (auto &&edge : edges)
        {
            int from = edge[0];
            int to = edge[1];
            adj[from].push(to);
            in[to] += 1;
            out[from] += 1;
        }

        int start = adj.begin()->first; // Default start node
        for (auto &&p : adj)
        {
            if (out[p.first] - in[p.first] == 1)
            { // Find the actual start node for Euler Path
                start = p.first;
                break;
            }
        }

        std::stack<int> current_path;
        std::vector<int> circuit;
        current_path.push(start);

        while (!current_path.empty())
        {
            int current_vertex = current_path.top();

            if (!adj[current_vertex].empty())
            { // If current vertex has neighbors
                int next_vertex = adj[current_vertex].top();
                adj[current_vertex].pop();      // Remove the edge from current to next
                current_path.push(next_vertex); // Move to next vertex
            }
            else
            {                                      // Backtrack
                circuit.push_back(current_vertex); // Add to Euler circuit/path
                current_path.pop();                // Remove the vertex as it has no more neighbors
            }
        }

        // Reverse the circuit to get the Euler path
        std::reverse(circuit.begin(), circuit.end());

        return circuit;
    }

    /**
     * Finds and returns all connected components in an undirected graph.
     * It iterates over all nodes, using a BFS starting from each unvisited node to discover all nodes
     * in the same connected component.
     *
     * @param adj The graph represented as an adjacency list, where keys are node identifiers and
     *            values are lists of adjacent nodes.
     * @return A vector of vectors, where each inner vector represents a connected component of the graph
     *         and contains all node identifiers within that component.
     */
    std::vector<std::vector<int>> find_connected_components(std::unordered_map<int, std::vector<int>> &adj)
    {
        std::unordered_map<int, bool> visited{}; // Tracks whether each node has been visited
        for (auto &&p : adj)
        {
            visited.insert({p.first, false}); // Initialize all nodes as unvisited
        }

        std::vector<std::vector<int>> connectedComponents; // Stores the connected components

        for (auto &&p : visited)
        {
            if (!p.second)
            {                               // For each unvisited node
                std::vector<int> component; // Stores the current component's nodes
                breadth_first_search(adj, p.first, [&visited, &component](int, int node)
                                     {
                                         visited[node] = true;      // Mark the node as visited
                                         component.push_back(node); // Add the node to the current component
                                     });                            // Perform BFS to find all nodes in this component
                connectedComponents.push_back(component);           // Add the current component to the list
            }
        }

        return connectedComponents; // Return all found connected components
    }


    /**
     * Counts the number of connected components in an undirected graph.
     *
     * @param adj The graph represented as an adjacency list, where keys are node identifiers and
     *            values are lists of adjacent nodes.
     * @return The number of connected components in the graph.
     */
    int count_connected_components(const std::unordered_map<int, std::vector<int>> &adj)
    {
        std::unordered_set<int> visited;
        int component_count = 0;

        auto dfs = [&](int node, auto &dfs_ref) -> void {
            visited.insert(node);
            for (int neighbor : adj.at(node))
            {
                if (visited.find(neighbor) == visited.end())
                {
                    dfs_ref(neighbor, dfs_ref);
                }
            }
        };

        for (const auto &p : adj)
        {
            int node = p.first;
            if (visited.find(node) == visited.end())
            {
                // Start a DFS from the unvisited node
                dfs(node, dfs);
                // After DFS, we've explored an entire connected component
                component_count++;
            }
        }

        return component_count;
    }

}

#endif // GRAPH_H