#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <functional>
#include <vector>
#include <optional>
#include <queue>
#include <cassert>

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

    void delete_binary_tree(TreeNode *root)
    {
        if (root == nullptr)
            return;
        delete_binary_tree(root->left);
        delete_binary_tree(root->right);
        delete root;
    }

    void inorder(TreeNode *root, std::function<void(int)> func)
    {
        if (root == nullptr)
            return;
        inorder(root->left, func);
        func(root->val);
        inorder(root->right, func);
    }

    void preorder(TreeNode *root, std::function<void(int)> func)
    {
        if (root == nullptr)
            return;
        func(root->val);
        preorder(root->left, func);
        preorder(root->right, func);
    }

    void postorder(TreeNode *root, std::function<void(int)> func)
    {
        if (root == nullptr)
            return;

        postorder(root->left, func);
        postorder(root->right, func);
        func(root->val);
    }

}

#endif // BINARY_TREE_H