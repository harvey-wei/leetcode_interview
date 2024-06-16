#include <iostream>
#include <unordered_map>
#include <unordered_set>
using namespace std;
/* Check the existence only. https://leetcode.com/problems/linked-list-cycle/ */
/* Where is the entry node?  https://leetcode.com/problems/linked-list-cycle-ii/ */

/* Definition for singly-linked list. */
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    /**
      * \method Floyd's Tortoise and Hare (Fast and slow pointers!)
      * \ref: congruence modulo
      * https://www.khanacademy.org/computing/computer-science/cryptography/modarithmetic/a/congruence-modulo
      */
    bool hasCycle_dummy(ListNode *head)
    {
        /* To handle the empty list. */
        ListNode dummy_node = ListNode(0);
        dummy_node.next = head;

        ListNode * tortorise = &dummy_node; /* 1 nodes per iteration */
        ListNode * hare = &dummy_node; /* 2 nodes per iteration */

        while (nullptr != hare->next && nullptr != hare->next->next)
        {
            if (tortorise != &dummy_node && hare == tortorise)
            {
                return true;
            }

            /* update the two guys */
            hare = hare->next->next;
            tortorise = tortorise->next;
        }

        return false;
    }

    bool hasCycle(ListNode *head)
    {
        /* Empty singly-linked list or single node list */
        if (nullptr == head || nullptr == head->next)
        {
            return false;
        }

        /* We can image they both go from a dummy node!*/
        ListNode *hare = head->next; /* fast pointer 2 nodes per iteration */
        ListNode *tortorise = head; /* slow pointer 1 node per iteration */

        while (nullptr != hare->next && nullptr != hare->next->next)
        {
            if (hare == tortorise)
            {
                return true;
            }

            /* update two pointers */
            hare = hare->next->next;
            tortorise = tortorise->next;
        }

        /* Might need to rectify */
        return false;
    }


    bool hasCycle_hashset(ListNode *head)
    {
        /*
           Time: O(N)
           Space: O(N)
        */

        /* Trick: take advantage of dummy node to deal with empty list. */
        ListNode dummy_node = ListNode(0);
        dummy_node.next = head;

        /* Node's address acts as a key. */
        unordered_set<ListNode *> visited_nodes;

        ListNode * node_ptr = &dummy_node;

        while (nullptr != node_ptr->next)
        {
            if (visited_nodes.end() != visited_nodes.find(node_ptr))
            {
                return true;
            }
            else
            {
                visited_nodes.insert(node_ptr);
            }

            /* update the node_ptr */
            node_ptr = node_ptr->next;
        }

        return false;
    }

    ListNode* detectCycle_hashset(ListNode *head)
    {
        /* Empty singly-linked list or one-node list can not have cycle. */
        if (nullptr == head || nullptr == head->next)
        {
            return nullptr;
        }

        unordered_set<ListNode *> visited_nodes;
        ListNode * node_ptr = head;
        visited_nodes.insert(node_ptr);

        while (nullptr != node_ptr->next)
        {
            /* Don't forget the else statement! */
            if (visited_nodes.end() != visited_nodes.find(node_ptr->next))
            {
                return node_ptr->next;
            }
            else
            {
                visited_nodes.insert(node_ptr->next);
            }

            /* update the node_ptr */
            node_ptr = node_ptr->next;
        }


        /* Might need to rectify. */
        return nullptr;
    }

    ListNode * detectCycle(ListNode *head)
    {
        /* Empty or one-node singly-linked list has no cycle. */
        if (nullptr == head || nullptr == head->next)
        {
            return nullptr;
        }

        /* Step 1: find the node where the slow and fast pointers meet for the first time. */
        /* Image these two pointers go from a dummy node. */
        ListNode * slow = head;
        ListNode * fast = head->next;
        ListNode * inter_node = nullptr;
        while (nullptr != fast->next && nullptr != fast->next->next)
        {
            if (slow == fast)
            {
                inter_node = slow;
                break;
            }

            /* update two pointers */
            slow = slow->next;
            fast = fast->next->next;
        }

        if (nullptr == inter_node)
        {
            /* No cycle! */
            return nullptr;
        }

        /* Step 2: count the number of cycle nodes. C nodes */
        int cycle_node_cnt = 1;
        ListNode * node_ptr = inter_node;
        while (inter_node != node_ptr->next)
        {
            cycle_node_cnt += 1;
            node_ptr = node_ptr->next;
        }

        /* Step 3:  Cth from the entrance like Cth from the end. front and rear pointers at the
           same speed.
           Expand the cyclic list:
           1->2->3->|4->5->6|->4->5->6|->4......
                     rear      front (at the same speed but at positions with C nodes apart)
        */
        ListNode * rear = head;
        ListNode * front = head;
        for (int i = 0; i < cycle_node_cnt; ++i)
        {
            front = front->next;
        }

        while (front != rear)
        {
            front = front ->next;
            rear = rear->next;
        }

        return front;
    }

    ListNode * detectCycle_mod(ListNode *head)
    {
        /* Empty or one-node singly-linked list has no cycle. */
        if (nullptr == head || nullptr == head->next)
        {
            return nullptr;
        }

        /* Step 1: find the node where the slow and fast pointers meet for the first time. */
        /* Image these two pointers go from a dummy node. */
        ListNode * slow = head;
        ListNode * fast = head->next;  // Must have distance diff even in the
        ListNode * inter_node = nullptr;
        while (nullptr != fast->next && nullptr != fast->next->next)
        {
            if (slow == fast)
            {
                inter_node = slow;
                break;
            }

            /* update two pointers */
            slow = slow->next;
            fast = fast->next->next;
        }

        if (nullptr == inter_node)
        {
            /* No cycle! */
            return nullptr;
        }

        /* Key observation:
           when the slow and fast pointer meets for the first time.
          (|f| - |L|) - (|s| - |L|) = |f| - |s| = C and |f| = 2|s| -> |s| = C
          with L as the count of nodes between head and entrance, exclusive.
          That is, slow pointer has traversed exactly the same number nodes as cycle has.
          Like but not the same Cth from end!!
        */

        /*
          Don't forget work an example by hand!
          Dummy node is the starting node!
          Hence, front and rear have C nodes in the difference of total steps.
          1-2-3-|4-5-6|-|4-5-6|
                 r       f
        */
        ListNode * front = inter_node;
        ListNode dummy_node = ListNode(0);
        dummy_node.next = head;
        ListNode * rear = &dummy_node;

        while (front != rear)
        {
            front = front->next;
            rear = rear->next;
        }

        return front;
    }
};

int
main()
{

    return 0;
}
