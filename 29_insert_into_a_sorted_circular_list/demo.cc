#include <iostream>
using namespace std;

// Definition for a Node.
class Node {
public:
    int val;
    Node* next;

    Node() {}

    Node(int _val) {
        val = _val;
        next = NULL;
    }

    Node(int _val, Node* _next) {
        val = _val;
        next = _next;
    }
};

class Solution {
public:
    Node* insert_efficient(Node* head, int insertVal)
    {
        // case 1: empty list
        if (nullptr == head)
        {
            head = new Node(insertVal);
            head->next = head;

            return head;
        }

        // case 2: one-node list
        if (head->next == head)
        {
            Node* node_new = new Node(insertVal);
            head->next = node_new;
            node_new->next = head;

            return head;
        }

        // case 3: count of nodes >= 2
        Node* node_new = new Node(insertVal);
        Node* curr = head;
        Node* next = head->next;

        // Advance curr and next if not find the proper position and will not advance to the origin.
        // Think in advance!
        // subcase 1: insertVal lies between smallest and biggest.
        // subcase 2: insertVal is <= smallest or >= biggest. biggest->insertVal->smallest(next of
        // biggest)
        Node* biggest = head;
        while (!(curr->val <= insertVal && insertVal <= next->val)
                && next != head)
        {
            // advance
            curr = curr->next;
            next = next->next;

            // >= is required
            // 1 2 3 3 and insert 4 head = 3 we need the last 3
            if (curr->val >= biggest->val)
            {
                biggest = curr;
            }
        }

        if (curr->val <= insertVal && insertVal <= next->val)
        {
            curr->next = node_new;
            node_new->next = next;

        }
        else
        {
            /* subcase 2 */
            Node* smallest = biggest->next;
            biggest->next = node_new;
            node_new->next = smallest;
        }

        return head;
    }

    Node* insert(Node* head, int insertVal)
    {
        // case 1: empty list.
        if (nullptr == head)
        {
            head = new Node(insertVal);
            head->next = head;

            return head;
        }

        // case 2: one-node list
        if (head == head->next)
        {
            Node* new_node = new Node(insertVal);
            head->next = new_node;
            new_node->next = head;

            return head;
        }

        // case 3: count of nodes >= 2
        /* Step 1: find the smallest node and largest node. */
        Node* max_node = head;
        Node* min_node = head->next;

        while (true)
        {
            if (max_node->val > min_node->val)
            {
                break;
            }
            max_node = max_node->next;
            min_node = max_node->next;

            if (head == max_node) break;
            // advance
        }

        if (max_node->val == min_node->val
                || insertVal >= max_node->val
                || insertVal <= min_node->val)
        {
            // all nodes are of same values.
            Node * new_node = new Node(insertVal);
            max_node->next = new_node;
            new_node->next = min_node;

            return head;
        }

        // min_node < insertVal < max_node->val
        Node* curr = min_node;

        while (true)
        {
            if (curr->val <= insertVal && curr->next->val >= insertVal)
            {
                break;
            }

            // advance curr
            curr = curr->next;
        }

        Node * temp = curr->next;
        Node * node_new = new Node(insertVal);
        curr->next = node_new;
        node_new->next = temp;

        return head;
    }


    Node* insert_not_so_efficient(Node* head, int insertVal)
    {
        // case 1: empty list.
        if (nullptr == head)
        {
            head = new Node(insertVal);
            head->next = head;

            return head;
        }

        // case 2: one-node list
        if (head == head->next)
        {
            Node* new_node = new Node(insertVal);
            head->next = new_node;
            new_node->next = head;

            return head;
        }

        // case 3: count of nodes >= 2
        /* Step 1: find the smallest node and largest node. */
        Node* max_node = head;
        Node* min_node = head->next;

        while (true)
        {
            if (max_node->val <= insertVal && min_node->val >= insertVal)
            {
                Node * node_new = new Node(insertVal);
                max_node->next = node_new;
                node_new->next = min_node;

                return head;
            }

            if (max_node->val > min_node->val)
            {
                if (insertVal >= max_node->val
                        || insertVal <= min_node->val)
                {
                    // all nodes are of same values.
                    Node * new_node = new Node(insertVal);
                    max_node->next = new_node;
                    new_node->next = min_node;

                    return head;
                }
            }

            // advance.
            max_node = max_node->next;
            min_node = max_node->next;

            if (head == max_node)
            {
                // all nodes are of same values.
                Node * new_node = new Node(insertVal);
                max_node->next = new_node;
                new_node->next = min_node;

                return head;
            }
        }
    }
};
