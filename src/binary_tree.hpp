#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <functional>
#include <vector>
#include <optional>
#include <queue>
#include <cassert>
#include <unordered_map>

namespace hsc_snippets
{
    struct TreeNode
    {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode() : val(0), left(nullptr), right(nullptr) {}
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
        TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    };

    /**
     * Constructs a binary tree from a vector of optional integers.
     *
     * @param v A vector of std::optional<int>, where each element represents a potential node in the
     *          binary tree. An std::nullopt value indicates the absence of a node at that position.
     * @return A pointer to the root node of the newly constructed binary tree. Returns nullptr if
     *         the input vector is empty.
     */
    TreeNode *new_binary_tree(const std::vector<std::optional<int>> v)
    {
        if (v.empty())
        {
            return nullptr;
        }

        const auto n = v.size();

        assert(v[0].has_value());

        auto root = new TreeNode(v[0].value());
        auto q = std::queue<TreeNode *>{};
        q.push(root);
        int i = 1;

        while (i < n)
        {
            auto node = q.front();
            q.pop();
            if (v[i].has_value())
            {
                node->left = new TreeNode(v[i].value());
                q.push(node->left);
            }
            i += 1;
            if (i >= n)
            {
                break;
            }
            if (v[i].has_value())
            {
                node->right = new TreeNode(v[i].value());
                q.push(node->right);
            }
            i += 1;
        }

        return root;
    }

    /**
     * Deletes all nodes of a binary tree to free memory.
     *
     * @param root A pointer to the root node of the binary tree. If the pointer is nullptr, the
     *             function does nothing, safely handling the case of an empty tree or reaching
     *             the end of a branch.
     */
    void delete_binary_tree(TreeNode *root)
    {
        if (root == nullptr)
            return;
        delete_binary_tree(root->left);
        delete_binary_tree(root->right);
        delete root;
    }

    /**
     * Calculates the depth of a binary tree.
     *
     * @param root A pointer to the root node of the binary tree. If the tree is empty (nullptr),
     *             the depth is considered to be 0.
     * @return The depth of the binary tree as an integer. An empty tree has a depth of 0.
     */
    int get_binary_tree_depth(TreeNode *root)
    {
        if (root == nullptr)
            return 0;
        int depth = 1;
        depth = std::max(depth, get_binary_tree_depth(root->left) + 1);
        depth = std::max(depth, get_binary_tree_depth(root->right) + 1);
        return depth;
    }

    /**
     * In-order traversal of a binary tree.
     * @param root Root node of the binary tree.
     * @param func Function to process each node's value.
     */
    void inorder(TreeNode *root, std::function<void(int)> func)
    {
        if (root == nullptr)
            return;
        inorder(root->left, func);
        func(root->val);
        inorder(root->right, func);
    }

    /**
     * Pre-order traversal of a binary tree.
     * @param root Root node of the binary tree.
     * @param func Function to process each node's value.
     */
    void preorder(TreeNode *root, std::function<void(int)> func)
    {
        if (root == nullptr)
            return;
        func(root->val);
        preorder(root->left, func);
        preorder(root->right, func);
    }

    /**
     * Post-order traversal of a binary tree.
     * @param root Root node of the binary tree.
     * @param func Function to process each node's value.
     */
    void postorder(TreeNode *root, std::function<void(int)> func)
    {
        if (root == nullptr)
            return;

        postorder(root->left, func);
        postorder(root->right, func);
        func(root->val);
    }

    /**
     * Converts a binary tree to an adjacency list representation. All node values in the binary tree must be unique.
     * The adjacency list is bidirectional, meaning for each parent-child relation,
     * both the parent's list contains the child and the child's list contains the parent.
     *
     * @param root A pointer to the root node of the binary tree. If the tree is empty (nullptr),
     *             the function returns an empty adjacency list.
     * @return An unordered_map where keys are node values and values are vectors of integers
     *         representing the node values of adjacent nodes.
     */
    std::unordered_map<int, std::vector<int>> binary_tree_to_adjacency_list(TreeNode *root)
    {
        auto adjacencyList = std::unordered_map<int, std::vector<int>>{};
        if (root == nullptr)
        {
            return adjacencyList;
        }
        auto q = std::queue<TreeNode *>{};
        q.push(root);
        while (!q.empty())
        {
            auto node = q.front();
            q.pop();
            if (node->left != nullptr)
            {
                adjacencyList[node->left->val].push_back(node->val);
                adjacencyList[node->val].push_back(node->left->val);
                q.push(node->left);
            }
            if (node->right != nullptr)
            {
                adjacencyList[node->right->val].push_back(node->val);
                adjacencyList[node->val].push_back(node->right->val);
                q.push(node->right);
            }
        }

        return adjacencyList;
    }

}

#endif // BINARY_TREE_H