#include <iostream>


/**
 * Definition for singly-linked list.
 */
struct ListNode
{
     int val;
     ListNode *next;
     ListNode() : val(0), next(nullptr) {}
     ListNode(int x) : val(x), next(nullptr) {}
     ListNode(int x, ListNode *next) : val(x), next(next) {}
};


class Solution
{
public:
    ListNode* middleNode(ListNode* head)
    {
        /**
         * Odd-length: 1->2->3->4->5. 3 is middle node.
         * Even-length: 1->2->3->4->5->6. 4 is middle node. the head of the second half
         */
        if (nullptr == head)
        {
            return nullptr;
        }

        /* You can also start from a dummy head. */
        ListNode* slow = head;
        ListNode* fast = head;

        while (nullptr != fast && nullptr != fast->next)
        {
            slow = slow->next;
            fast = fast->next->next;
        }

        return slow;
    }
};
