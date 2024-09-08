#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <vector>

namespace hsc_snippets {
    struct ListNode {
        int val;
        ListNode *next;

        ListNode() : val(0), next(nullptr) {
        }

        explicit ListNode(int x) : val(x), next(nullptr) {
        }

        ListNode(int x, ListNode *next) : val(x), next(next) {
        }
    };

    /**
     * Calculates the length of a linked list.
     *
     * @param head A pointer to the head of the linked list.
     * @return The number of nodes in the linked list.
     */
    static int get_linked_list_length(ListNode *head) {
        int len = 0;
        while (head != nullptr) {
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
    static ListNode *make_linked_list(const std::vector<int> &v) {
        if (v.empty()) {
            return nullptr;
        }
        auto head = new ListNode;
        ListNode *prev = nullptr;
        auto it = v.begin();
        while (it != v.end()) {
            if (prev == nullptr) {
                head->val = *it;
                prev = head;
            } else {
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
    static std::vector<int> linked_list_to_vector(ListNode *head) {
        auto v = std::vector<int>{};
        while (head != nullptr) {
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
    static void linked_list_delete(ListNode *head) {
        if (head == nullptr) {
            return;
        }
        auto next = head->next;
        while (next != nullptr) {
            delete head;
            head = next;
            next = head->next;
        }
        delete head;
    }

    /**
     * Removes nodes from a linked list in the specified range.
     *
     * @param head Pointer to the head of the linked list.
     * @param begin The starting index of the range to remove nodes (inclusive).
     * @param end The ending index of the range to remove nodes (exclusive).
     * @return A pointer to the head of the modified linked list.
     */
    static ListNode *linked_list_remove(ListNode *head, size_t begin, size_t end) {
        if (head == nullptr || begin >= end) {
            // Nothing to remove
            return head;
        }

        ListNode dummy(0, head); // Create a dummy node to simplify edge cases
        ListNode *prev = &dummy;

        // Move `prev` to the node just before `begin`
        for (size_t i = 0; i < begin && prev->next != nullptr; ++i) {
            prev = prev->next;
        }

        ListNode *current = prev->next;

        // Remove nodes in range [begin, end)
        for (size_t i = begin; i < end && current != nullptr; ++i) {
            ListNode *temp = current;
            current = current->next;
            delete temp; // Free the removed node
        }

        // Connect the node before `begin` to the node at `end`
        prev->next = current;

        return dummy.next; // Return the new head, which is the next of dummy node
    }


    /**
     * Retrieves a pointer to the ith element in the linked list.
     *
     * @param head A pointer to the head of the linked list.
     * @param i The index of the element to retrieve.
     * @return A pointer to the ith element in the linked list. If the index is out of bounds, it returns nullptr.
     */
    static ListNode *get_linked_list_ith_node(ListNode *head, size_t i) {
        size_t current_index = 0;
        while (head != nullptr) {
            if (current_index == i) {
                return head;
            }
            head = head->next;
            current_index++;
        }
        return nullptr; // Index out of bounds
    }

    /**
     * Returns a pointer to the node after taking a specified number of steps in the linked list.
     *
     * @param head Pointer to the head of the linked list.
     * @param step The number of steps to take from the head (0-based).
     * @return A pointer to the node after the specified number of steps, or nullptr if out of bounds.
     */
    static ListNode *linked_list_next(ListNode *head, size_t step) {
        size_t i = 0;
        while (head != nullptr && i < step) {
            head = head->next;
            i++;
        }

        return head; // Returns nullptr if step is out of bounds
    }
}

#endif // LINKED_LIST_H
