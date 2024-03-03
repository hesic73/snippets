#include <catch2/catch_test_macros.hpp>
#include "linked_list.hpp"
using namespace hsc_snippets;

TEST_CASE("linked_list.hpp", )
{
    SECTION("Test get_linked_list_length")
    {
        ListNode *head = new ListNode(1, new ListNode(2, new ListNode(3)));
        REQUIRE(get_linked_list_length(head) == 3);
        delete_linked_list(head); // Clean up
    }

    SECTION("Test make_linked_list")
    {
        std::vector<int> vec = {1, 2, 3};
        ListNode *head = make_linked_list(vec);
        REQUIRE(head->val == 1);
        REQUIRE(head->next->val == 2);
        REQUIRE(head->next->next->val == 3);
        delete_linked_list(head); // Clean up
    }

    SECTION("Test linked_list_to_vector")
    {
        ListNode *head = new ListNode(1, new ListNode(2, new ListNode(3)));
        std::vector<int> result = linked_list_to_vector(head);
        std::vector<int> expected = {1, 2, 3};
        REQUIRE(result == expected);
        delete_linked_list(head); // Clean up
    }
}
