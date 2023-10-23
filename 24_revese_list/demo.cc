struct ListNode
{
    int val;
    ListNode * next;

    ListNode() : val(0), next(nullptr) {} // default constr
    ListNode(int x) :val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution
{
    ListNode* reverseList(ListNode* head)
    {
        if (nullptr == head) return nullptr;

        /* Old head points to nullptr as tail. */
        ListNode * prev = nullptr;
        ListNode * curr = head;
        ListNode * next;

        while (nullptr != curr)
        {
            next = curr->next;
            curr->next = prev;

            /* update curr and next */
            prev = curr;
            curr = next;
        }
        /*  curr == nullptr but prev is the new head */

        return prev;
    }
};

int
main(int argc, char** argv)
{
    return 0;
}
