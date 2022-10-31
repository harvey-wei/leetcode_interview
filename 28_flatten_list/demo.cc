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


class Solution {
public:
    Node* flatten(Node* head) {
        stack<Node*> stack_nodes;
        Node* curr = head;

        while (nullptr != curr)
        {
            if (nullptr != curr->child && nullptr != curr->next)
            {
                stack_nodes.push(std::move(curr->next));
                curr->next = curr->child;
                curr->child = nullptr;
                curr->next->prev = curr;
                // update curr
                curr = curr->next;
            }
            else if (nullptr != curr->next)
            {
                // update curr
                curr = curr->next;
            }
            else if (nullptr != curr->child)
            {
                curr->next = curr->child;
                curr->child = nullptr;
                curr->next->prev = curr;

                // update curr
                curr = curr->next;
            }
            else
            {
                /* both child and next are nullptr. */
                if (!stack_nodes.empty())
                {
                    Node * top = stack_nodes.top();
                    stack_nodes.pop();
                    curr->next = top;
                    top->prev = curr;

                    // update curr
                    curr = top;

                }
                else
                {
                    curr = nullptr;
                }
            }
        }

        /* Might need to rectify. */
        return head;
    }

    /* TODO: The problem can be reduced to pre-order tree traversal.
       Hence, morris traversal is the space-efficient choice.
    */
};

int main()
{
    return 0;
}
