struct ListNode
{
    int val;
    ListNode* next;

    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};



class Solution {
public:
    bool hasCycle(ListNode *head) {
        /* Special case: empty or singleton linked list has no cycle. */
        if (nullptr == head || nullptr == head->next)
        {
            return false;
        }

        /* There must have a distance in the cyclic path. */
        /* Hence, slow and fast should not start at the same node*/

        // slow and fast start outside of head
        ListNode* slow = head; // Move one step at a time.
        ListNode* fast = head->next; // Move two steps at a time.

        while (nullptr != fast->next && nullptr != fast->next->next)
        {
            if (slow == fast)
            {
                return true;
            }

            // update slow and fast
            slow = slow->next;
            fast = fast->next->next;
        }

        return false;
    }


    bool hasCycle_(ListNode* head)
    {
        if (nullptr == head || nullptr == head->next)
        {
            /* Empty or one-node singly list has no cycle. */
            return false;
        }

        ListNode* slow = head;
        ListNode* fast = head;

        while (nullptr != fast->next && nullptr != fast->next->next)
        {
            // update
            slow = slow->next;
            fast = fast->next->next;

            // check
            if (slow == fast) return true;
        }

        return false;
    }



    ListNode* detectCycle(ListNode* head)
    {

    }
};
