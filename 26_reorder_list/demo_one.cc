#include <iostream>


struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode * append(ListNode *head, const int &val)
{
    /* using a dummy node to point to head even if head is nullptr.
       If the list is empty, the dummy node is the end node whose next is nullptr.
    */
    ListNode dummy_node = ListNode(0, head);
    ListNode * node_ptr = &dummy_node;

    /* Walk from dummy_node to the end node. */
    while (nullptr != node_ptr->next)
    {
        node_ptr = node_ptr->next;
    }

    node_ptr->next = new ListNode(val);

    return dummy_node.next;
}

class Solution {
public:
    /**
      * \ The general method of solving algorithmic problems.
      * Pillars of computational thinking:
      * 0. Work an example by hand recursively!
      * 1. Decomposition. Break a complex problem into more manageable sub-problems and fuse
      * the solutions of these sub-problems into the solution to the complex problem.
      * 2. Pattern Recognition.
      * Intra-problem similarities -> repetitive -> for or while loop.
      * Inter-problem similarities -> subroutine for efficient code reusability.
      * Branching structures -> case by case analysis.
      * 3. Data representation and abstraction. What characteristics are important and what are not
      * important -> use what kind of data structure (static or dynamic or double pointers) to keep
      * track of them.
      * 4. Algorithm. Should be as detailed as possible such that you can write out the step-by-step
      * instructions of how to solve the problem.
      *
      * For each sub-problem, we adopt the seven-step approach:
      * step 1: Work an example by hand using a pencil and a piece of paper.
      * step 2: Write down exactly what you did in the step 1.
      * step 3: Generalize your steps from 2 **to algorithm** by pattern (repetitive and branching) recognition and data abstraction
      * If you have trouble with this step, you should repeat steps 1 and 2 on different instances
      * of the problem.
      * step 4: Test your algorithm by applying it to a new instance of the problem.
      * Finding mistakes before translating to code avoids wasting time.
      * You can go back to Step 3 if you identify a **generalization mistake**
      * *Note that steps 1-4 can be done with pencil and paper and are independent of language.*
      *
      * step 5: Translate to code.
      * What if any of the lines in your algorithm do not immediately translate into one or two
      * lines of code? (If you struggle to solve a problem, just break it down and adhere to the
      * principle "from general to specific"
      * They should be abstracted out into their own function: make a good name for the function,
      * call it here, and make yourself a note about what it does. After you finish translating
      * this algorithm, go implement that function. That function is itself a programming problem
      * (for which you wrote the problem statement), so use The Seven Steps.
      * step 6: Test. Even if you have a correct algorithm, you could still have made
      * mistakes in the implementation in code,
      * step 7. Debug. Debugging is the act of fixing bugs you identified in the testing stage.
      * Once you’ve identified a problem, you need to figure out if the issue is with the algorithm
      * or code implementation and go back to Step 3 (generalization to algorithm) or Step 5
      * (translation to code),
      * Remember the difference between algorithm and code!
      *
      * \method
      * step 1: find the middle node of the list using hare and tortoise pointers.
      *         For even-number long  list, left and right half are of the same length.
      *         For odd-number long list, left half has one more node than the right half.
      * step 2: reverse the second list.
      * step 3: join the nodes from the above two lists alternately.
      */


    /**
      * 1-2-3-4-5-6 (even number of nodes)
      * s1: 1-2-3 4-5-6
      * s2: 1-2-3 6-5-4
      * s3: 1-6-2-5-3-5
      *
      * 1-2-3-4-5 (odd number of nodes)
      * s1: 1-2-3 4-5
      * s2: 1-2-3 5-4
      * s3: 1-5-2-4-3
      */

    ListNode * find_mid_node(ListNode *head)
    {
        /* Empty list */
        if (nullptr == head) return nullptr;

        /* List is of >= 1 nodes */
        ListNode * slow = head;
        ListNode * fast = head;

        /*
           examples:
           1: s==f 1 correct
           1-2: s == f 1 correct
           1-2-3-4: s == 2 and f == 3 correct
           1-2-3-4-5 s == 3 and f == 5 correct
           loop invariant for node_cnt >= 2
        */
        while (nullptr != fast->next && nullptr != fast->next->next)
        {
            slow = slow->next;
            fast = fast->next->next;
        }

        std::cout << "The end of left half list: " << slow->val << std::endl;
        /* Return the end of the left half of the list. */
        return slow;
    }

    ListNode * reverse_list(ListNode *head)
    {
        /* Empty list */
        if (nullptr == head) return nullptr;

        ListNode * prev = nullptr;
        ListNode * curr = head;

        while (nullptr != curr)
        {
            ListNode *next = curr->next;
            curr->next = prev;

            /* update double pointers */
            prev = curr;
            curr = next;
        }

        std::cout << "The head of reversed list: " << prev->val << std::endl;
        /* return the head of the reversed list. */
        return prev;
    }

    ListNode * concat_lists(ListNode *left, ListNode *right)
    {
        /* Left list has the same number of nodes or exactly one more node than the right list. */
        ListNode *head = left;
        /* Either of them is empty. */
        if (nullptr == left || nullptr == right) return nullptr;

        while (nullptr != left && nullptr != right)
        {
            ListNode * next_left = left->next;

            ListNode * next_right = right->next;

            left->next = right;
            right->next = next_left;

            left = next_left;
            right = next_right;
        }

        return head;
    }

    void reorderList(ListNode* head)
    {
        ListNode * end_of_left = find_mid_node(head);
        ListNode * right = end_of_left->next;
        end_of_left->next = nullptr;

        right = reverse_list(right);

        concat_lists(head, right);
    }
};

int main()
{
    ListNode head(1);
    ListNode *head_ptr = &head;
    head_ptr = append(&head, 2);
    head_ptr = append(&head, 3);
    head_ptr = append(&head, 4);

    ListNode * curr = &head;
    while (nullptr != curr)
    {
        std::cout << curr->val << "->";
        curr = curr->next;
    }
    std::cout << "nullptr" << std::endl;

    Solution sol;
    sol.reorderList(head_ptr);

    return 0;
}
