#include <iostream>
struct ListNode
{
    int val;

    /* Singly linked list. */
    ListNode* next;

    ListNode() : val(0), next(nullptr){}
    ListNode(int x) : val(x), next(nullptr){}
    ListNode(int x, ListNode* next) : val(x), next(next){}
};

class Solution {
public:
    ListNode* append_naive(ListNode* head, int val)
    {
        if (nullptr == head)
        {
            /* case 1: head is nullptr. */
            /* head is changed! */
            head = new ListNode(val);
        }
        else
        {
            /* case 2: head is not nullptr! */
            /* head remains the same! */
            ListNode* node = head;

            while (nullptr != node->next)
            {
                node = node->next;
            }

            /* node->next == nullptr means node is now pointing to tail. */
            node->next = new ListNode(val);
        }

        return head;
    }

    ListNode* append(ListNode* head, int val)
    {
        ListNode dummy = ListNode(0, head);

        ListNode* node = &dummy;

        /* If head is nullptr, the below while loop is skipped! */
        while (nullptr != node->next)
        {
            node = node->next;
        }

        node->next = new ListNode(val);

        /* Don't forget to return the head! */
        return dummy.next;
    }

    ListNode* removeNthFromEnd(ListNode* head, int n)
    {
        // We need to locate the (n + 1)th node from the end.
        /* Handle the empty list by introducing dummy node pointing to the current head! */
        ListNode dummy = ListNode(0, head);

        ListNode* front = &dummy;
        ListNode* back = &dummy;

        /* Assume # of nodes >= n */
        /* n >= 1*/
        for (int i = 0; i < n; ++i)
        {
            back = back->next;
        }

        /* [front, back] has n + 1 nodes. */
        /* front could be the dummy */

        while (nullptr != back->next)
        {
            front = front->next;
            back = back->next;
        }

        // set n to 2 to determine.
        /* back is the end and front points to the (n + 1)th node from the end*/
        /* delete nth from the end by change the next of (n+1)the from the end*/
        ListNode * nth_node = front->next;
        front->next = front->next->next;
        delete nth_node;

        return dummy.next;
    }
};


int
main(int argc, char** argv)
{
    return 0;
}
