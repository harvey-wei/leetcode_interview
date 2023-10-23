/**
 * Definition for singly-linked list.
 * \ref https://leetcode.com/problems/linked-list-cycle-ii/editorial/
 */

struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    /* Image the cycle as a circular track. */
    bool hasCycle(ListNode *head)
    {
        /* Empty or singleton linked list implies no cycle. */
        /* Short-circuiting is mandated by C++ standard! */
        if (nullptr == head || nullptr == (head->next))
        {
            return false;
        }

        /* dummy -> head -> (head->next) */
        /* Image both fast and slow go from dummy node. */
        ListNode* fast = head->next;
        ListNode* slow = head;

        /* How to determine the termination condition? */
        /* Update fast and slow and then see when to stop! */
        /* Check initial iteration and terminal iteration. */
        while (nullptr != fast && nullptr != fast->next)
        {
            /* Check whether slow == fast */
            if (slow == fast) return true;

            /* update fast and slow pointers */
            /* fast and fast->next can not be nullptr! */
            fast = fast->next->next; // two nodes per iteration
            slow = slow->next; // one node per iteration
        }

        return false;
    }


    /**
     * Definition:
     * a = # of edges from head to the node where the cycle begins.
     * c = # of edges in the cycle, namely the length of the cycle.
     * b = # of edges from the entrance to the first meeting point.
     * The condition for slow and fast pointers to meet when starting from a virtual dummy node.
     * Lfast - Lslow = kc
     * Lfast = 2Lslow since fast pointers runs twice as fast as slow pointer.
     * => Lslow = kc
     */

    ListNode *detectCycle(ListNode *head)
    {
        /* No cycle for empty and singleton singly linked list. */
        if (nullptr == head || nullptr == head->next)
        {
            return nullptr;
        }

        ListNode* hare = head;
        ListNode* tortoise = head;

        /**
         * Move hare two steps and tortoise one step per iteration until they meet
         * if cycle exists.
         * null next means end of the singly linked list.
         */
        while (nullptr != hare && nullptr != hare->next)
        {
            tortoise = tortoise->next;
            hare = hare->next->next;

            if (tortoise == hare)
            {
                break;
            }
        }

        /* Check if there are cycle! */
        if (nullptr == hare || nullptr == hare->next)
        {
            /* The above while loop is terminated due to tail of lilst. Hence, no cycle. */
            return nullptr;
        }

        /* tortoise and hare meet the node which is b nodes away from the entrance of the cycle.*/
        /* Lslow = a + b = kc if tortoise walks another a edges, it will hit the entrance. */
        /* Reset hare to head and move it one step. It will meet tortoise at the entrance since*/
        /* they both walks a edges! */

        hare = head;

        while (hare != tortoise)
        {
            hare = hare->next;
            tortoise = tortoise->next;
        }

        return hare;
    }

};

int
main()
{

    return 0;
}
