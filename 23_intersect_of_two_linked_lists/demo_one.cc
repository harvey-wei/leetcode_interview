#include <iostream>
#include <unordered_set>

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode * n) : val(x), next(n) {}
};

class Solution {
public:
    /*
       More solutions to the same problem:
       Use stack to traverse from the end after traversing from the start. (Last-in first-out!)
       Use hash set to walk list A and then check whether a node in list B exists in list A.
       Construct a cycle and find the entrance!
    */
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB)
    {
        ListNode dummy_node_a = ListNode(0);
        ListNode dummy_node_b = ListNode(0);

        dummy_node_a.next = headA;
        dummy_node_b.next = headB;

        /* No empty list. */
        ListNode * curr_node = &dummy_node_a;
        int len_a = 0;
        while (nullptr != curr_node->next)
        {
            /* update the loop pointer */
            curr_node = curr_node->next;
            ++len_a;
        }

        curr_node = &dummy_node_b;
        int len_b = 0;
        while (nullptr != curr_node->next)
        {
            curr_node = curr_node->next;
            ++len_b;
        }

        if (0 == len_a && 0 == len_b)
        {
            return nullptr;
        }

        /* The first nodes of them could also be the intersection! */
        ListNode * curr_node_a = &dummy_node_a;
        ListNode * curr_node_b = &dummy_node_b;

        if (len_a > len_b)
        {
            for (int i = 0; i < (len_a - len_b); ++i)
            {
                curr_node_a = curr_node_a->next;
            }
        }
        else
        {
            for (int i = 0; i < (len_b - len_a); ++i)
            {
                curr_node_b = curr_node_b->next;
            }
        }

        while (nullptr != curr_node_a->next && nullptr != curr_node_b->next)
        {
            if (curr_node_a->next == curr_node_b->next)
            {
                return curr_node_a->next;
            }
            else
            {
                curr_node_a = curr_node_a->next;
                curr_node_b = curr_node_b->next;
            }
        }

        return nullptr;
    }
};


int main()
{
    return 0;
}
