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
    ListNode* removeNthFromEnd(ListNode* head, int n)
    {
        ListNode dummy(0, head);

        ListNode* front = &dummy;
        ListNode* back = &dummy;

        /* Front walks n nodes in advance. */
        for (int i = 0; i < n; ++i)
        {
            front = front->next;
        }

        while (nullptr != front->next)
        {
            front = front->next;
            back = back->next;
        }

        /* back is the (n + 1)th node from  end. */
        ListNode* temp = back->next->next;
        delete back->next;
        back->next = temp;

        return dummy.next;
    }
};
