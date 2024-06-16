#include <iostream>
 struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode() : val(0), left(nullptr), right(nullptr) {}
     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };

class Solution_ {
public:
    TreeNode* pruneTree(TreeNode* root) {
        if (nullptr == root)
        {
            return nullptr;
        }

        /* You must identify which of pre-order, in-order, post-order to use. */
        /* Root can be removed if and only if its left and right subtree are nullptr. */
        /* Hence, post-order traversal. check left and check right and then check the current! */
        root->left = pruneTree(root->left);
        root->right = pruneTree(root->right);

        if (0 == root->val && nullptr == root->left && nullptr == root->right)
        {
            delete root;
            root = nullptr;
        }

        return  root;

    }
};

class Solution
{
    public:
        /* return the new root value after deciding whether to pruning the tree. */
        TreeNode* pruneTree(TreeNode* root)
        {
            if (nullptr == root)
            {
                /* base case 1*/
                return nullptr;
            }
            else
            {
                root->left = pruneTree(root->left);
                root->right = pruneTree(root->right);

                if (0 == root->val && nullptr == root->left && nullptr == root->right)
                {
                    /* prune the tree */
                    delete root;
                    root = nullptr;
                }

                return root;
            }
        }
};


int main()
{
    return 0;
}
