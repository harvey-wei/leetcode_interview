#include <iostream>
#include <stack>
using namespace std;

// Definition for a Node.
class Node {
public:
    int val;
    Node* prev;
    Node* next;
    Node* child;
};


// You can image child as left subtree, left as right substree
// prev is parent
// The goal is to do pre-order traversal
// Data abstraction and Find repetitive pattern.
// We need a dummy head to return the result
// We also need a prev pointer track the tail of the current result.
// We also need a curr poiter to tack the start of the remaining linked list.
// Node's address act as ID.

class Solution {
public:
    Node* flatten(Node* head)
    {
        if (nullptr == head) return head;
        Node dummy = Node();
        Node* prev;
        Node* curr;
        prev = &dummy;

        stack<Node*> nodes_stack;
        nodes_stack.push(head);

        while (!nodes_stack.empty())
        {
            /* Pop and push next and child. */
            curr = nodes_stack.top();
            nodes_stack.pop();

            prev->next = curr;
            curr->prev = prev;

            if (nullptr != curr->next)
            {
                nodes_stack.push(curr->next);
            }

            if (nullptr != curr->child)
            {
                nodes_stack.push(curr->child);

                // set child of curr to null
                curr->child = nullptr;
            }

            // update prev
            prev = curr;
        }
        // Detach the dummy head from the result.
        dummy.next->prev = nullptr;

        return dummy.next;
    }

    /* TODO: The problem can be reduced to pre-order tree traversal.
       Hence, morris traversal is the space-efficient choice.
    */
};

int main()
{
    return 0;
}
