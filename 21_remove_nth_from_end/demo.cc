#include <iostream>

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode* append_naive(ListNode *head, const int &val)
{
    /* empty */
    if (nullptr == head)
    {
        /* You need to release by yourself. Hence, you need call new! */
        head = new ListNode(val);
    }

    /* walk to the end node whose next is nullptr */
    /* loop pointer should have local scope in this function block. */
    ListNode * node_ptr = nullptr;
    node_ptr = head;

    while (nullptr != node_ptr->next)
    {
        node_ptr = node_ptr->next;
    }

    node_ptr->next = new ListNode(val);

    return head;
}

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

/** Note that val is not necessarily existent in the singly-linked list.
  * Only delete the first occurrence of the value.
  */
ListNode * remove_naive(ListNode *head, const int &val)
{
    /* If the list is empty, return itself. */
    if (nullptr == head)
    {
        return head;
    }

    /* Check to see if the head's value == val. */
    if (val == head->val)
    {
        return nullptr;
    }

    ListNode * node_ptr = head;
    while (nullptr != node_ptr->next)
    {
        if (val == node_ptr->next->val)
        {
            ListNode * temp = node_ptr->next->next;
            delete node_ptr->next;
            node_ptr->next = temp;
            break;
        }

        /* update loop pointer*/
        node_ptr = node_ptr->next;
    }

    return head;

}

ListNode * remove(ListNode *head, const int &val)
{
    ListNode dummy_node = ListNode(0, head);

    /* Traverse the dummy list from dummy_node to end node and search for the val. */
    ListNode * node_ptr = &dummy_node;

    while (nullptr != node_ptr->next)
    {
        if (val == node_ptr->next->val)
        {
            ListNode * temp = node_ptr->next->next;
            delete node_ptr->next;
            node_ptr->next = temp;

            /* We only delete the first occurrence of the val. */
            break;
        }
        else
        {
            node_ptr = node_ptr->next;
        }
    }

    return dummy_node.next;
}


class Solution {
public:
    /* The number of nodes in the list is sz.
    1 <= sz <= 30
    0 <= Node.val <= 100
    1 <= n <= sz
    */
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode dummy_node = ListNode(0, head);

        /* Assume list is not empty! */
        ListNode * front = &dummy_node;
        ListNode * rear = &dummy_node;

        /* n <= sz ensures front will never reach the end.
           Hence, we use for loop to count the number of step front pointer goes.
        */
        for (int i = 0; i < n; ++i)
        {
            front = front->next;
        }

        while (nullptr != front->next)
        {
            front = front->next;
            rear = rear->next;
        }

        ListNode * temp = rear->next->next;
        delete rear->next;
        rear->next = temp;

        return dummy_node.next;
    }
};
int main()
{
    return 0;
}
