#include <catch2/catch_test_macros.hpp>
#include "binary_tree.hpp"
#include <vector>
#include <optional>
using namespace hsc_snippets;

TEST_CASE("binary_tree.hpp", )
{
    auto v = std::vector<std::optional<int>>{1, 2, 3, 4, 5, std::nullopt, 6};
    auto root = new_binary_tree(v);

    SECTION("inorder")
    {
        auto result = std::vector<int>{};
        auto expected_result = std::vector<int>{4, 2, 5, 1, 3, 6};
        inorder(root, [&result](int value)
                { result.push_back(value); });

        REQUIRE(result == expected_result);
    }

    SECTION("preorder")
    {
        auto result = std::vector<int>{};
        auto expected_result = std::vector<int>{1, 2, 4, 5, 3, 6};
        preorder(root, [&result](int value)
                 { result.push_back(value); });

        REQUIRE(result == expected_result);
    }

    SECTION("postorder")
    {
        auto result = std::vector<int>{};
        auto expected_result = std::vector<int>{4, 5, 2, 6, 3, 1};
        postorder(root, [&result](int value)
                  { result.push_back(value); });

        REQUIRE(result == expected_result);
    }

    delete_binary_tree(root);
}
