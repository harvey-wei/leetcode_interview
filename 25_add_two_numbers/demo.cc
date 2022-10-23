#include <iostream>

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* reverse_list(ListNode *head)
    {
        ListNode * prev = nullptr;
        ListNode * curr = head;

        while (nullptr != curr)
        {
            ListNode * next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }

        /* Might need to rectify. */
        return prev;
    }

    /*
       The number of nodes in each linked list is in the range [1, 100].
    */
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
    {
        l1 = reverse_list(l1);
        l2 = reverse_list(l2);

        ListNode dummy = ListNode(0, nullptr);
        ListNode *curr = &dummy;

        int carry = 0;
        while (nullptr != l1 || nullptr != l2 || 0 != carry)
        {
            int s = (nullptr != l1 ? l1->val : 0) +
                    (nullptr != l2 ? l2->val : 0) + carry;
            carry = s / 10; // integer division

            /* To create a list and return it, you have dynamically allocate the memory for each
               node. */
            curr->next = new ListNode(s % 10);

            // update l1 and  l2 and curr
            l1 = nullptr != l1 ? l1->next : nullptr;
            l2 = nullptr != l2 ? l2->next : nullptr;
            curr = curr->next;
        }

        return reverse_list(dummy.next);
    }
};


int main()
{
    Solution sol;

    return 0;
}
