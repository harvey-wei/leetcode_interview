#include <iostream>
 struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode() : val(0), left(nullptr), right(nullptr) {}
     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };

// https://leetcode.com/problems/binary-tree-level-order-traversal/editorial/
class Solution {
public:
    TreeNode* pruneTree(TreeNode* root)
    {
        /**
         * One tree can be delete if and only if its root == 0 and its left and right subtree are
         * deleted.
         * Hence, we need to check left and right, and then current node. -> post order
         * bottom to up , left to right
         * nullptr can be viewes as deleted.
         * This recusive funtion return the root which might be set null.
         */

        if (nullptr == root)
        {
            return nullptr;
        }

        /* post-order traversal */
        root->left = pruneTree(root->left);
        root->right = pruneTree(root->right);

        if (0 == root->val && nullptr == root->left && nullptr == root->right)
        {
            delete root;

            return nullptr;
        }

        return root;
    }
};

int main()
{
    return 0;
}
