#include <iostream>
#include <vector>
#include <stack>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

struct CallStackNode
{
    ListNode* node;
    ListNode* left;
    ListNode* right;

    CallStackNode(ListNode* _node = nullptr, ListNode* _left = nullptr, ListNode* _right = nullptr)
        : node(_node), left(_left), right(_right)
    {}
};

class Solution {
public:
    /**
      * \brief Find the middle node and break the list.
      * \method Fast and slow pointers.
      */
    ListNode* split(ListNode* head)
    {
        /* At least two nodes. */
        ListNode* fast = head->next;
        ListNode* slow = head;

        while (fast != nullptr && fast->next != nullptr)
        {
            slow = slow->next;
            fast = fast->next->next;
        }

        /* If there are only two nodes, then slow == head. Hence, we needs to return slow->next. */
        ListNode* second_head = slow->next;
        slow->next = nullptr;  // break the list into half

        return second_head;
    }

    ListNode* merge(ListNode* head_one, ListNode* head_two)
    {
        /* dummy_node.next == new head */
        ListNode dummy_node = ListNode(0);
        ListNode* curr = &dummy_node;

        while (head_one != nullptr && head_two != nullptr)
        {
            if (head_one->val < head_two->val)
            {
                curr->next = head_one;
                head_one = head_one->next;
            }
            else
            {
                curr->next = head_two;
                head_two = head_two->next;
            }

            curr = curr->next;
            curr->next = nullptr;
        }

        curr->next = head_one != nullptr ? head_one : head_two;

        return dummy_node.next;
    }

    ListNode* sortList_iter(ListNode* head)
    {
        if (nullptr == head || nullptr == head->next)
        {
            return head;
        }

        /* step 1: construct the recursion tree. */
        /* step 2: post-order traversal. */

        return nullptr;
    }

    ListNode* sortList(ListNode* head) {
        /* Base case: empty or one-node list. */
        if (nullptr == head || nullptr == head->next)
        {
            return head;
        }

        ListNode* head_one = head;
        ListNode* head_two = split(head);  // middle node

        head_one = sortList(head_one);
        head_two = sortList(head_two);

        return merge(head_one, head_two);
    }
};


int main()
{
    return 0;
}
