#include <iostream>
#include <queue>


using namespace std;

struct TreeNode
{
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(): val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x): val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* _left, TreeNode* _right): val(x), left(_left), right(_left) {}
};


class CBTInserter {
public:
    CBTInserter(TreeNode* root)
    {
        this->root = root;
        /* root should not be null */
        node_q.push(root);
        TreeNode* curr;

        /* BFS until meet a non-complete node whose misses left or right child. */
        /* BFS order matches the filling order of complete binary tree. */
        while (!node_q.empty() && nullptr != node_q.front()->left
                && nullptr != node_q.front()->right)
        {
            curr = node_q.front();
            node_q.pop();
            /* We must push left first and then right to match the Completeness Definition. */
            /* For queue, First in - First out. */
            node_q.push(curr->left);
            node_q.push(curr->right);
        }

        /* Now the front (oldest) node is not complete*/
    }

    int insert(int val)
    {
        /**
         * The key is to track the previous node who are the first one misses left or right node.
         * Assume we traverse the tree from top to bottom and left to right. (BFS)
         */
        TreeNode* parent = node_q.front();

        if (nullptr == parent->left)
        {
            /* Both left and right are missing. */
            parent->left = new TreeNode(val);
        }
        else
        {
            /* Left is not null but right is missing */
            parent->right = new TreeNode(val);
            node_q.pop();
            node_q.push(parent->left);
            node_q.push(parent->right);
        }

        // return parent value.
        return parent->val;
    }

    TreeNode* get_root()
    {
        return root;
    }

private:
    TreeNode* root;
    queue<TreeNode*> node_q;
};

/**
 * Your CBTInserter object will be instantiated and called as such:
 * CBTInserter* obj = new CBTInserter(root);
 * int param_1 = obj->insert(val);
 * TreeNode* param_2 = obj->get_root();
 */
