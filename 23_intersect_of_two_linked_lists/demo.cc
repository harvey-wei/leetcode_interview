struct ListNode
{
    int val;
    ListNode* next;

    ListNode(int x): val(x), next(nullptr){}
};

class Solution_ {
public:
    ListNode *detectCycle(ListNode *head)
    {
        /* Empty or singleton list has no cycle. */
        if (nullptr == head || nullptr == head->next) return nullptr;

        /* Image both slow and fast walk from a dummy head. */
        ListNode* slow = head;
        ListNode* fast = head->next;

        /* Find the first meeting node. */
        bool has_cycle = false;
        while (nullptr != fast->next && nullptr != fast->next->next)
        {
            // check
            if (slow == fast)
            {
                has_cycle = true;
                break;
            }

            // update
            slow = slow->next;
            fast = fast->next->next;
        }

        if (!has_cycle) return nullptr;

        /*
         * fast_len = 2 slow_len, fast_len - slow_len = C
         * non_cyclic_len + entrance2meeting = C
         * Reset slow to the dummy head
         * Make slow and fast walk both one edge at a time
         * They will meet at the entrance
         */
        slow = head;
        fast = fast->next;

        while (slow != fast)
        {
            slow = slow->next;
            fast = fast->next;
        }

        return slow;
    }
};


class Solution {
public:
    int get_list_length(ListNode* const head)
    {
        if (nullptr == head) return 0;

        // We define the length as # of nodes.
        int len = 1;
        ListNode* curr = head;

        while (nullptr != curr->next)
        {
            curr = curr->next;
            ++len;
        }

        return len;
    }

    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB)
    {
        if (nullptr == headA || nullptr == headB) return nullptr;

        int len_A = get_list_length(headA);
        int len_B = get_list_length(headB);
        int diff = 0;

        ListNode* shorter;
        ListNode* longer;

        if (len_A > len_B)
        {
            diff = len_A - len_B;
            longer = headA;
            shorter = headB;
        }
        else
        {
            diff = len_B - len_A;
            longer = headB;
            shorter = headA;
        }

        for (int i = 0; i < diff; ++i)
        {
            longer = longer->next;
        }

        while (nullptr != shorter && nullptr != longer)
        {
            if (shorter == longer)
            {
                return shorter;
            }

            shorter = shorter->next;
            longer = longer->next;
        }

        return nullptr;
    }
};
