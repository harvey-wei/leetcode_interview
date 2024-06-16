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
    public:
    ListNode* reverseList(ListNode* head)
    {
        /* We reset the curr->next to prev */
        /* Move prev curr to tail. */
        /* For the head, we reset head->next to null*/
        ListNode* prev = nullptr;
        ListNode* curr = head;
        ListNode* next;

        while (nullptr != curr)
        {
            next = curr->next;
            curr->next = prev;

            prev = curr;
            curr = next;
        }

        return prev;
    }
};

int
main(int argc, char** argv)
{
    return 0;
}
