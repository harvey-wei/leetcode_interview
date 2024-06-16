#include <climits>
#include <limits>
#include <algorithm>


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
    Solution()
    {
        max_sum = INT_MIN;
    }

    /**
     * SRTBOT
     * Subproblem: f(root) =  gain_from_subtree(root) is the max length of path starting at root.
     * Relation: f(root) = root->val + max(max(f(root.left), 0), max(f(root.right).0))
     * Topologial order: From the last step, we can see we need to process both left and right
     first.  -> post-order traversal
     * Base case: null node f(null) = 0;
     * Original Problem: max(f(root), root + f(root->left) >= 0 + f(root->right) >= 0)
     * Here, we have two parellel recursion.
     * One is gain from subtree. Another is left -> root-> right sum
     */
    int gain_from_subtree(TreeNode* root)
    {
        if (nullptr == root ) return 0;

        /* We negative gain to zero for the purpose of ignoring it. */
        int gain_left = std::max(gain_from_subtree(root->left), 0);
        int gain_right = std::max(gain_from_subtree(root->right), 0);

        /* A new path: left -> root-> right upate the max_sum */
        /* Note only positive left and right are added. */
        /* If root is the root of the original tree. -> orignal problem*/
        max_sum = std::max(max_sum, gain_left + gain_right + root->val);

        return root->val + std::max(gain_left, gain_right);

    }

    int maxPathSum(TreeNode* root) {
        gain_from_subtree(root);
        return max_sum;
    }
private:
    int max_sum;
};
