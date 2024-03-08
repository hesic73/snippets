#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <vector>

namespace hsc_snippets
{

    struct ListNode
    {
        int val;
        ListNode *next;

        ListNode() : val(0), next(nullptr) {}

        explicit ListNode(int x) : val(x), next(nullptr) {}

        ListNode(int x, ListNode *next) : val(x), next(next) {}
    };

    /**
     * Calculates the length of a linked list.
     *
     * @param head A pointer to the head of the linked list.
     * @return The number of nodes in the linked list.
     */
    int get_linked_list_length(ListNode *head)
    {
        int len = 0;
        while (head != nullptr)
        {
            len += 1;
            head = head->next;
        }
        return len;
    }

    /**
     * Creates a linked list from a vector of integers.
     *
     * @param v A reference to a vector of integers from which to create the linked list.
     * @return A pointer to the head of the newly created linked list.
     */
    ListNode *make_linked_list(const std::vector<int> &v)
    {
        if (v.empty())
        {
            return nullptr;
        }
        auto head = new ListNode;
        ListNode *prev = nullptr;
        auto it = v.begin();
        while (it != v.end())
        {
            if (prev == nullptr)
            {
                head->val = *it;
                prev = head;
            }
            else
            {
                prev->next = new ListNode(*it);
                prev = prev->next;
            }
            it = std::next(it);
        }

        return head;
    }

    /**
     * Converts a linked list to a vector of integers.
     *
     * @param head A pointer to the head of the linked list.
     * @return A vector of integers containing the values of the linked list nodes.
     */
    std::vector<int> linked_list_to_vector(ListNode *head)
    {
        auto v = std::vector<int>{};
        while (head != nullptr)
        {
            v.push_back(head->val);
            head = head->next;
        }
        return v;
    }

    /**
     * Deletes all nodes in a linked list to free memory.
     *
     * @param head A pointer to the head of the linked list to be deleted.
     */
    void delete_linked_list(ListNode *head)
    {
        if (head == nullptr)
        {
            return;
        }
        auto next = head->next;
        while (next != nullptr)
        {
            delete head;
            head = next;
            next = head->next;
        }
        delete head;
    }
}

#endif // LINKED_LIST_H
