#include <iostream>
#include <vector>
#include <stack>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    /*
       https://leetcode.com/problems/binary-tree-inorder-traversal/solution/
    */
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> result;
        int a = 2;

        return result;
    }

    vector<int> postorderTraversal_recur()
    {
        vector<int> result;

        return result;
    }

    vector<int> postorderTraversal(TreeNode* root)
    {
        vector<int> result;

        TreeNode * curr = root;

        /* The previous traversed right sub-tree. */
        TreeNode * prev = nullptr; /* TODO: revise?*/

        stack<TreeNode*> stack_tree;
        /*
           push curr into stack
           pop means traversed!
           top is to check the parent node (a nearest sub-tree contains the left and right
           sub-trees.)
           Don't need to maintain a hash-table to track whether the node is visited!
        */
        while (nullptr != curr || !stack_tree.empty())
        {
            /* Walk left down to the (sub)-tree. */
            while (nullptr != curr)
            {
                stack_tree.push(std::move(curr));
                curr = curr->left;
            }

            /* The parent of the leaf-node/tree. */
            curr = stack_tree.top();

            if (nullptr == curr->right || prev == curr->right)
            {
                /* The right sub-tree is completely popped!
                   We need pop and then top again.
                */
                stack_tree.pop();
                result.push_back(std::move(curr->val));
                prev = curr;
                curr = nullptr;
            }
            else
            {
                /* walk the right sub-tree. */
                curr = curr->right;
            }
        }

        return result;
    }

    /*
       https://leetcode.com/problems/binary-tree-preorder-traversal/
    */
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> result;

        return result;
    }

    /*
       https://leetcode.com/problems/binary-tree-level-order-traversal/solution/
    */
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> result;

        return result;
    }
};



int main()
{

    return 0;
}
