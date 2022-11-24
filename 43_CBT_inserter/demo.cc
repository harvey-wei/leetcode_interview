#include <iostream>
#include <queue>
using namespace std;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class CBTInserter_my {
private:
    queue<TreeNode*> node_queue;
    TreeNode* root;

public:
    CBTInserter_my(TreeNode* root) {
        /* Note that the root is not nullptr. */
        this->root = root;
        node_queue.push(root);
    }

    int insert(int val) {
        int parent_val = 0;
        TreeNode* node_new = new TreeNode(val);

        while (!node_queue.empty())
        {
            TreeNode* parent = node_queue.front();

            /* Don't pop if left is nullptr. */
            /* Reminder: pop followed by push its child nodes
               pop means traverse the node/ print the node.
            */
            if (nullptr != parent->left)
            {
                node_queue.pop();
            }

            if (nullptr == parent->left)
            {
                parent->left = node_new;
                parent_val = parent->val;
                break;
            }
            else
            {
                node_queue.push(parent->left);
            }

            if (nullptr == parent->right)
            {
                parent->right = node_new;
                node_queue.push(parent->right);
                parent_val = parent->val;
                break;
            }
            else
            {
                node_queue.push(parent->right);
            }

            /* Optimize the conditional statements after ensuring the correctness. */
        }

        return parent_val;
    }

    TreeNode* get_root() {
        return root;
    }
};


class CBTInserter{
private:
    queue<TreeNode*> node_queue;
    TreeNode* root;

public:
    CBTInserter(TreeNode* root) {
        /* Note that the root is not nullptr. */
        this->root = root;
        node_queue.push(root);

        /* BFS to the last node who has both left and right child. */

        while (!node_queue.empty() && (nullptr != node_queue.front()->left)
                &&(nullptr != node_queue.front()->right))
        {
            TreeNode * parent = node_queue.front();
            node_queue.pop();
            node_queue.push(parent->left);
            node_queue.push(parent->right);
        }

        /* Invariant: Make sure node in the queue lacks left or right.*/
    }

    int insert(int val) {
        int parent_val = 0;
        TreeNode* node_new = new TreeNode(val);

        TreeNode* parent = node_queue.front();

        if (nullptr == parent->left)
        {
            parent->left = node_new;

            parent_val = parent->val;
        }
        else
        {
            parent->right = node_new;
            node_queue.pop();
            node_queue.push(parent->left);
            node_queue.push(parent->right);

            parent_val = parent->val;
        }

        return parent_val;
    }

    TreeNode* get_root() {
        return root;
    }
};
/**
 * Your CBTInserter object will be instantiated and called as such:
 * CBTInserter* obj = new CBTInserter(root);
 * int param_1 = obj->insert(val);
 * TreeNode* param_2 = obj->get_root();
 */
