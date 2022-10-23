#include <iostream>
#include <stack>
using namespace std;

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

void print(ListNode * head)
{
    ListNode * curr = head;
    while (nullptr != curr)
    {
        std::cout << curr->val << "->";
        curr = curr->next;
    }
    std::cout << "nullptr" << std::endl;
}

class Solution {
public:
    ListNode * bisect_list(ListNode *head)
    {
        /* Assume the input list has at least two nodes. Hence, we start at the first node! */
        /* Trick: Slow and fast can start at different nodes just image both of them walk from the
           dummy node whose next is head.
        */
        ListNode *slow = head;
        ListNode *fast = head->next;

        while (nullptr != fast->next && nullptr != fast->next->next)
        {
            slow = slow->next;
            fast = fast->next->next;
        }

        ListNode * right = nullptr;
        if (nullptr == fast->next)
        {
            /* Odd number of nodes in total! */
            right = slow->next;
            slow->next = nullptr;
        }
        else if (nullptr != fast->next && nullptr == fast->next->next)
        {
            /* Even number of nodes in total. */
            right = slow->next->next;
            slow->next = nullptr;
        }


        return right;
    }

    bool is_equal(ListNode * first, ListNode * second)
    {
        if (nullptr == first || nullptr == second)
        {
            return false;
        }

        while (nullptr != first && nullptr != second)
        {
            if (first->val != second->val)
            {
                return false;
            }
            else
            {
                // advance the first and second
                first = first->next;
                second = second->next;
            }
        }

        if (nullptr != first || nullptr != second)
        {
            return false;
        }
        else
        {
            return true;
        }
    }


    ListNode * reverse_list(ListNode * head)
    {
        /* Empty list */
        if (nullptr == head) return nullptr;

        ListNode *prev = nullptr;
        ListNode *curr = head;

        while (nullptr != curr)
        {
            ListNode * next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }

        return prev;
    }

    bool isPalindrome(ListNode* head) {
        if (nullptr == head) return false;

        if (nullptr == head->next) return true;

        /* The number of nodes in the list is in the range [1, 105] */
        ListNode * right = bisect_list(head);

        return is_equal(head, reverse_list(right));
    }

    bool isPalindrome_stack(ListNode *head)
    {
        if (nullptr == head) return false;

        if (nullptr == head->next) return true;

        stack<ListNode*> stack_nodes;
        ListNode *curr = head;
        while (nullptr != curr)
        {
            stack_nodes.push(curr);
            curr = curr->next;
        }

        curr = head;
        while (nullptr != curr)
        {
            const auto top_node =  stack_nodes.top();
            stack_nodes.pop();
            if (top_node->val != curr->val)
            {
                return false;
            }

            curr = curr->next;
        }

        return true;
    }
};


int main()
{
    ListNode head =  ListNode(1);
    append(&head, 0);
    append(&head, 1);
    print(&head);

    Solution sol;
    sol.isPalindrome(&head);
}
