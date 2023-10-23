struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* reverse_list(ListNode* head)
    {
        if (nullptr == head)
        {
            return nullptr;
        }

        ListNode* prev = nullptr;
        ListNode* curr = head;
        ListNode* next;

        while (nullptr != curr)
        {
            /* change the next of curr to its prev */
            next = curr->next; // store the odd value before modification.
            curr->next = prev;

            /* update prev, curr, and next */
            prev = curr;
            curr = next;
        }

        return prev;
    }

    void reorderList(ListNode* head)
    {
        /* head is guaranteed to be non-empty. */
        /* Step 1: Find the middle node of the linked list. */
        ListNode dummy = ListNode(0, head);

        ListNode* fast = &dummy;
        ListNode* slow = &dummy;

        while (nullptr != fast->next && nullptr != fast->next->next)
        {
            /* update fast and slow */
            fast = fast->next->next;
            slow = slow->next;
        }

        /* fast->next == nullptr means even-lengthed list. */
        /* fast->next->next == nullptr means odd-lengthed list. */
        /**
         * dummy->1->2->3->4>5->6
         * fast: 2, 4, 6
         * slow: 1, 2, 3
         * 6 and 3 are desired.
         */
        /**
         * dummy->1->2->3->4->5
         * fast: 2, 4
         * slow: 1, 2
         * move both fast and slow one more step
         * fast: 5
         * slow: 3
         */

        if (nullptr != fast->next)
        {
            /* odd-length */
            slow = slow->next;
        }

        ListNode* head_a = head;
        ListNode* head_b = slow->next;
        slow->next = nullptr;

        head_b = reverse_list(head_b);

        ListNode dummy_result = ListNode();
        ListNode* dummy_res_ptr = &dummy_result;

        while (nullptr != head_a)
        {
            dummy_res_ptr->next = head_a;
            head_a = head_a->next;

            dummy_res_ptr->next->next = head_b;
            if (nullptr != head_b) head_b = head_b->next;

            dummy_res_ptr = dummy_res_ptr->next->next;
        }

        head = dummy_result.next;
        dummy_result.next = nullptr;

        return;

    }
};


int
main(int argc, char** argv)
{
    return 0;
}
