#include <stack>
/**
 * Definition for a binary tree node.
 */


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

    // curr_sum = sum from root to current node (current node is LSD)
    // Each node value is 0 - 9
    void pre_dfs(TreeNode* root, int curr_sum, int& root2leaf)
    {
        if (nullptr != root)
        {
            // Image you shift orginal root to current node's parent to left (x10)
            // update sum from root to current node
            curr_sum = curr_sum * 10 + root->val;

            // Reach a leaf and update root2leaf
            if (nullptr == root->left && nullptr == root->right)
            {
                root2leaf += curr_sum;
            }

            // curr_sum must be passed by value to avoid un-choose.
            pre_dfs(root->left, curr_sum, root2leaf);
            pre_dfs(root->right, curr_sum, root2leaf);
        }

    }

    int sumNumbers(TreeNode* root)
    {
        int root2leaf = 0;
        pre_dfs(root, 0, root2leaf);

        return root2leaf;
    }
};
