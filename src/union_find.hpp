#ifndef UNION_FIND_H
#define UNION_FIND_H

namespace hsc_snippets
{
#include <vector>

    class UnionFind
    {
    private:
        std::vector<int> parent;
        std::vector<int> rank;

    public:
        /**
         * @brief Construct a new Union Find object.
         * @param size The number of elements in the set.
         */
        explicit UnionFind(int size) : parent(size), rank(size, 0)
        {
            for (int i = 0; i < size; ++i)
            {
                parent[i] = i;
            }
        }

        /**
         * @brief Find the set containing element 'p'.
         * @param p The element to find.
         * @return The set containing element 'p'.
         */
        int find(int p)
        {
            if (parent[p] != p)
            {
                parent[p] = find(parent[p]); // Path compression
            }
            return parent[p];
        }

        /**
         * @brief Union the sets containing elements 'p' and 'q'.
         * @param p The first element.
         * @param q The second element.
         */
        void unionSets(int p, int q)
        {
            int rootP = find(p);
            int rootQ = find(q);

            if (rootP == rootQ)
                return; // 'p' and 'q' are already in the same set.

            // Merge smaller set into the larger one.
            if (rank[rootP] < rank[rootQ])
            {
                parent[rootP] = rootQ;
            }
            else if (rank[rootP] > rank[rootQ])
            {
                parent[rootQ] = rootP;
            }
            else
            {
                parent[rootQ] = rootP;
                rank[rootP] += 1; // Increase the rank if both have the same rank.
            }
        }
    };

}

#endif // UNION_FIND_H
