/*
// Definition for a Node.
*/

class Node
{
public:
    int val;
    Node* next;

    Node() {}

    Node(int _val) {
        val = _val;
        next = nullptr;
    }

    Node(int _val, Node* _next) {
        val = _val;
        next = _next;
    }
};


class Solution {
public:
    Node* insert(Node* head, int insertVal)
    {
        // case 1: empty list, create a new one
        if (nullptr ==  head)
        {
            head = new Node(insertVal);
            head->next = head;
            return head;
        }

        // case 2: single node.
        if (head->next == head)
        {
            Node* temp = new Node(insertVal);
            temp->next = head;
            head->next = temp;

            return  head;
        }

        // case 3: >= 2 nodes.

        // Since we need to compare the insertVal with two adjacent nodes,
        // but we can not look back.
        // Option 1: two pointers: prev curr
        // OPtion 2: one pointer: curr and curr->next;
        Node* prev = head;
        Node* curr = head->next;

        bool is_inserted = false;
        do
        {
            if (prev->val <= insertVal && insertVal <= curr->val)
            {
                /* insertVal falls the range of [min, max] */
                /* prev <= curr*/
                is_inserted = true;
            }
            else if (prev->val > curr->val)
            {
                /* prev reaches max while curr reaches the min */
                if (insertVal >= prev->val || insertVal <= curr->val)
                {
                    is_inserted = true;
                }
            }

            if (is_inserted)
            {
                Node* temp = new Node(insertVal, curr);
                prev->next = temp;

                return head;;
            }

            prev = curr;
            curr = curr->next;
        }
        while(prev != head);

        // All values are the same. prev == head.
        prev->next = new Node(insertVal, curr);

        return head;
    }
};
