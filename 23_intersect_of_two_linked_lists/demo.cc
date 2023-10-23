/**
 * Definition for singly-linked list.
 */
 struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(NULL) {}
 };

class Solution {
public:
    ListNode* get_cycle_entrance(ListNode* head)
    {
        /* Empty list or singleton list has no cycle! */
        if (nullptr == head || nullptr == head->next)
        {
            return nullptr;
        }

        /**
         * a = # of edges from head to the entrance
         * c = # of edges of the cycle
         * b = # of edges from entrance to the first meeting node
         * Meeting condition for hare and tortoise:
         * hare runs 2 edges per iteration while tortoise runs 1 edge per iteration
         * a + b + kc = 2(a + b) => a + b = kc
         */

        /* Imagine both hare and tortoise start going from a dummy head. */
        ListNode dummy = ListNode(0);
        dummy.next = head;
        ListNode* hare = head->next; // two edges from dummy head
        ListNode* tortoise = head; // one edge from dummy head

        /* Walk until hare and tortoise meets for the first time! */
        while (nullptr != hare && nullptr != hare->next && hare != tortoise)
        {
            hare = hare->next->next;
            tortoise = tortoise->next;

            /* if (hare == tortoise) */
            /* { */
            /*     break; */
            /* } */
        }

        if (nullptr == hare || nullptr == hare->next)
        {
            /* no cycle */
            return nullptr;
        }

        /* hare == tortoise */
        /* reset the hare to head */
        /* tortoise is b edges away from the entrance while hare is a edges away from entrance */
        /* a + b = c infers that they will coincide at the entrance if they walk one edge per
           iteration
         */
        hare = &dummy;
        while (hare != tortoise)
        {
            hare = hare->next;
            tortoise = tortoise->next;
        }

        return hare;
    }

    ListNode *getIntersectionNode_(ListNode *headA, ListNode *headB) {
        if (nullptr == headA || nullptr == headB)
        {
            return nullptr;
        }

        /* Join the tail of list A to the start of the list B. */
        ListNode* node = headA; // not nullptr

        /* Null node means next node of the end of singly linked list! */
        while (nullptr != node->next)
        {
            node = node->next; // node should not be Null.
        }

        /* node is the tail node->next == Null*/
        /* Set node->next to headB */
        node->next = headB;

        /* ERROR: linked structure was modified. */
        return get_cycle_entrance(headA);
    }

    void get_length_of_list(ListNode* head, int& len)
    {
        if (nullptr == head)
        {
            len = 0;
            return;
        }

        ListNode* node = head;
        len = 0;

        while (nullptr != node->next)
        {
            node = node->next;
            ++len;
        }

        return;

    }

    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB)
    {
        if (nullptr == headA || nullptr == headB)
        {
            return nullptr;
        }

        int len_a, len_b, len_diff;
        get_length_of_list(headA, len_a);
        get_length_of_list(headB, len_b);

        ListNode* ptr_longer;
        ListNode* ptr_shorter;

        if (len_a > len_b)
        {
            ptr_longer = headA;
            ptr_shorter = headB;
            len_diff = len_a - len_b;
        }
        else
        {
            ptr_longer = headB;
            ptr_shorter = headA;
            len_diff = len_b - len_a;
        }


        for (int i = 0; i < len_diff; ++i)
        {
            ptr_longer = ptr_longer->next;
        }

        while (nullptr != ptr_longer && nullptr != ptr_shorter && ptr_longer != ptr_shorter)
        {
            ptr_longer = ptr_longer->next;
            ptr_shorter = ptr_shorter->next;
        }

        if (nullptr == ptr_longer || nullptr == ptr_shorter)
        {
            return nullptr;
        }

        return ptr_longer;
    }
};

int
main()
{
    return 0;
}
