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
    ListNode* reverseList(ListNode* head)
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

        /* Don't forget to work an example by hand to clarify the boundary condition. */
        return prev;
    }
};
int main()
{
    return 0;
}
