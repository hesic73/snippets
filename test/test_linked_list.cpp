#include <catch2/catch_test_macros.hpp>
#include "linked_list.hpp"
using namespace hsc_snippets;

TEST_CASE("linked_list.hpp",) {
    SECTION("Test get_linked_list_length") {
        ListNode *head = new ListNode(1, new ListNode(2, new ListNode(3)));
        REQUIRE(get_linked_list_length(head) == 3);
        linked_list_delete(head); // Clean up
    }

    SECTION("Test make_linked_list") {
        std::vector<int> vec = {1, 2, 3};
        ListNode *head = make_linked_list(vec);
        REQUIRE(head->val == 1);
        REQUIRE(head->next->val == 2);
        REQUIRE(head->next->next->val == 3);
        linked_list_delete(head); // Clean up
    }

    SECTION("Test linked_list_to_vector") {
        ListNode *head = new ListNode(1, new ListNode(2, new ListNode(3)));
        std::vector<int> result = linked_list_to_vector(head);
        std::vector<int> expected = {1, 2, 3};
        REQUIRE(result == expected);
        linked_list_delete(head); // Clean up
    }

    SECTION("Test get_linked_list_ith_node") {
        std::vector<int> vec = {10, 20, 30, 40, 50};
        ListNode *head = make_linked_list(vec);

        // Test valid index
        ListNode *node = get_linked_list_ith_node(head, 2);
        REQUIRE(node != nullptr);
        REQUIRE(node->val == 30);

        // Test invalid index (out of bounds)
        node = get_linked_list_ith_node(head, 10);
        REQUIRE(node == nullptr);

        linked_list_delete(head); // Clean up
    }
}

TEST_CASE("linked_list_remove functionality", "[linked_list_remove]") {
    SECTION("Remove from an Empty List") {
        ListNode *head = nullptr;
        ListNode *result = linked_list_remove(head, 0, 1);
        REQUIRE(result == nullptr);
    }

    SECTION("Remove with Invalid Range") {
        std::vector<int> vec = {1, 2, 3};
        ListNode *head = make_linked_list(vec);
        ListNode *result = linked_list_remove(head, 2, 2);
        std::vector<int> expected = {1, 2, 3};
        REQUIRE(linked_list_to_vector(result) == expected);
        linked_list_delete(result);
    }

    SECTION("Remove from the Beginning") {
        std::vector<int> vec = {1, 2, 3, 4};
        ListNode *head = make_linked_list(vec);
        ListNode *result = linked_list_remove(head, 0, 2);
        std::vector<int> expected = {3, 4};
        REQUIRE(linked_list_to_vector(result) == expected);
        linked_list_delete(result);
    }

    SECTION("Remove from the Middle") {
        std::vector<int> vec = {1, 2, 3, 4};
        ListNode *head = make_linked_list(vec);
        ListNode *result = linked_list_remove(head, 1, 3);
        std::vector<int> expected = {1, 4};
        REQUIRE(linked_list_to_vector(result) == expected);
        linked_list_delete(result);
    }

    SECTION("Remove from the End") {
        std::vector<int> vec = {1, 2, 3, 4};
        ListNode *head = make_linked_list(vec);
        ListNode *result = linked_list_remove(head, 2, 5);
        std::vector<int> expected = {1, 2};
        REQUIRE(linked_list_to_vector(result) == expected);
        linked_list_delete(result);
    }

    SECTION("Remove the Entire List") {
        std::vector<int> vec = {1, 2, 3, 4};
        ListNode *head = make_linked_list(vec);
        ListNode *result = linked_list_remove(head, 0, 4);
        REQUIRE(result == nullptr);
    }

    SECTION("Single-Element List") {
        std::vector<int> vec = {1};
        ListNode *head = make_linked_list(vec);
        ListNode *result = linked_list_remove(head, 0, 1);
        REQUIRE(result == nullptr);
    }
}
