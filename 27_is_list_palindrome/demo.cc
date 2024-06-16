/**
 * Definition for singly-linked list.
 */


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
        if (nullptr == head) return nullptr;

        ListNode* prev = nullptr;
        ListNode* curr = head;
        ListNode* next = nullptr;

        while(nullptr != curr)
        {
            next = curr->next;
            curr->next = prev;

            // update curr and prev
            prev = curr;
            curr = next;
        }

        // curr == null
        return prev;
    }

    bool isPalindrome(ListNode* head)
    {
        /* Edge cases. */
        if (nullptr == head) return false;
        if (nullptr == head->next) return true;

        /**
         * We need the end node of first half. Hence, we start at a dummy head.
         * even: 1-2-3-4, we need 2 as the head of second half. slow == 2
         * odd:  1-2-3-4-5, we need 3, slow = 3
         * If we start at , for even, 3 is chonse, for odd 3 is chosen
         * While loop is over, fast->next == null ? can be used to tell apart even/odd.
         * Start from head or a dummy head?
         * fast can reach null or not
         */
        ListNode* slow = head;
        ListNode* fast = head->next;

        while (nullptr != fast && nullptr != fast->next)
        {
            slow = slow->next;
            fast = fast->next->next;
        }

        // For even: fast->next == nullptr
        // For odd: fast == nullptr

        ListNode* first = head;
        ListNode* second = slow->next;
        slow->next = nullptr;

        second = reverse_list(second);

        while (nullptr != first && nullptr != second)
        {
            if (first->val != second->val)
            {
                return false;
            }
            else
            {
                first = first->next;
                second = second->next;
            }
        }

        return true;
    }
};
