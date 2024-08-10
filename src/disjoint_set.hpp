#ifndef DISJOINT_SET_H
#define DISJOINT_SET_H

namespace hsc_snippets
{
#include <vector>

    class DisjointSet
    {
    private:
        std::vector<int> parent;
        std::vector<int> rank;
        int count; // Number of distinct sets

    public:
        /**
         * @brief Construct a new Disjoint Set object.
         * @param size The number of elements in the set.
         */
        explicit DisjointSet(int size) : parent(size), rank(size, 0), count(size)
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

            count--; // Decrease the number of sets
        }

        /**
         * @brief Get the number of distinct sets.
         * @return The number of distinct sets.
         */
        int getCount() const
        {
            return count;
        }
    };

}

#endif // DISJOINT_SET_H
